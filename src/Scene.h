//
// Created by William Aey on 8/16/2022.
//

#pragma once
#include "glfwWindow.h"
class Scene {
public:
    Scene() = default;
    virtual ~Scene(){};
    virtual void OnUpdate(glfwWindow *&window) = 0;
    virtual void OnRender() = 0;

protected:
    unsigned int VBO, VAO;
};
