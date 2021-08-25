///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Released under the zlib License                     |//
//| More information available in the readme file       |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#pragma once
#ifndef _ENJ_GUARD_GAME_H_
#define _ENJ_GUARD_GAME_H_

// TODO 3: culling based on position is done before actually updating the position


// ****************************************************************
class cGame final
{
private:
    cPlayer      m_Player;
    coreObject3D m_PlayerShadow;

    coreBatchList m_EnemyList;
    coreBatchList m_EnemyShadowList;
    coreBatchList m_BlockList;

    coreMemoryPool m_EnemyPool;
    coreMemoryPool m_EnemyShadowPool;
    coreMemoryPool m_BlockPool;

    coreUint32  m_iScore;

    coreFlow    m_fEndTime;
    coreFlow    m_fEndAngle;
    coreVector3 m_vEndCamPos;
    coreFlow    m_fEndCamLen;


public:
    cGame()noexcept;
    ~cGame();

    DISABLE_COPY(cGame)

    void Render();
    void Move();

    void RenderShadow();

    inline const coreFloat& GetEndTime()const {return m_fEndTime;}


private:
    void __LoadLevels();

    RETURN_RESTRICT cEnemy* __CreateEnemy(const coreUint8 iType);
};


#endif // _ENJ_GUARD_GAME_H_