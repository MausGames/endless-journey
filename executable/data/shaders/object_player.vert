///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////


void VertexMain()
{
    gl_Position      = coreObject3DPositionRaw();
    v_av2TexCoord[0] = coreObject3DTexCoordRaw();

    coreLightingTransformRaw();
}