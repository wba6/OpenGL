//
// Created by William Aey on 8/16/2022.
//

#ifndef OPENGL_SCENEPICKER_H
#define OPENGL_SCENEPICKER_H
#include "Core_defines.h"
#include "Scene.h"
class ScenePicker {
public:
    ScenePicker() = default;
    void AddScene();
    void NextScene();

private:
    void currentScene();
    std::vector<Scene *> m_scenes;
};


#endif//OPENGL_SCENEPICKER_H
