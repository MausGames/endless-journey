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
cBlock::cBlock()noexcept
: m_iState (0u)
{
    this->DefineModel  ("object_block.md3");
    this->DefineProgram("object_block_program");
}