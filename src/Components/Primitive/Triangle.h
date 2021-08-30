#pragma once

#include <vector>

class CFComponent{
    public:

};
class Triangle: public CFComponent{
public:
    Triangle(){}

    std::vector<float> vertices = {
                -0.5f, 0.5f, 0.0f, // left
                0.5f, 0.5f, 0.0f, // right
                0.0f,  0.0f, 0.0f  // top
    };

    std::vector<unsigned int> indices = {
        0, 1, 2,  // first Triangle
    };
};