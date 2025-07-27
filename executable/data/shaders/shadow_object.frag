///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////


smoothEx varying float v_v1Height;


void FragmentMain()
{
    if(v_v1Height >= -0.001) discard;
    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}