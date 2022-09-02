//
// Created by William Aey on 8/16/2022.
//

#ifndef OPENGL_SCENEPICKER_H
#define OPENGL_SCENEPICKER_H
#include "Common_defines.h"
#include "Scene.h"
class ScenePicker {
public:
    ScenePicker();
    ~ScenePicker();
    void AddScene(Scene *scene);
    void NextScene();

private:
    unsigned int m_CurrentScene;
    std::vector<Scene *> m_scenes;
};


#endif//OPENGL_SCENEPICKER_H
