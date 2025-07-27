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
cGame::cGame()noexcept
: m_EnemyList       (1024u *  7u)
, m_EnemyShadowList (1024u *  7u)
, m_BlockList       (1024u * 24u)
, m_iScore          (10u)
, m_fEndTime        (0.0f)
, m_fEndAngle       (0.0f)
, m_vEndCamPos      (coreVector3(0.0f,0.0f,0.0f))
, m_fEndCamLen      (0.0f)
{
    m_PlayerShadow.DefineModel  ("default_sphere.md3z");
    m_PlayerShadow.DefineProgram("shadow_object_program");
    m_PlayerShadow.SetSize      (coreVector3(0.99f,0.99f,3.0f) * 0.55f);

    m_EnemyPool      .Configure(sizeof(cEnemy),       1024u);
    m_EnemyShadowPool.Configure(sizeof(coreObject3D), 1024u);
    m_BlockPool      .Configure(sizeof(cBlock),       1024u);

    m_EnemyList      .DefineProgram("object_enemy_inst_program");
    m_EnemyShadowList.DefineProgram("shadow_object_inst_program");
    m_BlockList      .DefineProgram("object_block_inst_program");

    this->__LoadLevels();

    m_EnemyList.MoveNormal();   // for first culling iteration

    const cBlock oTemplate;   // for faster resource lookup

    for(coreUintW j = 0u; j < STEPS; ++j)
    {
        const coreFloat fDistance = I_TO_F(j) *  BLOCK_DISTANCE + BLOCK_START;
        const coreFloat fHeight   = I_TO_F(j) * -BLOCK_HEIGHT - 1.0f;
        const coreFloat fRadius   = 2.0f*PI * fDistance;
        const coreUintW iNum      = FLOOR(fRadius / 2.7f);
        const coreFloat fAngle    = 2.0f*PI / I_TO_F(iNum);
        const coreFloat fFix      = 1.0f + FRACT(fRadius / 2.7f) / I_TO_F(iNum);

        for(coreUintW i = 0u; i < iNum; ++i)
        {
            cBlock* pBlock = POOLED_NEW(m_BlockPool, cBlock, oTemplate);

            const coreVector2 vDir = coreVector2::Direction(I_TO_F(i) * fAngle);

            pBlock->SetPosition (coreVector3(vDir * -fDistance, fHeight));
            pBlock->SetSize     (coreVector3(1.3f * fFix, 1.0f, 1.0f));
            pBlock->SetDirection(coreVector3(vDir, 0.0f));
            pBlock->SetColor3   (coreVector3(1.0f,1.0f,1.0f) * Core::Rand->Float(0.85f, 1.0f));

            m_BlockList.BindObject(pBlock);
        }
    }
}


// ****************************************************************
cGame::~cGame()
{
    m_EnemyPool      .Shutdown();
    m_EnemyShadowPool.Shutdown();
    m_BlockPool      .Shutdown();

    FOR_EACH(it, *m_EnemyList      .List()) POOLED_DELETE(m_EnemyPool,       *it)
    FOR_EACH(it, *m_EnemyShadowList.List()) POOLED_DELETE(m_EnemyShadowPool, *it)
    FOR_EACH(it, *m_BlockList      .List()) POOLED_DELETE(m_BlockPool,       *it)
}


// ****************************************************************
void cGame::Render()
{
    m_BlockList.Render();

    g_pShadow->Apply();

    m_EnemyList.Render();
    m_Player   .Render();
}


// ****************************************************************
void cGame::Move()
{
    m_Player.Move();

    m_PlayerShadow.SetPosition(m_Player.GetPosition());
    m_PlayerShadow.SetEnabled (m_Player.IsEnabled(CORE_OBJECT_ENABLE_ALL) ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
    m_PlayerShadow.Move();

    const coreBool bFinished = m_Player.IsFinished();

    if(bFinished)
    {
        if(!m_fEndTime)
        {
            m_fEndAngle  = (-Core::Graphics->GetCamDirection().xy()).Angle();
            m_vEndCamPos = Core::Graphics->GetCamPosition();
            m_fEndCamLen = Core::Graphics->GetCamPosition().Length();
        }

        m_fEndTime  .Update(1.0f);
        m_fEndAngle .Update(STEP(0.0f, 2.0f, m_fEndTime - 3.0f) * -0.5f);
        m_fEndCamLen.Update(STEP(0.0f, 2.0f, m_fEndTime - 3.0f) *  4.0f);

        const coreVector2 vEndDir = coreVector2::Direction(m_fEndAngle);
        const coreFloat   fTime   = BLENDS(CLAMP01((m_fEndTime - 1.0f) * 0.2f));

        const coreVector3 vCamDir = LERP(coreVector3(vEndDir, 0.5f), coreVector3(0.0f,0.0f,1.0f),                      fTime).Normalized();
        const coreVector3 vCamOri = LERP(CAMERA_ORIENTATION,         coreVector3(-vEndDir, 0.0f),                      fTime).Normalized();
        const coreVector3 vCamPos = LERP(m_vEndCamPos,               vCamDir * MIN(m_fEndCamLen + m_fEndTime, 200.0f), fTime);

        Core::Graphics->SetCamera(vCamPos, -vCamDir, vCamOri);
    }
    else
    {
        const coreVector3 vBase = m_Player.GetCamBase();

        const coreVector3 vCamDir = coreVector3(vBase.xy().Normalized(), 0.5f);
        const coreVector3 vCamOri = CAMERA_ORIENTATION;
        const coreVector3 vCamPos = vBase + vCamDir * 20.0f;

        Core::Graphics->SetCamera(vCamPos, -vCamDir.Normalized(), vCamOri);
    }

    const coreVector3 vCamPos = Core::Graphics->GetCamPosition();
    const coreVector3 vCamDir = Core::Graphics->GetCamDirection();

    const auto nIsVisible = [](const coreVector3 vPos, const coreVector3 vCamPos, const coreVector3 vCamDir, const coreBool bFinished)
    {
        return !((!bFinished && (vPos.z < -BLOCK_HEIGHT * 20.0f) && (coreVector2::Dot(vPos.xy(), vCamDir.xy()) > 0.0f)) || !coreVector3::Visible(vPos, DEG_TO_RAD(50.0f), vCamPos, vCamDir));   // TODO 3: handle aspect ratio
    };

    FOR_EACH(it, *m_EnemyList.List())
    {
        cEnemy* pEnemy = d_cast<cEnemy*>(*it);

        const coreVector3 vPos = pEnemy->GetPosition();

        if(bFinished)
        {
            const coreFloat fRealTime = 1.1f * m_fEndTime + 0.05f * vPos.z;
            pEnemy->SetShift(MAX0(fRealTime) * 40.0f);
        }

        if(nIsVisible(vPos, vCamPos, vCamDir, false))
        {
            pEnemy->SetEnabled(CORE_OBJECT_ENABLE_ALL);

            const coreVector3 vDiff = m_Player.GetPosition() - vPos;
            if(vDiff.LengthSq() < POW2(1.0f))
            {
                if(m_Player.Kick()) pEnemy->Bump();
            }
        }
        else
        {
            pEnemy->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
        }
    }

    m_EnemyList.MoveNormal();

    ASSERT(m_EnemyList.List()->size() == m_EnemyShadowList.List()->size())
    for(coreUintW i = 0u, ie = m_EnemyShadowList.List()->size(); i < ie; ++i)
    {
        const coreObject3D* pEnemy  = (*m_EnemyList      .List())[i];
        coreObject3D*       pShadow = (*m_EnemyShadowList.List())[i];

        pShadow->SetPosition(pEnemy->GetPosition());
        pShadow->SetEnabled (pEnemy->IsEnabled(CORE_OBJECT_ENABLE_ALL) ? CORE_OBJECT_ENABLE_ALL : CORE_OBJECT_ENABLE_NOTHING);
    }

    m_EnemyShadowList.MoveNormal();

    FOR_EACH(it, *m_BlockList.List())
    {
        cBlock* pBlock = d_cast<cBlock*>(*it);

        const coreVector3 vPos = pBlock->GetPosition();

        if(bFinished)
        {
            if(!pBlock->GetState())
            {
                const coreFloat fRealTime  = m_fEndTime + 0.05f * vPos.z + 2.0f * (1.0f - pBlock->GetColor3().x);
                const coreFloat fRealSpeed = (fRealTime < 0.0f) ? 0.0f : 40.0f;

                pBlock->SetPosition(vPos + coreVector3(vPos.xy().Normalized() * (TIME * fRealSpeed), 0.0f));
            }
        }

        if(nIsVisible(vPos, vCamPos, vCamDir, bFinished))
        {
            pBlock->SetEnabled(CORE_OBJECT_ENABLE_ALL);

            if(!pBlock->GetState())
            {
                const coreVector3 vDiff = m_Player.GetPosition() - vPos;
                if((vDiff.z > 1.4f) && (vDiff.z < 1.8f) && (vDiff.xy().LengthSq() < POW2(1.7f)))
                {
                    const coreVector3 vColor = coreVector3(FRACT(I_TO_F(m_iScore) * 0.01f), 0.7f, 0.9f).HsvToRgb();

                    pBlock->SetColor3(vColor);
                    pBlock->SetState (1u);

                    m_Player.SetColor3(vColor);

                    m_iScore += 1u;
                }
            }
        }
        else
        {
            pBlock->SetEnabled(CORE_OBJECT_ENABLE_NOTHING);
        }
    }

    m_BlockList.MoveNormal();
}


// ****************************************************************
void cGame::RenderShadow()
{
    m_PlayerShadow   .Render();
    m_EnemyShadowList.Render();
}


// ****************************************************************
RETURN_RESTRICT cEnemy* cGame::__CreateEnemy(const coreUint8 iType)
{
    cEnemy* pEnemy = POOLED_NEW(m_EnemyPool, cEnemy);
    pEnemy->SetBaseType(iType);

    coreObject3D* pShadow = POOLED_NEW(m_EnemyShadowPool, coreObject3D);
    pShadow->DefineModel  ("default_sphere.md3z");
    pShadow->DefineProgram("shadow_object_program");
    pShadow->SetSize      (coreVector3(0.99f,0.99f,3.0f) * 0.65f);

    m_EnemyList      .BindObject(pEnemy);
    m_EnemyShadowList.BindObject(pShadow);

    return pEnemy;
}