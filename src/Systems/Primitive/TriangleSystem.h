//
// Created by fordchen on 2021/8/30.
//

#ifndef CFRENDERENGINE_TRIANGLESYSTEM_H
#define CFRENDERENGINE_TRIANGLESYSTEM_H

#include "Systems/Base/System.h"
#include "Components/Primitive/Triangle.h"

CFENGINE_RENDER_START
class TriangleSystem : public System{
public:

    std::shared_ptr<Renderer> update(entt::registry &registry, float dt) override;


private:
    std::string m_vertexShader = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
    std::string m_fragmentShader = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 u_color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = u_color;\n"
                                   "}\n\0";
};
CFENGINE_RENDER_END

#endif //CFRENDERENGINE_TRIANGLESYSTEM_H
