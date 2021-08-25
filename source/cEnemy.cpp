///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Released under the zlib License                     |//
//| More information available in the readme file       |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
cEnemy::cEnemy()noexcept
: m_iBaseType   (0u)
, m_vLayerPos   (coreVector2(0.0f,0.0f))
, m_fLayerAngle (0.0f)
, m_fLayerShift (0.0f)
, m_iStepFrom   (STEPS - 1u)
, m_iStepTo     (STEPS - 1u)
, m_fStepValue  (0.0f)
, m_fSpeed      (1.0f)
, m_fAngleSpeed (1.0f)
, m_fLifeTime   (0.0f)
, m_fRotation   (0.0f)
, m_fBump       (0.0f)
{
    this->DefineModel  ("object_enemy.md3");
    this->DefineProgram("object_enemy_program");

    this->SetSize(coreVector3(1.0f,1.0f,1.0f) * 0.5f);
}


// ****************************************************************
void cEnemy::Move()
{
    m_fLifeTime += 1.0f * TIME * ABS(m_fSpeed);

    switch(m_iBaseType)
    {
    default: ASSERT(false)

    // move
    case 0u:
        m_fLayerAngle += 0.02f * TIME * m_fSpeed * m_fAngleSpeed;
        m_fStepValue   = 0.1f;
        break;

    // move and jump
    case 2u:
        m_fLayerAngle += 0.02f * TIME * m_fSpeed * m_fAngleSpeed;
        FALLTHROUGH

    // jump
    case 1u:
        const coreFloat fValue = FMOD(m_fLifeTime, 2.0f);
        m_fStepValue = (fValue < 1.0f) ? fValue : (2.0f - fValue);
        break;
    }

    m_fRotation.Update(1.0f);
    m_fBump.UpdateMax(-5.0f, 0.0f);

    const coreBool bIsActive = this->IsEnabled(CORE_OBJECT_ENABLE_MOVE);

    const coreVector2 vLayerDir = coreVector2::Direction(m_fLayerAngle);
    const coreFloat   fJump     = bIsActive ? (SIN(m_fStepValue * PI) * 1.2f) : 0.0f;
    const coreFloat   fStretch  = bIsActive ? (SIN(m_fBump      * PI) + 1.0f) : 1.0f;

    const coreFloat fLerp = (m_iStepFrom != m_iStepTo) ? LERPS(I_TO_F(m_iStepFrom), I_TO_F(m_iStepTo), FRACT(m_fStepValue)) : I_TO_F(m_iStepFrom);

    m_vLayerPos.x = fLerp *  BLOCK_DISTANCE + BLOCK_START - 1.0f + m_fLayerShift;
    m_vLayerPos.y = fLerp * -BLOCK_HEIGHT;

    const coreVector3 vPos = coreVector3(vLayerDir * m_vLayerPos.x, m_vLayerPos.y + this->GetSize().x);
    const coreVector2 vDir = bIsActive ? coreVector2::Direction(m_fRotation) : coreVector2(0.0f,1.0f);

    this->SetPosition   (coreVector3(vPos.xy(), vPos.z + fJump));
    this->SetSize       (coreVector3(1.0f,1.0f,1.0f) * 0.5f * fStretch);
    this->SetDirection  (coreVector3(vDir, 0.0f));
    this->SetOrientation(coreVector3(-vDir.x*vDir.y, vDir.x*vDir.x, vDir.y));

    this->coreObject3D::Move();
}