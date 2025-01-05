///////////////////////////////////////////////////////////
//*-----------------------------------------------------*//
//| Part of Endless Journey (https://www.maus-games.at) |//
//*-----------------------------------------------------*//
//| Copyright (c) 2021 Martin Mauersics                 |//
//| Released under the zlib License                     |//
//*-----------------------------------------------------*//
///////////////////////////////////////////////////////////


flat varying float v_v1Front;
varying      float v_v1Gradient;


void FragmentMain()
{
    float v1Intensity = 0.4 + 0.6 * dot(normalize(v_v3ViewDir), vec3(0.0, 0.0, 1.0));
    gl_FragColor = vec4(vec3(mix(0.25, v1Intensity, v_v1Front) * v_v1Gradient + coreDither() / 255.0), 1.0) * u_v4Color;
}