#ifndef SOURCE_H
#define SOURCE_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include "Button.h"
#include "GameObject.h"
#include <vector>
#include <algorithm> // Untuk menggunakan std::shuffle
#include <random>    // Untuk menggunakan std::random_device dan std::mt19937
#include <fstream>


namespace Engine {
	enum class ScreenState {
		MAIN_MENU,
		IN_GAME,
		END_GAME
	};

	class Source :
		public Engine::Game
	{
	public:
		Source(Setting* setting);
		~Source();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	private:
		void InitMainMenu();
		void InitInGame();
		void InitEndGame();
		void UpdateMainMenu();
		void UpdateInGame();
		void UpdateEndGame();
		void RenderMainMenu();
		void RenderInGame();
		void RenderEndGame();
		void ResetGame();
		void SaveHighScore(int highScore);
		int LoadHighScore();

		ScreenState screenState;
		Texture* buttonTexture = NULL;
		Sprite* basketSprite = NULL;
		Sprite* avocadoSprite = NULL;
		Sprite* blueberrySprite = NULL;
		Sprite* strawberrySprite = NULL;
		Sprite* coconutSprite = NULL;
		Sprite* bananaSprite = NULL;
		Sprite* musicSprite = NULL;
		Sprite* soundEffectSprite = NULL;
		Sprite* homeSprite = NULL;
		Sprite* backgroundMainSprite = NULL;
		Sprite* backgroundSprite = NULL;
		Sprite* backgroundEndSprite = NULL;
		Sprite* monkeySprite = NULL;
		Sprite* fruitBasketSprite = NULL;
		Sprite* fruit1MainSprite = NULL;
		Sprite* fruit2MainSprite = NULL;
		Sprite* fruit3MainSprite = NULL;
		Sprite* gameOverSprite = NULL;
		Sprite* titleImageSprite = NULL;
		Sprite* imageAvocadoSprite = NULL;
		Sprite* imageBlueberrySprite = NULL;
		Sprite* imageStrawberrySprite = NULL;
		Sprite* imageCoconutSprite = NULL;
		Sprite* imageBananaSprite = NULL;
		Sprite* imageBomb1Sprite = NULL;
		Sprite* imageBomb2Sprite = NULL;


		Music* music = NULL;;
		Sound* soundPoint = NULL;
		Sound* soundBomb = NULL;
		Sound* soundGameOver = NULL;

		vector<Sprite*> fruits;
		vector<Sprite*> bombs;
		Text* text;
		Text* textPointFruitObject;
		Text* textPointBombObject;
		Text* titleEndGame;
		Text* mainMenu1;
		Text* mainMenu2;
		Text* scoreText;
		Text* endGameScore;
		Text* highScoreText;
		Text* highScoreTextEnd;
		Text* time;
		vector<Button*> buttons;
		vector<Button*> buttonsEndGame;
		vector<GameObject*> objects;
		void SpawnObjects();
		Sprite* CreateSprite(Texture* texture);
		Sprite* CreateSprite2(Texture* texture);

		int currentButtonIndex = 0, totalScore = 0;
		int bomHits;
		float timer = 60.0f;
		float endGameDuration = 60.0f;
		bool isSoundOn = true;
		bool isSoundOnGameOver = false;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
		int spawnCount = 0;	
		bool isGameOverSoundPlaying;
		float spawnTimer;
		int highScore;
		bool isGameOver;
		bool isBombSoundPlaying = soundBomb->IsPlaying(); // Check if the sound is currently playing
		float elapsedTime = 0.0f;
		bool isMuted;
		bool isMutedSoundEffect;


		float fruitSpeed = 1.5f; // Kecepatan awal buah
		float fruitSpeedIncrement = 0.1f; // Peningkatan kecepatan buah setelah periode tertentu
		int fruitSpeedIncrementPeriod = 50; // Periode peningkatan kecepatan buah (dalam jumlah frame)
		int currentFrameFruit = 0; // Jumlah frame yang telah berlalu sejak permainan dimulai

		float bombSpeed = 1.5f;
		float bombSpeedIncrement = 0.13f; // Peningkatan kecepatan bomb setelah periode tertentu
		int bombSpeedIncrementPeriod = 50; // Periode peningkatan kecepatan bomb (dalam jumlah frame)
		int currentFrameBomb = 0; // Jumlah frame yang telah berlalu sejak permainan dimulai

	};
}
#endif

#pragma once
