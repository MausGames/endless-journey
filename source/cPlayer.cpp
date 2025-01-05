///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
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
    this->DefineModel  ("object_player.md3z");
    this->DefineProgram("object_player_program");

    this->SetSize(coreVector3(1.0f,1.0f,1.0f) * 0.55f);

    m_pKickSound = Core::Manager::Resource->Get<coreSound>("kick.opus");
    m_pBellSound = Core::Manager::Resource->Get<coreSound>("bell.opus");
}


// ****************************************************************
void cPlayer::Move()
{
    if(this->IsFinished()) return;

    Core::Input->ForwardHatToStick(CORE_INPUT_JOYSTICK_ANY);

    const coreVector2 vJoystickMove = Core::Input->GetJoystickStickL(CORE_INPUT_JOYSTICK_ANY);

    const coreBool bInputUp    = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_PRESS) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_PRESS) || Core::Input->GetMouseButton(CORE_INPUT_LEFT,  CORE_INPUT_PRESS) || Core::Input->GetJoystickButton(CORE_INPUT_JOYSTICK_ANY, 0u, CORE_INPUT_PRESS));
    const coreBool bInputDown  = (Core::Input->GetKeyboardButton(CORE_INPUT_KEY(S), CORE_INPUT_PRESS) || Core::Input->GetKeyboardButton(CORE_INPUT_KEY(DOWN),  CORE_INPUT_PRESS) || Core::Input->GetMouseButton(CORE_INPUT_RIGHT, CORE_INPUT_PRESS) || Core::Input->GetJoystickButton(CORE_INPUT_JOYSTICK_ANY, 1u, CORE_INPUT_PRESS));
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
    if(bInputRight) m_fVelocity += TIME * fSpeed;

    m_fLayerAngle += TIME * m_fVelocity;
    m_fVelocity   *= 1.0f - TIME * 8.0f;

    if(m_iStepOld != m_iStepNew)
    {
        m_fStepValue.Update(5.0f * m_fStepSpeed);
        if(m_fStepValue >= 1.0f)
        {
            m_fStepValue = 0.0f;
            m_iStepOld   = m_iStepNew;

            if(this->IsFinished())
            {
                this->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
                if(m_pBellSound.IsUsable()) m_pBellSound->PlayRelative(NULL, 0.5f, 1.0f, false, 0u);
            }
        }
    }

    const coreBool bFinalJump = (m_iStepNew == 0u);

    const coreVector2 vLayerDir = coreVector2::Direction(m_fLayerAngle);
    const coreFloat   fJump     = SIN(m_fStepValue * PI) * RCP(m_fStepSpeed) * (bFinalJump ? 2.0f : 1.2f);

    m_vLayerPos.x = (LERPS(I_TO_F(m_iStepOld), I_TO_F(m_iStepNew),                          m_fStepValue) - 1.0f) *  BLOCK_DISTANCE + BLOCK_START - 1.0f;
    m_vLayerPos.y = (LERPS(I_TO_F(m_iStepOld), I_TO_F(m_iStepNew + (bFinalJump ? 4u : 0u)), m_fStepValue) - 1.0f) * -BLOCK_HEIGHT;

    const coreVector3 vPos = coreVector3(vLayerDir * m_vLayerPos.x, m_vLayerPos.y + this->GetSize().x);

    if(!bFinalJump) m_vCamBase = vPos;

    this->SetPosition(coreVector3(vPos.xy(), vPos.z + fJump));

    if(!vPos.xy().IsNull())
    {
        if(!coreMath::IsNear(m_fVelocity, 0.0f))
        {
            const coreMatrix3 mRota = coreMatrix4::RotationAxis(m_fVelocity * RCP(fSpeed) * TIME * -150.0f, coreVector3(vPos.xy().Normalized(), 0.0f)).m123();

            this->SetDirection  ((this->GetDirection  () * mRota).Normalized());
            this->SetOrientation((this->GetOrientation() * mRota).Normalized());
        }

        if(m_iStepOld != m_iStepNew)
        {
            const coreMatrix3 mRota = coreMatrix4::RotationAxis((I_TO_F(m_iStepNew) - I_TO_F(m_iStepOld)) * TIME * -4.0f, coreVector3(vPos.xy().Rotated90().Normalized(), 0.0f)).m123();

            this->SetDirection  ((this->GetDirection  () * mRota).Normalized());
            this->SetOrientation((this->GetOrientation() * mRota).Normalized());
        }
    }

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

        if(m_pKickSound.IsUsable()) m_pKickSound->PlayRelative(NULL, 0.7f, 1.0f, false, 0u);

        return true;
    }

    return false;
}