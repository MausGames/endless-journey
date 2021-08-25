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
cInterface::cInterface()noexcept
{
    m_Title.Construct   ("default.ttf", 80u, 2u);
    m_Title.SetCenter   (coreVector2(0.0f,-0.5f));
    m_Title.SetAlignment(coreVector2(0.0f, 1.0f));
    m_Title.SetText     ("ENDLESS JOURNEY");

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
        m_Message.Render();
    }
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void cInterface::Move()
{
    const coreVector3 vCamPos = Core::Graphics->GetCamPosition();
    const coreFloat   fOffset = (vCamPos.z + 187.5f) * -0.05f;

    m_Title.SetPosition(coreVector2(0.0f, 0.11f + fOffset));
    m_Title.Move();

    m_Message.SetAlpha(LERPH3(0.0f, 1.0f, CLAMP((g_pGame->GetEndTime() - 6.0f) * 0.5f, 0.0f, 1.0f)));
    m_Message.Move();
}
