///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////
#include "engine/data_transform_3d.glsl"
#include "engine/data_ambient.glsl"


varying float v_v1Distance;


void VertexMain()
{
    gl_Position = coreObject3DPositionRaw();

    coreLightingTransformRaw();

    v_v1Distance = length(a_v3RawPosition) * 0.4 - 0.05;
}