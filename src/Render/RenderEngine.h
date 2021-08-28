
#include <Systems/Render/DrawTriangleSystem.h>


class RenderEngine : public entityx::EntityX {
public:
  explicit RenderEngine() {
    systems.add<DrawTriangleSystem>();
    systems.configure();
  }

  void update(entityx::TimeDelta dt) {
    systems.update_all(dt);
  }
};