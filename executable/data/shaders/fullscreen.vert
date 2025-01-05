///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#include "engine/data_transform_2d.glsl"


varying vec2 v_v2Relative;


void VertexMain()
{
    gl_Position  = coreObject2DPosition();
    v_v2Relative = a_v2LowPosition;
}