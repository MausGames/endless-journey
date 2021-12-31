///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#pragma once
#ifndef _ENJ_GUARD_ENEMY_H_
#define _ENJ_GUARD_ENEMY_H_


// ****************************************************************
class cEnemy final : public coreObject3D
{
private:
    coreUint8 m_iBaseType;

    coreVector2 m_vLayerPos;
    coreFloat   m_fLayerAngle;
    coreFloat   m_fLayerShift;

    coreUint16 m_iStepFrom;
    coreUint16 m_iStepTo;
    coreFloat  m_fStepValue;

    coreFloat m_fSpeed;
    coreFloat m_fAngleSpeed;
    coreFlow  m_fLifeTime;

    coreFlow m_fRotation;
    coreFlow m_fBump;


public:
    cEnemy()noexcept;

    DISABLE_COPY(cEnemy)

    void Move()final;

    inline void Bump() {m_fBump = 1.0f;}

    inline void SetBaseType  (const coreUint8  iBaseType)                                    {m_iBaseType   = iBaseType;}
    inline void SetAngle     (const coreFloat  fAngle)                                       {m_fLayerAngle = fAngle;}
    inline void SetShift     (const coreFloat  fShift)                                       {m_fLayerShift = fShift;}
    inline void SetPath      (const coreUint16 iStepFrom, const coreUint16 iStepOffset = 0u) {m_iStepFrom   = iStepFrom; m_iStepTo = iStepFrom - iStepOffset;}
    inline void SetSpeed     (const coreFloat  fSpeed)                                       {m_fSpeed      = fSpeed;}
    inline void SetAngleSpeed(const coreFloat  fAngleSpeed)                                  {m_fAngleSpeed = fAngleSpeed;}
    inline void SetLifeTime  (const coreFloat  fLifeTime)                                    {m_fLifeTime   = fLifeTime;}
};


#endif // _ENJ_GUARD_ENEMY_H_