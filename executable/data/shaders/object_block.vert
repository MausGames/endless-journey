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
    float v1Len    = length(u_v3Position.xy);
    float v1Height = a_v3RawPosition.z + u_v3Position.z;
    float v1Depth  = a_v3RawPosition.y * 1.0 + 1.0;
    float v1Angle  = a_v3RawPosition.x * 1.3 / v1Len + atan(u_v3Position.y, u_v3Position.x);
    vec2  v2Dir    = vec2(cos(v1Angle), sin(v1Angle));

    vec3 v3VertexPos = vec3(v2Dir * (v1Len - v1Depth), v1Height);

    gl_Position      = u_m4ViewProj * vec4(v3VertexPos, 1.0);
    v_av2TexCoord[0] = coreObject3DTexCoordRaw();

    coreLightingTransform(v3VertexPos);
}