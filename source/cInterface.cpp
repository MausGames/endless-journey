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
    m_Title.Construct   ("winterselfie.ttf", 86u, 5u);
    m_Title.SetCenter   (coreVector2(0.0f,-0.5f));
    m_Title.SetAlignment(coreVector2(0.0f, 1.0f));
    m_Title.SetColor3   (coreVector3(1.0f,1.0f,1.0f) * 0.92f);
    m_Title.SetText     ("ENDLESS JOURNEY");

    m_Name.Construct   ("winterselfie.ttf", 48u, 5u);
    m_Name.SetCenter   (m_Title.GetCenter());
    m_Name.SetAlignment(m_Title.GetAlignment());
    m_Name.SetColor3   (coreVector3(1.0f,1.0f,1.0f) * 0.92f);
    m_Name.SetText     ("A GAME BY MARTIN MAUERSICS");

    m_Message.Construct  ("winterselfie.ttf", 60u, 5u);
    m_Message.SetPosition(coreVector2(0.0f,0.0f));
    m_Message.SetColor3  (coreVector3(1.0f,1.0f,1.0f) * 0.92f);
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
    const coreFloat   fOffset = (vCamPos.z + 187.5f) * -0.061f;

    m_Title.SetPosition(coreVector2(0.0f, 0.154f + fOffset));
    m_Title.Move();

    m_Name.SetPosition(coreVector2(0.0f, 0.082f + fOffset));
    m_Name.Move();

    m_Message.SetAlpha(BLENDH3(CLAMP01((g_pGame->GetEndTime() - 6.0f) * 0.5f)));
    m_Message.Move();
}