//
// Created by William Aey on 8/16/2022.
//

#include "ScenePicker.h"
void ScenePicker::AddScene(Scene *scene)
{
    m_scenes.emplace_back(scene);
}
void ScenePicker::NextScene()
{
}
ScenePicker::~ScenePicker()
{
    for (size_t i{0}; i < m_scenes.size(); i++)
    {
        delete m_scenes.at(i);
    }
    m_scenes.clear();
}
ScenePicker::ScenePicker()
{
    m_CurrentScene = 0;
}
