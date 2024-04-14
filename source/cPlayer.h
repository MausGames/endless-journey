///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#pragma once
#ifndef _ENJ_GUARD_PLAYER_H_
#define _ENJ_GUARD_PLAYER_H_


// ****************************************************************
class cPlayer final : public coreObject3D
{
private:
    coreVector2 m_vLayerPos;
    coreFloat   m_fLayerAngle;

    coreUint16 m_iStepOld;
    coreUint16 m_iStepNew;
    coreFlow   m_fStepValue;
    coreFloat  m_fStepSpeed;

    coreFloat m_fVelocity;

    coreVector3 m_vCamBase;

    coreSoundPtr m_pKickSound;
    coreSoundPtr m_pBellSound;


public:
    cPlayer()noexcept;

    DISABLE_COPY(cPlayer)

    void Move()final;

    coreBool Kick();

    inline coreBool IsFinished()const {return (m_iStepOld == 0u);}

    inline const coreVector3& GetCamBase()const {return m_vCamBase;}
};


#endif // _ENJ_GUARD_PLAYER_H_