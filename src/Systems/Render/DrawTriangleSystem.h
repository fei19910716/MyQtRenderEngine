#include "Appearance.h"

#include <entityx/entityx.h>

class DrawTriangleSystem : public Appearance, public entityx::System<DrawTriangleSystem>{
public:

    // void configure(ex::EventManager &events) override;

    void update(entityx::EntityManager& entities,
                entityx::EventManager& events, double dt) override;

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