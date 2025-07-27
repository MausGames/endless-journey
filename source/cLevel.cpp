///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#include "main.h"

#define STEPS_REV(x) (STEPS - (x))


// ****************************************************************
void cGame::__LoadLevels()
{
    coreUint16 iCurStep = 7u;

    // ################################################################
    // introduction
    for(coreUintW j = 0u; j < 5u; ++j)
    {
        for(coreUintW i = 0u, ie = 80u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle((I_TO_F(i) + GA * I_TO_F(j)) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));
        }
        iCurStep++;
    }

    // ################################################################
    // moving
    for(coreUintW j = 0u; j < 15u; ++j)
    {
        for(coreUintW i = 0u, ie = 80u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle((I_TO_F(i) + 0.5f * I_TO_F(j)) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

                 if(j <  5u) pEnemy->SetSpeed( 1.0f + 0.3f * I_TO_F(j));
            else if(j < 10u) pEnemy->SetSpeed(-1.0f - 0.3f * I_TO_F(j));
            else if(j < 15u) pEnemy->SetSpeed((j % 2u) ? -4.0f : 2.0f);
        }
        iCurStep++;
    }

    // ################################################################
    // up and down
    for(coreUintW j = 0u; j < 10u; ++j)
    {
        for(coreUintW i = 0u, ie = 80u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle((I_TO_F(i) - GA * I_TO_F(j)) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 1u);

            if(j >= 5u) pEnemy->SetLifeTime(I_TO_F(i) * 0.25f);
        }
        iCurStep++;
    }

    iCurStep++;

    // ################################################################
    // frogger
    for(coreUintW j = 0u; j < 4u; ++j)
    {
        for(coreUintW i = 0u, ie = 320u; i < ie; ++i)
        {
            if((i % 4u) < 2u) continue;

            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle((I_TO_F(i) + 0.5f * I_TO_F(j)) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed((2.0f + 0.6f * I_TO_F(j)) * ((j % 2u) ? 1.0f : -1.0f));
        }
        iCurStep++;
    }

    iCurStep++;   // pause

    // ################################################################
    // tripple groups
    for(coreUintW j = 0u; j < 1u; ++j)
    {
        for(coreUintW i = 0u, ie = 300u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 2u);

            pEnemy->SetSpeed(0.7f);
            pEnemy->SetLifeTime(((i % 6u) < 3u) ? 1.0f : 0.0f);
        }
        iCurStep += 3u;
    }

    // ################################################################
    // moving tripple groups
    for(coreUintW j = 0u; j < 1u; ++j)
    {
        for(coreUintW i = 0u, ie = 300u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(2u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 2u);

            pEnemy->SetSpeed(0.7f);
            pEnemy->SetLifeTime(((i % 6u) < 3u) ? 1.0f : 0.0f);
        }
        iCurStep += 3u;
    }

    // ################################################################
    // tight timing
    for(coreUintW j = 0u; j < 5u; ++j)
    {
        for(coreUintW i = 0u, ie = 40u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));
        }
        if(j) for(coreUintW i = 0u, ie = 280u; i < ie; ++i)
        {
            if((i % 4u) < 1u) continue;

            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed((j % 2u) ? 1.0f : -1.0f);
        }
        iCurStep++;
    }

    // ################################################################
    // overlap
    for(coreUintW j = 0u; j < 3u; ++j)
    {
        for(coreUintW i = 0u, ie = 240u; i < ie; ++i)
        {
            if(!j && ((i % 8u) < 4u)) continue;

            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed(-2.0f * (((i % 8u) < 4u) ? 1.0f : ((j == 2u) ? 2.0f : -1.0f)));
        }
        iCurStep++;
    }

    // ################################################################
    // waves
    for(coreUintW j = 0u; j < 2u; ++j)
    {
        for(coreUintW i = 0u, ie = 210u; i < ie; ++i)
        {
            if((i % 6u) < 1u) continue;

            cEnemy* pEnemy = this->__CreateEnemy(2u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 2u);

            pEnemy->SetAngleSpeed(4.0f * ((j % 2u) ? 1.0f : -1.0f));
            pEnemy->SetLifeTime(I_TO_F(i) / I_TO_F(ie) * ((j % 2u) ? 2.0f : 1.0f) * 18.0f);
        }
        iCurStep += 3u;
    }

    // ################################################################
    // high speed
    for(coreUintW j = 0u; j < 3u; ++j)
    {
        for(coreUintW i = 0u, ie = 35u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed(14.0f);
        }
        iCurStep++;
    }

    iCurStep++;   // pause

    // ################################################################
    // avalanche
    for(coreUintW j = 0u; j < 1u; ++j)
    {
        for(coreUintW i = 0u, ie = 360u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 9u);

            pEnemy->SetSpeed(0.3f);
            pEnemy->SetLifeTime(I_TO_F(i) / I_TO_F(ie) * 134.0f);
        }
        iCurStep += 10u;
    }

    // ################################################################
    // jumping boxes
    for(coreUintW j = 0u; j < 3u; ++j)
    {
        for(coreUintW i = 0u, ie = 150u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(2u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep), 3u);

            pEnemy->SetSpeed(((i % 6u) < 3u) ? -1.0f : 1.0f);
            pEnemy->SetAngleSpeed(4.0f);
            pEnemy->SetLifeTime(((i % 6u) < 3u) ? 1.0f : 0.0f);
        }
        iCurStep++;
    }

    iCurStep += 3u;

    // ################################################################
    // labyrinth
    for(coreUintW j = 0u; j < 3u; ++j)
    {
        for(coreUintW i = 0u, ie = 40u; i < ie; ++i)
        {
            if((j == 0u) && ((i % 2u) == 0u)) continue;
            if((j == 2u) && ((i % 2u) == 1u)) continue;

            cEnemy* pEnemy = this->__CreateEnemy(1u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));
        }
        iCurStep++;
    }

    // ################################################################
    // train
    for(coreUintW j = 0u; j < 2u; ++j)
    {
        for(coreUintW i = 0u, ie = 120u; i < ie; ++i)
        {
            if((i % 60u) < 10u) continue;

            cEnemy* pEnemy = this->__CreateEnemy(0u);

            pEnemy->SetAngle(I_TO_F(i) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed(40.0f * (j ? -1.0f : 1.0f));
        }
        iCurStep++;
    }

    iCurStep++;   // pause

    // ################################################################
    // ceremony
    for(coreUintW j = 0u; j < 10u; ++j)
    {
        for(coreUintW i = 0u, ie = 10u; i < ie; ++i)
        {
            cEnemy* pEnemy = this->__CreateEnemy(2u);

            pEnemy->SetAngle((I_TO_F(i) + GA * I_TO_F(j)) / I_TO_F(ie) * 2.0f*PI);
            pEnemy->SetPath(STEPS_REV(iCurStep));

            pEnemy->SetSpeed((j % 2u) ? -1.0f : 1.0f);
            pEnemy->SetAngleSpeed(4.0f);
        }
        iCurStep++;
    }
}