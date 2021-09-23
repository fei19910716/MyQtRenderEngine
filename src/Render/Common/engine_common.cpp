
#include "engine_common.h"

CFENGINE_RENDER_START
std::vector<float> SIMPLE_VERTEX = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
};

std::vector<unsigned int> SIMPLE_INDEX = {
        0, 1, 2, 2, 3, 0,
};
CFENGINE_RENDER_END