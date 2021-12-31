///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#pragma once
#ifndef _ENJ_GUARD_INTERFACE_H_
#define _ENJ_GUARD_INTERFACE_H_


// ****************************************************************
class cInterface final
{
private:
    coreLabel m_Title;
    coreLabel m_Name;
    coreLabel m_Message;


public:
    cInterface()noexcept;

    DISABLE_COPY(cInterface)

    void Render();
    void Move();
};


#endif // _ENJ_GUARD_INTERFACE_H_