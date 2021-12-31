///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////


varying float v_v1Height;


void VertexMain()
{
    v_v1Height  = a_v3RawPosition.z;
    gl_Position = coreObject3DPositionRaw();
}