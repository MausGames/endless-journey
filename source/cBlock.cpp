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
cBlock::cBlock()noexcept
: m_iState (0u)
{
    this->DefineModel  ("object_block.md3");
    this->DefineProgram("object_block_program");
}