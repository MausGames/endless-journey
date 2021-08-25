///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Released under the zlib License                     |//
//| More information available in the readme file       |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#include "main.h"

STATIC_MEMORY(cInterface, g_pInterface)
STATIC_MEMORY(cGame,      g_pGame)
STATIC_MEMORY(cShadow,    g_pShadow)


// ****************************************************************
// init the application
void CoreApp::Init()
{
    Core::Graphics->SetCamera(CAMERA_POSITION, CAMERA_DIRECTION, CAMERA_ORIENTATION);
    Core::Graphics->SetView(Core::System->GetResolution(), DEG_TO_RAD(45.0f), 10.0f, 500.0f);

    STATIC_NEW(g_pInterface)
    STATIC_NEW(g_pGame)
    STATIC_NEW(g_pShadow)
}


// ****************************************************************
// exit the application
void CoreApp::Exit()
{
    STATIC_DELETE(g_pShadow)
    STATIC_DELETE(g_pGame)
    STATIC_DELETE(g_pInterface)
}


// ****************************************************************
// render the application
void CoreApp::Render()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    g_pGame     ->Render();
    g_pInterface->Render();
}


// ****************************************************************
// move the application
void CoreApp::Move()
{
    if(Core::System->GetWinSizeChanged())
    {
        Core::Reshape();
    }

    if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(ESCAPE), CORE_INPUT_PRESS))
    {
        Core::System->Quit();
    }

    g_pGame     ->Move();
    g_pInterface->Move();
}