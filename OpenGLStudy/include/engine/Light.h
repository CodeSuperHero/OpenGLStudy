#pragma once
#include "engine/Engine.h"

namespace OSEngine
{
    class Shader;
    class Camera;

    class Light
    {
    public:
        Light() : mColor(vec3(1.0f, 1.0f, 1.0f)), position(vec3(1.2f, 1.0f, 5.0f)){}
        ~Light() { }
        void Init(unsigned int * vbo);
        void Render(Camera* camera);

        unsigned int GetLightVao() { return lightVao; }
        vec3* GetLightColor() { return &mColor; }
        vec3 Position() { return position; }

    private:
        vec3 position;
        vec3 mColor;
        unsigned int lightVao;
        Shader* shader;
    };
}

/* point light attenuation
7	    1.0	    0.7	    1.8
13	    1.0	    0.35	0.44
20	    1.0	    0.22	0.20
32	    1.0	    0.14	0.07
50	    1.0	    0.09	0.032
65	    1.0	    0.07	0.017
100	    1.0	    0.045	0.0075
160	    1.0	    0.027	0.0028
200	    1.0	    0.022	0.0019
325	    1.0	    0.014	0.0007
600	    1.0	    0.007	0.0002
3250	1.0	    0.0014	0.000007
*/


/* spot light intensity
θ	    θ（角度）   	ϕ（内切）	    ϕ（角度）	    γ（外切）	    γ（角度）	    ϵ	                I
0.87	30	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.87 - 0.82 / 0.09 = 0.56
0.9	    26	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.9 - 0.82 / 0.09 = 0.89
0.97	14	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.97 - 0.82 / 0.09 = 1.67
0.97	14	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.97 - 0.82 / 0.09 = 1.67
0.83	34	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.83 - 0.82 / 0.09 = 0.11
0.64	50	        0.91	    25	        0.82	    35	    0.91 - 0.82 = 0.09	    0.64 - 0.82 / 0.09 = -2.0
0.966	15	        0.9978	    12.5	    0.953	    17.5	0.966 - 0.953 = 0.0448	0.966 - 0.953 / 0.0448 = 0.29
*/