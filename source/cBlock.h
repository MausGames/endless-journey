///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#pragma once
#ifndef _ENJ_GUARD_BLOCK_H_
#define _ENJ_GUARD_BLOCK_H_


// ****************************************************************
class cBlock final : public coreObject3D
{
private:
    coreUint8 m_iState;


public:
    cBlock()noexcept;

    ENABLE_COPY(cBlock)

    inline void SetState(const coreUint8 iState) {m_iState = iState;}

    inline const coreUint8& GetState()const {return m_iState;}
};


#endif // _ENJ_GUARD_BLOCK_H_