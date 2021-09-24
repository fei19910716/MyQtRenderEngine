//
// Created by fordchen on 2021/9/14.
//

#ifndef CFRENDERENGINE_DISPLAYRENDERER_H
#define CFRENDERENGINE_DISPLAYRENDERER_H

#include "Render/Renderer/SimpleRenderer.h"

namespace render{
class DisplayRenderer: public SimpleRenderer {
public:
    DisplayRenderer();
    ~DisplayRenderer();

    /**
     * 需要绑定到窗口FBO
     */
    void bindOutput() override;

    /**
   *
   * 设置显示大小
   *
   * @param width 宽度
   * @param height 高度
   *
   */
    void setDisplaySize(unsigned int width, unsigned int height);


protected:
    unsigned int display_width_, display_height_;
};

}
#endif //CFRENDERENGINE_DISPLAYRENDERER_H
