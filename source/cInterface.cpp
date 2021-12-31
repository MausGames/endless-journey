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
cInterface::cInterface()noexcept
: m_Title   ()
, m_Name    ()
, m_Message ()
{
    m_Title.Construct   ("default.ttf", 80u, 2u);
    m_Title.SetCenter   (coreVector2(0.0f,-0.5f));
    m_Title.SetAlignment(coreVector2(0.0f, 1.0f));
    m_Title.SetText     ("ENDLESS JOURNEY");

    m_Name.Construct   ("default.ttf", 40u, 2u);
    m_Name.SetCenter   (m_Title.GetCenter());
    m_Name.SetAlignment(m_Title.GetAlignment());
    m_Name.SetText     ("A GAME BY MARTIN MAUERSICS");

    m_Message.Construct  ("default.ttf", 60u, 2u);
    m_Message.SetPosition(coreVector2(0.0f,0.0f));
    m_Message.SetText    ("THANK YOU FOR PLAYING");
}


// ****************************************************************
void cInterface::Render()
{
    glDisable(GL_DEPTH_TEST);
    {
        m_Title  .Render();
        m_Name   .Render();
        m_Message.Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cInterface::Move()
{
    const coreVector3 vCamPos = Core::Graphics->GetCamPosition();
    const coreFloat   fOffset = (vCamPos.z + 187.5f) * -0.058f;

    m_Title.SetPosition(coreVector2(0.0f, 0.145f + fOffset));
    m_Title.Move();

    m_Name.SetPosition(coreVector2(0.0f, 0.085f + fOffset));
    m_Name.Move();

    m_Message.SetAlpha(LERPH3(0.0f, 1.0f, CLAMP((g_pGame->GetEndTime() - 6.0f) * 0.5f, 0.0f, 1.0f)));
    m_Message.Move();
}