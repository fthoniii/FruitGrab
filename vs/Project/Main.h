#ifndef Main_H
#define Main_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "Music.h"
#include "Sound.h"
#include "GameObject.h"
#include <vector>

namespace Engine {
	enum class ScreenState {
		MAIN_MENU,
		IN_GAME,
		NO_SOUND
	};
	class Main :public Engine::Game
	{
	public:
		Main(Setting* setting);
		~Main();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		int currentButtonIndex = 0;
		ScreenState screenState;
		vector<Button*> buttons;
		Text* text;
		void InitMainMenu();
		void InitInGame();
		void InitNoSound();
		void InitMusic();
		void RenderMainMenu();
		void RenderInGame();
		void RenderNoSound();
		void UpdateMainMenu();
		void UpdateInGame();
		void UpdateNoSound();
		Sprite* backgroundSprite = NULL;
		Sprite* basketSprite = NULL;
		float x = 0;
		vector<Sprite*> platforms;

		Music* music = NULL;;
		Sound* sound = NULL;
		Engine::Sprite* CreateSprite(Texture* texture);
		void SpawnObjects();
		vector<GameObject*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
		bool debug = false;
		float yVelocity = 0;
		bool jump = false;
	};
}

#endif

