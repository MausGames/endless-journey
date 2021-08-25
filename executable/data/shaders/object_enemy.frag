///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Released under the zlib License                     |//
//| More information available in the readme file       |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////


varying float v_v1Distance;


void FragmentMain()
{
    float v1Intensity = 0.4 + 0.4 * dot(normalize(v_v3ViewDir), vec3(0.0, 0.0, 1.0));
    gl_FragColor = vec4(vec3(v1Intensity * v_v1Distance), 1.0) * u_v4Color;
}