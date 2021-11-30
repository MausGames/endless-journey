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
cPlayer::cPlayer()noexcept
: m_vLayerPos   (coreVector2(0.0f,0.0f))
, m_fLayerAngle (0.0f)
, m_iStepOld    (STEPS)
, m_iStepNew    (STEPS)
, m_fStepValue  (0.0f)
, m_fStepSpeed  (1.0f)
, m_fVelocity   (0.0f)
, m_vCamBase    (coreVector3(0.0f,0.0f,0.0f))
{
    this->DefineModel  ("default_sphere.md3");
    this->DefineProgram("object_player_program");

    this->SetSize(coreVector3(1.0f,1.0f,1.0f) * 0.5f);
}


// ****************************************************************
void cPlayer::Move()
{
    if(this->IsFinished()) return;

    Core::Input->ForwardHatToStick(0u);

    const coreVector2 vJoystickMove = Core::Input->GetJoystickRelativeL(0u);

    const coreBool bInputUp    = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_PRESS) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_PRESS) || Core::Input->GetMouseButton(CORE_INPUT_LEFT,  CORE_INPUT_PRESS) || Core::Input->GetJoystickButton(0u, 0u, CORE_INPUT_PRESS));
    const coreBool bInputDown  = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(S), CORE_INPUT_PRESS) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(DOWN),  CORE_INPUT_PRESS) || Core::Input->GetMouseButton(CORE_INPUT_RIGHT, CORE_INPUT_PRESS) || Core::Input->GetJoystickButton(0u, 1u, CORE_INPUT_PRESS));
    const coreBool bInputLeft  = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(A), CORE_INPUT_HOLD)  || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(LEFT),  CORE_INPUT_HOLD)  || (vJoystickMove.x < 0.0f));
    const coreBool bInputRight = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(D), CORE_INPUT_HOLD)  || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(RIGHT), CORE_INPUT_HOLD)  || (vJoystickMove.x > 0.0f));

    if((m_iStepOld == m_iStepNew) || (m_fStepValue > 0.8f))
    {
        if(bInputUp && (m_iStepNew > 0u))
        {
            m_iStepOld   = m_iStepNew;
            m_iStepNew  -= 1u;
            m_fStepValue = 0.0f;
            m_fStepSpeed = m_iStepNew ? 1.0f : 0.3f;
        }
        else if(bInputDown && (m_iStepNew < STEPS))
        {
            m_iStepOld   = m_iStepNew;
            m_iStepNew  += 1u;
            m_fStepValue = 0.0f;
            m_fStepSpeed = 1.0f;
        }
    }

    const coreFloat fSpeed = 600.0f * RCP(2.0f*PI * m_vLayerPos.x + 1.5f);

         if(bInputLeft)  m_fVelocity -= TIME * fSpeed;
    else if(bInputRight) m_fVelocity += TIME * fSpeed;

    m_fLayerAngle += TIME * m_fVelocity;
    m_fVelocity   *= 1.0f - TIME * 8.0f;

    if(m_iStepOld != m_iStepNew)
    {
        m_fStepValue.Update(5.0f * m_fStepSpeed);
        if(m_fStepValue >= 1.0f)
        {
            m_fStepValue = 0.0f;
            m_iStepOld   = m_iStepNew;

            if(this->IsFinished()) this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
        }
    }

    const coreBool bFinalJump = (m_iStepNew == 0u);

    const coreVector2 vLayerDir = coreVector2::Direction(m_fLayerAngle);
    const coreFloat   fJump     = SIN(m_fStepValue * PI) * RCP(m_fStepSpeed) * (bFinalJump ? 2.0f : 1.2f);
    const coreFloat   fStretch  = SIN(m_fStepValue * PI) * 0.2f + 1.0f;

    m_vLayerPos.x = (LERPS(I_TO_F(m_iStepOld), I_TO_F(m_iStepNew),                          m_fStepValue) - 1.0f) *  BLOCK_DISTANCE + BLOCK_START - 1.0f;
    m_vLayerPos.y = (LERPS(I_TO_F(m_iStepOld), I_TO_F(m_iStepNew + (bFinalJump ? 4u : 0u)), m_fStepValue) - 1.0f) * -BLOCK_HEIGHT;

    const coreVector3 vPos = coreVector3(vLayerDir * m_vLayerPos.x, m_vLayerPos.y + this->GetSize().x);

    if(!bFinalJump) m_vCamBase = vPos;

    this->SetPosition(coreVector3(vPos.xy(), vPos.z + fJump));
    this->SetSize    (coreVector3(1.0f, 1.0f, fStretch) * 0.5f);

    this->coreObject3D::Move();
}


// ****************************************************************
coreBool cPlayer::Kick()
{
    if((m_iStepOld == m_iStepNew) || (m_fStepValue > 0.8f))
    {
        m_iStepOld   = m_iStepNew;
        m_iStepNew   = MIN(m_iStepNew + KICK, STEPS - 1u);
        m_fStepValue = 0.0f;
        m_fStepSpeed = 0.5f;

        return true;
    }

    return false;
}