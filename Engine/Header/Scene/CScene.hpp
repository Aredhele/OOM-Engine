/// \file       CScene.hpp
/// \date       05/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_SCENE_HPP__
#define OOM_ENGINE_C_SCENE_HPP__

#include <vector>

void LoadGameScene();
void LoadDemoSceneAudio();
void LoadDemoScenePhysics();

class CScene
{
public:

	enum EScene
	{
		Game,
		DemoAudio,
		DemoPhysics
	};

	EScene scene_type;			///< The scene type
	void(*p_scene_loader)();    ///< The scene load function pointer

	static void LoadScene(EScene scene_type)
	{
		for(auto& scene : scenes)
		{
			if (scene.scene_type == scene_type)
			{
				scene.p_scene_loader();
				break;
			}
		}
	}

	static std::vector<CScene> scenes;
};

/* static */ std::vector<CScene> CScene::scenes =
{ 
	{CScene::EScene::Game,        LoadGameScene},
	{CScene::EScene::DemoAudio,   LoadDemoSceneAudio},
	{CScene::EScene::DemoPhysics, LoadDemoScenePhysics}
};

#endif ! //OOM_ENGINE_C_SCENE_HPP__