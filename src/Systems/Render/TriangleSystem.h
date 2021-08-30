//
// Created by fordchen on 2021/8/30.
//

#ifndef CFRENDERENGINE_TRIANGLESYSTEM_H
#define CFRENDERENGINE_TRIANGLESYSTEM_H

#include "System.h"
#include "Components/Primitive/Triangle.h"

class TriangleSystem : public System{
public:

    void update(entt::registry &registry, float dt) override;

private:
    std::string m_vertexShader = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
    std::string m_fragmentShader = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";
};


#endif //CFRENDERENGINE_TRIANGLESYSTEM_H
