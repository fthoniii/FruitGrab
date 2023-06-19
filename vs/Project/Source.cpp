#include "Source.h"

using namespace Engine;

Source::Source(Setting* setting) :Game(setting)
{
	screenState = ScreenState::MAIN_MENU;
}

Source::~Source()
{
	delete basketSprite;
	delete music;
	delete text;
	delete soundPoint;
	delete soundBomb;
	delete soundGameOver;
}

void Source::Init()
{
	InitMainMenu();
	InitInGame();
	InitEndGame();
}

void Source::Update()
{
	if (ScreenState::MAIN_MENU == screenState) {
		UpdateMainMenu();
	}
	else if (ScreenState::IN_GAME == screenState) {
		UpdateInGame();	
	}
	else if (ScreenState::END_GAME == screenState) {
		UpdateEndGame();
	}
}

void Source::Render()
{
	if (ScreenState::MAIN_MENU == screenState) {
		RenderMainMenu();
	}
	else if (ScreenState::IN_GAME == screenState) {
		RenderInGame();
	}
	else if (ScreenState::END_GAME == screenState) {
		RenderEndGame();
	}
}

void Source::InitMainMenu()
{
	//Create Background Main Menu
	Texture* bgMainTexture = new Texture("bg.png");
	backgroundMainSprite = new Sprite(bgMainTexture, defaultSpriteShader, defaultQuad);
	backgroundMainSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Playing music
	music = new Music("musik.ogg");
	music->SetVolume(30); //background music volume nya harus lebih rendah dari sound effect agar tidak mengganggu
	music->Play(isSoundOn);

	// Create a Button
	Texture* buttonTexture = new Texture("btn.png");

	// Create Button Play Sprites
	Sprite* playSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	playSprite->SetNumXFrames(5);
	playSprite->SetNumYFrames(4);
	playSprite->AddAnimation("normal", 12, 12);
	playSprite->AddAnimation("hover", 11, 11);
	playSprite->AddAnimation("press", 11, 11);
	playSprite->SetScale(1.15);
	playSprite->SetAnimationDuration(400);

	// Create Button Sound Effect Sprites
	soundEffectSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	soundEffectSprite->SetNumXFrames(5);
	soundEffectSprite->SetNumYFrames(4);
	soundEffectSprite->AddAnimation("normal", 15, 15);
	soundEffectSprite->AddAnimation("hover", 13, 13);
	soundEffectSprite->AddAnimation("press", 13, 13);
	soundEffectSprite->AddAnimation("mute", 8, 8);
	soundEffectSprite->AddAnimation("muteHover", 3, 3);
	soundEffectSprite->SetScale(0.3);
	soundEffectSprite->SetAnimationDuration(400);

	// Create Button Sound Sprites
	musicSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	musicSprite->SetNumXFrames(5);
	musicSprite->SetNumYFrames(4);
	musicSprite->AddAnimation("normal", 16, 16);
	musicSprite->AddAnimation("hover", 17, 17);
	musicSprite->AddAnimation("press", 17, 17);
	musicSprite->AddAnimation("mute", 0, 0);
	musicSprite->AddAnimation("muteHover", 4, 4);
	musicSprite->SetScale(0.3);
	musicSprite->SetAnimationDuration(400);

	// Create Button Exit Sprites
	Sprite* exitSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(5);
	exitSprite->SetNumYFrames(4);
	exitSprite->AddAnimation("normal", 2, 2);
	exitSprite->AddAnimation("hover", 1, 1);
	exitSprite->AddAnimation("press", 1, 1);
	exitSprite->SetScale(0.3);
	exitSprite->SetAnimationDuration(400);

	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((setting->screenWidth / 1.50) - (playSprite->GetScaleWidth() / 2),
		160);
	buttons.push_back(playButton);

	Button* soundButton = new Button(soundEffectSprite, "sound");
	soundButton->SetPosition((setting->screenWidth / 1.26) - (musicSprite->GetScaleWidth() / 1.15),
		22);
	buttons.push_back(soundButton);

	Button* musicButton = new Button(musicSprite, "music");
	musicButton->SetPosition((setting->screenWidth / 1.15) - (musicSprite->GetScaleWidth() / 1.15),
		22);
	buttons.push_back(musicButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((setting->screenWidth / 1.05) - (exitSprite->GetScaleWidth() / 1.05),
		25);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(ButtonState::HOVER);

	// Create Text Guide
	mainMenu1 = new Text("HitandRun-Regular.otf", 30, defaultTextShader);
	mainMenu1->SetText("PRESS KEY \"UP\" or \"DOWN\" to Move");
	mainMenu1->SetPosition(setting->screenWidth - 1240, setting->screenHeight - 617);
	mainMenu1->SetColor(255, 232, 54);

	mainMenu2 = new Text("HitandRun-Regular.otf", 30, defaultTextShader);
	mainMenu2->SetText("\"ENTER\" to Choose");
	mainMenu2->SetPosition(setting->screenWidth - 1057, setting->screenHeight - 673);
	mainMenu2->SetColor(255, 232, 54);

	// Create Text High Score 
	highScoreText = new Text("HitandRun-Regular.otf", 27, defaultTextShader);
	highScoreText->SetPosition(setting->screenWidth - 1240, setting->screenHeight - 520);
	highScoreText->SetColor(255, 236, 87);
	highScoreText->SetText("High Score : " + std::to_string(LoadHighScore()));

	// Sprite Monkey Decoration
	Texture* monkeyTexture = new Texture("monkey.png");
	monkeySprite = new Sprite(monkeyTexture, defaultSpriteShader, defaultQuad);
	monkeySprite->SetPosition(setting->screenWidth - 1260, setting->screenHeight - 455);
	monkeySprite->SetScale(0.65f);

	// Sprite Fruit Basket Decoration
	Texture* fruitBasketTexture = new Texture("fruitBasket.png");
	fruitBasketSprite = new Sprite(fruitBasketTexture, defaultSpriteShader, defaultQuad);
	fruitBasketSprite->SetPosition(setting->screenWidth - 930, setting->screenHeight - 560);
	fruitBasketSprite->SetScale(0.3f);

	// Sprite Fruit 1 Strawberry Decoration
	Texture* fruitTexture1 = new Texture("fruit1.png");
	fruit1MainSprite = new Sprite(fruitTexture1, defaultSpriteShader, defaultQuad);
	fruit1MainSprite->SetPosition(setting->screenWidth - 725, setting->screenHeight - 170);
	fruit1MainSprite->SetScale(0.3f);
	
	// Sprite Fruit 2 Blueberry Decoration
	Texture* fruitTexture2 = new Texture("fruit2.png");
	fruit2MainSprite = new Sprite(fruitTexture2, defaultSpriteShader, defaultQuad);
	fruit2MainSprite->SetPosition(setting->screenWidth - 495, setting->screenHeight - 190);
	fruit2MainSprite->SetScale(0.15f);

	// Sprite Fruit 3 Banana Decoration
	Texture* fruitTexture3 = new Texture("fruit3.png");
	fruit3MainSprite = new Sprite(fruitTexture3, defaultSpriteShader, defaultQuad);
	fruit3MainSprite->SetPosition(setting->screenWidth - 340, setting->screenHeight - 124);
	fruit3MainSprite->SetScale(0.19f);

	// Sprite Title
	Texture* titleImageTexture = new Texture("titleImage.png");
	titleImageSprite = new Sprite(titleImageTexture, defaultSpriteShader, defaultQuad);
	titleImageSprite->SetPosition(setting->screenWidth - 795, setting->screenHeight - 410);
	titleImageSprite->SetScale(0.72f);

	// Add input mappings
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("press", SDLK_RETURN); //tombol enter

	isMuted = false;
	isMutedSoundEffect = false;
}

void Source::UpdateMainMenu()
{
	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex; //ternary operator
		// Set current button to hover state
		Button* b = buttons[currentButtonIndex];
		if (isMutedSoundEffect && "sound" == b->GetButtonName()) {
			buttons[currentButtonIndex]->SetButtonState(ButtonState::MUTEHOVER);
		}
		else {
			buttons[currentButtonIndex]->SetButtonState(ButtonState::HOVER);
		}
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		Button* b = buttons[currentButtonIndex];
		if (isMutedSoundEffect && "sound" == b->GetButtonName()) {
			buttons[currentButtonIndex]->SetButtonState(ButtonState::MUTEHOVER);
		}
		else {
			buttons[currentButtonIndex]->SetButtonState(ButtonState::HOVER);
		}
	}

	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			buttonsEndGame[currentButtonIndex+1]->SetButtonState(ButtonState::NORMAL);
			currentButtonIndex = 0;
			buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::HOVER);
			screenState = ScreenState::IN_GAME;
		}
		else if ("sound" == b->GetButtonName()) {
			if (isMutedSoundEffect) {
				isMutedSoundEffect = false;
				soundPoint->SetMuted(false);
				soundBomb->SetMuted(false);
				soundGameOver->SetMuted(false);
			}
			else {
				isMutedSoundEffect = true;
				soundPoint->SetMuted(true);
				soundBomb->SetMuted(true);
				soundGameOver->SetMuted(true);
			}

		}
		else if ("music" == b->GetButtonName()) {
			if (isMuted) {
				isMuted = false;
				music->Play(true);
			}
			else {
				isMuted = true;
				music->Stop();
			}
		}
		else if ("exit" == b->GetButtonName()) {
			state = Engine::State::EXIT;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		if (b->GetButtonName() == "music") {
			if (isMuted && b->GetButtonName() == "music") {
				if (b->GetButtonState() == ButtonState::HOVER || b->GetButtonState() == ButtonState::MUTEHOVER) {
					b->SetButtonState(ButtonState::MUTEHOVER);
				}
				else {
					b->SetButtonState(ButtonState::MUTE);
				}
			}
			else {
				if (b->GetButtonState() == ButtonState::PRESS) {
					b->SetButtonState(ButtonState::PRESS);
				}
				else if (b->GetButtonState() == ButtonState::HOVER || b->GetButtonState() == ButtonState::MUTEHOVER) {
					b->SetButtonState(ButtonState::HOVER);
				}
				else if (b->GetButtonState() == ButtonState::NORMAL) {
					b->SetButtonState(ButtonState::NORMAL);
				}
			}
		}

		else if (b->GetButtonName() == "sound") {
			if (isMutedSoundEffect && b->GetButtonName() == "sound") {
				if (b->GetButtonState() == ButtonState::HOVER || b->GetButtonState() == ButtonState::MUTEHOVER) {
					b->SetButtonState(ButtonState::MUTEHOVER);
				}
				else {
					b->SetButtonState(ButtonState::MUTE);
				}
			}
			else {
				if (b->GetButtonState() == ButtonState::PRESS) {
					b->SetButtonState(ButtonState::PRESS);
				}
				else if (b->GetButtonState() == ButtonState::HOVER || b->GetButtonState() == ButtonState::MUTEHOVER) {
					b->SetButtonState(ButtonState::HOVER);
				}
				else if (b->GetButtonState() == ButtonState::NORMAL) {
					b->SetButtonState(ButtonState::NORMAL);
				}
			}
		}
		b->Update(GetGameTime());
	}


}

void Source::RenderMainMenu()
{
	backgroundMainSprite->Draw();
	monkeySprite->Draw();
	fruitBasketSprite->Draw();
	fruit1MainSprite->Draw();
	fruit2MainSprite->Draw();
	fruit3MainSprite->Draw();
	titleImageSprite->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}

	// Render all Text 
	mainMenu1->Draw();
	mainMenu2->Draw();
	highScoreText->Draw();
}

void Source::InitInGame()
{
	//Create background
	Texture* bgTexture = new Texture("forest.png");
	backgroundSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Create basket
	Texture* basketTexture = new Texture("basket.png");
	basketSprite = new Sprite(basketTexture, defaultSpriteShader, defaultQuad);
	basketSprite->SetPosition(0, 0);
	basketSprite->SetScale(0.42f);

	basketSprite->SetBoundingBoxSize(basketSprite->GetScaleWidth() - (16 * basketSprite->GetScale()),
		basketSprite->GetScaleHeight() - (4 * basketSprite->GetScale()));

	// Add input mapping 
	inputManager->AddInputMapping("Move Right", SDLK_RIGHT);
	inputManager->AddInputMapping("Move Left", SDLK_LEFT);
	inputManager->AddInputMapping("Main Menu", SDLK_ESCAPE);

	// Text Guide Game
	text = new Text("HitandRun-Regular.otf", 28, defaultTextShader);
	text->SetScale(1.0f);
	text->SetColor(255, 232, 54);
	text->SetPosition(setting->screenWidth - 1265, setting->screenHeight - 40);

	// Text Score
	scoreText = new Text("HitandRun-Regular.otf", 30, defaultTextShader);
	scoreText->SetScale(1.0f);
	scoreText->SetColor(255, 236, 87);
	scoreText->SetPosition(setting->screenWidth - 225, setting->screenHeight - 45);

	// Text Timer
	time = new Text("HitandRun-Regular.otf", 30, defaultTextShader);
	time->SetScale(1.0f);
	time->SetColor(255, 236, 87);
	time->SetPosition(setting->screenWidth - 225, setting->screenHeight - 90);

	// Spawn setting
	maxSpawnTime = 1000;
	numObjectPerSpawn = 4;
	numObjectsInPool = 20;

	// Create Texture Fruit and Bomb
	Texture* avocadoTexture = new Texture("avocado.png");
	Texture* blueberryTexture = new Texture("blueberry.png");
	Texture* strawberryTexture = new Texture("strawberry.png");
	Texture* coconutTexture = new Texture("coconut.png");
	Texture* bananaTexture = new Texture("banana.png");
	Texture* bomTexture = new Texture("bom.png");


	for (int i = 0; i < numObjectsInPool; i++) {
		// Load a texture Avocado
		Sprite* avocadoSprite = new Sprite(avocadoTexture, defaultSpriteShader, defaultQuad);
		avocadoSprite->SetScale(3.3);
		avocadoSprite->SetAnimationDuration(150);
		avocadoSprite->SetPosition(-1000, -1000);

		avocadoSprite->SetScore(10);

		GameObject* o = new GameObject(avocadoSprite);
		objects.push_back(o);

		avocadoSprite->SetBoundingBoxSize(avocadoSprite->GetScaleWidth() - (18 * avocadoSprite->GetScale()),
			avocadoSprite->GetScaleHeight());
		fruits.push_back(avocadoSprite);


		// Load a texture Blueberry
		Sprite* blueberrySprite = new Sprite(blueberryTexture, defaultSpriteShader, defaultQuad);
		blueberrySprite->SetScale(3.3);
		blueberrySprite->SetAnimationDuration(150);
		blueberrySprite->SetPosition(-1000, -1000);

		blueberrySprite->SetScore(15);

		o = new GameObject(blueberrySprite);
		objects.push_back(o);

		blueberrySprite->SetBoundingBoxSize(blueberrySprite->GetScaleWidth() - (18 * blueberrySprite->GetScale()),
			blueberrySprite->GetScaleHeight());
		fruits.push_back(blueberrySprite);


		// Load a texture Strawberry
		Sprite* strawberrySprite = new Sprite(strawberryTexture, defaultSpriteShader, defaultQuad);
		strawberrySprite->SetScale(3.3);
		strawberrySprite->SetAnimationDuration(150);
		strawberrySprite->SetPosition(-1000, -1000);

		strawberrySprite->SetScore(20);

		o = new GameObject(strawberrySprite);
		objects.push_back(o);

		strawberrySprite->SetBoundingBoxSize(strawberrySprite->GetScaleWidth() - (18 * strawberrySprite->GetScale()),
			strawberrySprite->GetScaleHeight());
		fruits.push_back(strawberrySprite);


		// Load a texture Coconut
		Sprite* coconutSprite = new Sprite(coconutTexture, defaultSpriteShader, defaultQuad);
		coconutSprite->SetScale(3.3);
		coconutSprite->SetAnimationDuration(150);
		coconutSprite->SetPosition(-1000, -1000);

		coconutSprite->SetScore(25);

		o = new GameObject(coconutSprite);
		objects.push_back(o);

		coconutSprite->SetBoundingBoxSize(coconutSprite->GetScaleWidth() - (18 * coconutSprite->GetScale()),
			coconutSprite->GetScaleHeight());
		fruits.push_back(coconutSprite);


		// Load a texture Banana
		Sprite* bananaSprite = new Sprite(bananaTexture, defaultSpriteShader, defaultQuad);
		bananaSprite->SetScale(3.3);
		bananaSprite->SetAnimationDuration(150);
		bananaSprite->SetPosition(-1000, -1000);

		bananaSprite->SetScore(50);

		o = new GameObject(bananaSprite);
		objects.push_back(o);

		bananaSprite->SetBoundingBoxSize(bananaSprite->GetScaleWidth() - (18 * bananaSprite->GetScale()),
			bananaSprite->GetScaleHeight());
		fruits.push_back(bananaSprite);


		// Load a texture Bomb
		Sprite* bomSprite = new Sprite(bomTexture, defaultSpriteShader, defaultQuad);
		bomSprite->SetScale(0.12f);
		bomSprite->AddAnimation("spikes", 0, 0);
		bomSprite->PlayAnim("spikes");
		bomSprite->SetAnimationDuration(150);
		bomSprite->SetPosition(-1000, -1000);

		bomSprite->SetScore(-10);

		o = new GameObject(bomSprite);
		objects.push_back(o);

		bomSprite->SetBoundingBoxSize(bomSprite->GetScaleWidth() - (18 * bomSprite->GetScale()),
			bomSprite->GetScaleHeight());
		bombs.push_back(bomSprite);
	}

	// Create image fruit and bomb
	imageAvocadoSprite = new Sprite(avocadoTexture, defaultSpriteShader, defaultQuad);
	imageAvocadoSprite->SetScale(2.2);
	imageAvocadoSprite->SetPosition(10, setting->screenHeight - 95);

	imageBlueberrySprite = new Sprite(blueberryTexture, defaultSpriteShader, defaultQuad);
	imageBlueberrySprite->SetScale(2.2);
	imageBlueberrySprite->SetPosition(100, setting->screenHeight - 95);

	imageStrawberrySprite = new Sprite(strawberryTexture, defaultSpriteShader, defaultQuad);
	imageStrawberrySprite->SetScale(2.2);
	imageStrawberrySprite->SetPosition(187, setting->screenHeight - 95);

	imageCoconutSprite = new Sprite(coconutTexture, defaultSpriteShader, defaultQuad);
	imageCoconutSprite->SetScale(2.2);
	imageCoconutSprite->SetPosition(280, setting->screenHeight - 95);

	imageBananaSprite = new Sprite(bananaTexture, defaultSpriteShader, defaultQuad);
	imageBananaSprite->SetScale(2.2);
	imageBananaSprite->SetPosition(372, setting->screenHeight - 95);
	
	imageBomb1Sprite = new Sprite(bomTexture, defaultSpriteShader, defaultQuad);
	imageBomb1Sprite->SetScale(0.08);
	imageBomb1Sprite->SetPosition(10, setting->screenHeight - 150);

	imageBomb2Sprite = new Sprite(bomTexture, defaultSpriteShader, defaultQuad);
	imageBomb2Sprite->SetScale(0.08);
	imageBomb2Sprite->SetPosition(113, setting->screenHeight - 150);


	// Text Poin Fruit Object Game
	textPointFruitObject = new Text("HitandRun-Regular.otf", 20, defaultTextShader);
	textPointFruitObject->SetScale(1.0f);
	textPointFruitObject->SetColor(255, 255, 255);
	textPointFruitObject->SetPosition(47, setting->screenHeight - 87);
	textPointFruitObject->SetText("+10        +15         +20         +25        +50");

	// Text Poin Bomb Object Game
	textPointBombObject = new Text("HitandRun-Regular.otf", 20, defaultTextShader);
	textPointBombObject->SetScale(1.0f);
	textPointBombObject->SetColor(255, 0, 0);
	textPointBombObject->SetPosition(47, setting->screenHeight - 142);
	textPointBombObject->SetText("-10          3x : \"LOSE\"");

	// Sound Effect jika mendapat poin
	soundPoint = new Sound("point.wav");
	soundPoint->SetVolume(40);

	// Sound Effect jika mendapat bomb
	soundBomb = new Sound("bombhit.wav");
	soundBomb->SetVolume(100);

	// Sound Effect jika Game Over dengan mengenai bomb sebanyak 3 kali
	soundGameOver = new Sound("gameover.wav");
	soundGameOver->SetVolume(100);

	// Deklarasi nilai bomHits
	bomHits = 0;

}

void Source::UpdateInGame()
{
	// Cek timer
	if (timer <= 0) {
		// Timer habis akan ke END_GAME
		screenState = ScreenState::END_GAME;
		return;
	}

	// Update timer
	timer -= 0.01635f;

	currentFrameFruit++;
	currentFrameBomb++;

	// Peningkatan kecepatan buah setelah periode tertentu
	if (currentFrameFruit % fruitSpeedIncrementPeriod == 0) {
		fruitSpeed += fruitSpeedIncrement;
	}

	// Peningkatan kecepatan bomb setelah periode tertentu
	if (currentFrameBomb % bombSpeedIncrementPeriod == 0) {
		bombSpeed += bombSpeedIncrement;
	}

	// If user press "Quit" key then exit
	if (inputManager->IsKeyReleased("Main Menu")) {
		screenState = ScreenState::MAIN_MENU;
		ResetGame();
		return;
	}

	text->SetText("PRESS Key Right-Left to Move");

	basketSprite->PlayAnim("idle");

	// Move basket sprite using keyboard
	vec2 basketPos = basketSprite->GetPosition();
	float basketWidth = basketSprite->GetScaleWidth();

	float x = basketPos.x, y = basketPos.y;
	if (inputManager->IsKeyPressed("Move Right") && basketPos.x + basketWidth <= setting->screenWidth) {
		basketSprite->PlayAnim("run");
		x += 0.3f * GetGameTime();
		basketSprite->SetFlipHorizontal(false);
	}

	if (inputManager->IsKeyPressed("Move Left") && basketPos.x >= 0) {
		basketSprite->PlayAnim("run");
		x -= 0.3f * GetGameTime();
		basketSprite->SetFlipHorizontal(true);
	}

	basketSprite->SetPosition(x, y);

	// Update basket sprite animation
	basketSprite->Update(GetGameTime());

	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}

	// Count spawn duration
	spawnDuration += GetGameTime();

	// Update all objects
	for (GameObject* o : objects) {
		o->Update(GetGameTime());
	}

	// Update all objects
	bool isPointSoundPlaying = soundPoint->IsPlaying(); 
	bool isBombSoundPlaying = soundBomb->IsPlaying(); 

	for (Sprite* fruit : fruits) {
		fruit->SetPosition(fruit->GetPosition().x, fruit->GetPosition().y - fruitSpeed);
			
		if (fruit->GetBoundingBox()->CollideWith(basketSprite->GetBoundingBox()) && fruit->GetPosition().y > basketSprite->GetPosition().y + (basketSprite->GetScaleHeight() / 2)) {
			if (!isPointSoundPlaying) { 
				soundPoint->Stop(); 
				soundPoint->Play(false); 
				isPointSoundPlaying = true;
			}

			int fruitScore = fruit->GetScore();
			totalScore += fruitScore;

			fruit->SetPosition(-1000, -1000); // Mengatur posisi buah di luar layar agar tidak terlihat lagi
			
			// Menghentikan iterasi setelah menambahkan skor ke keranjang
			break;
		}

	}

	for (Sprite* bomb : bombs) {
		bomb->SetPosition(bomb->GetPosition().x, bomb->GetPosition().y - bombSpeed);

		if (bomb->GetBoundingBox()->CollideWith(basketSprite->GetBoundingBox()) && bomb->GetPosition().y > basketSprite->GetPosition().y + (basketSprite->GetScaleHeight() / 2)) {
			bomHits++;

			if (!isBombSoundPlaying) {
				soundBomb->Stop(); 
				soundBomb->Play(false); 
				isBombSoundPlaying = true; 
			}
			
			int bombScore = bomb->GetScore();
			totalScore += bombScore;

			bomb->SetPosition(-1000, -1000); // Mengatur posisi buah di luar layar agar tidak terlihat lagi


			// Cek apakah pemain sudah mengenai bom sebanyak 3 kali
			if (bomHits >= 3) {
				screenState = ScreenState::END_GAME;
				soundGameOver->Play(false);
			}

			// Menghentikan iterasi setelah menambahkan skor ke keranjang
			break;
		}
	}
}

void Source::RenderInGame()
{
	backgroundSprite->Draw();
	imageAvocadoSprite->Draw();
	imageBlueberrySprite->Draw();
	imageStrawberrySprite->Draw();
	imageCoconutSprite->Draw();
	imageBananaSprite->Draw();
	imageBomb1Sprite->Draw();
	imageBomb2Sprite->Draw();

	// Render all Text
	text->Draw();
	textPointFruitObject->Draw();
	textPointBombObject->Draw();
	scoreText->SetText("Score : " + to_string(totalScore));
	scoreText->Draw();


	// Convert the timer value to string and display it in the text object
	int timeInt = static_cast<int>(timer);
	time->SetText("Timer : " + std::to_string(timeInt) + " s");
	time->Draw();

	// Render all objects
	for (Sprite* fruit : fruits) {
		fruit->Draw();
	}

	for (Sprite* bomb : bombs) {
		bomb->Draw();
	}

	basketSprite->Draw();
}

void Source::InitEndGame()
{
	//Create Background
	Texture* bgEndTexture = new Texture("bg.png");
	backgroundEndSprite = new Sprite(bgEndTexture, defaultSpriteShader, defaultQuad);
	backgroundEndSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Create a Button
	Texture* buttonTexture = new Texture("btn.png");
	
	// Create Button Play Again Sprites
	Sprite* playAgainSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	playAgainSprite->SetNumXFrames(5);
	playAgainSprite->SetNumYFrames(4);
	playAgainSprite->AddAnimation("normal", 10, 10);
	playAgainSprite->AddAnimation("hover", 7, 7);
	playAgainSprite->AddAnimation("press", 7, 7);
	playAgainSprite->SetScale(1.15);
	playAgainSprite->SetAnimationDuration(400);

	// Create Button Home Sprites
	homeSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	homeSprite->SetNumXFrames(5);
	homeSprite->SetNumYFrames(4);
	homeSprite->AddAnimation("normal", 6, 6);
	homeSprite->AddAnimation("hover", 5, 5);
	homeSprite->AddAnimation("press", 5, 5);
	homeSprite->SetScale(0.4);
	homeSprite->SetAnimationDuration(400);

	// Create Button Exit Sprites
	Sprite* exitSprite = new Sprite(buttonTexture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(5);
	exitSprite->SetNumYFrames(4);
	exitSprite->AddAnimation("normal", 2, 2);
	exitSprite->AddAnimation("hover", 1, 1);
	exitSprite->AddAnimation("press", 1, 1);
	exitSprite->SetScale(0.4);
	exitSprite->SetAnimationDuration(400);

	
	Button* playAgainButton = new Button(playAgainSprite, "playAgain");
	playAgainButton->SetPosition((setting->screenWidth / 2) - (playAgainSprite->GetScaleWidth() / 2),
		135);
	buttonsEndGame.push_back(playAgainButton);

	Button* homeButton = new Button(homeSprite, "home");
	homeButton->SetPosition((setting->screenWidth / 1.2) - (homeSprite->GetScaleWidth() / 1.15),
		25);
	buttonsEndGame.push_back(homeButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((setting->screenWidth / 1.05) - (exitSprite->GetScaleWidth() / 1.05),
		25);
	buttonsEndGame.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::HOVER);

	// Create Text End Score
	endGameScore = new Text("Bangers-Regular.ttf", 72, defaultTextShader);
	endGameScore->SetPosition(setting->screenWidth - 785, setting->screenHeight - 220);
	endGameScore->SetColor(255, 232, 54);

	// Create Text High Score
	highScoreTextEnd = new Text("HitandRun-Regular.otf", 40, defaultTextShader);
	highScoreTextEnd->SetPosition(60, setting->screenHeight - 650);
	highScoreTextEnd->SetColor(255, 236, 87);
	highScoreTextEnd->SetText("High Score : " + std::to_string(LoadHighScore()));

	// Sprite Game Over Text Image
	Texture* gameOverTexture = new Texture("gameOver.png");
	gameOverSprite = new Sprite(gameOverTexture, defaultSpriteShader, defaultQuad);
	gameOverSprite->SetPosition(setting->screenWidth - 975, setting->screenHeight - 363);
	gameOverSprite->SetScale(0.65f);

	// Add input mappings
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("press", SDLK_RETURN); //tombol enter
}

void Source::UpdateEndGame()
{
	bomHits = 0;

	// Update text
	endGameScore->SetText("Score : " + std::to_string(totalScore));

	// Update High Score
	int currentScore = totalScore;
	int highScore = LoadHighScore();
	if (currentScore > highScore) {
		highScore = currentScore;
		SaveHighScore(highScore);
	}

	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttonsEndGame.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex; //ternary operator
		// Set current button to hover state
		buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttonsEndGame[currentButtonIndex]->SetButtonState(ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttonsEndGame[currentButtonIndex];
		b->SetButtonState(ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("playAgain" == b->GetButtonName()) {
			fruitSpeed = 1.5f;
			bombSpeed = 1.5f;
			ResetGame();
			screenState = ScreenState::IN_GAME;
			//SpawnObjects(); // Memanggil metode SpawnObjects()
			isGameOverSoundPlaying = false;
			return;
		}
		else if ("home" == b->GetButtonName()) {
			// Set previous button to normal state
			buttons[currentButtonIndex]->SetButtonState(ButtonState::NORMAL);
			// Set current button index to the index of the play button
			currentButtonIndex = 0;
			// Set play button to hover state
			buttons[currentButtonIndex]->SetButtonState(ButtonState::HOVER);

			screenState = ScreenState::MAIN_MENU;
			ResetGame();
			
		}
		else if ("exit" == b->GetButtonName()) {
			state = Engine::State::EXIT;
		}
	}

	if (!isGameOverSoundPlaying) {
		soundGameOver->Play(isSoundOnGameOver);
		isGameOverSoundPlaying = true;
	}

	// Update All buttons
	for (Button* b : buttonsEndGame) {
		b->Update(GetGameTime());
	}

	// Update Text High Score
	highScoreText->SetText("High Score : " + std::to_string(highScore));
}

void Source::RenderEndGame()
{
	backgroundEndSprite->Draw();
	gameOverSprite->Draw();

	// Render all buttons
	for (Button* b : buttonsEndGame) {
		b->Draw();
	}

	if (!isBombSoundPlaying) { 
		soundBomb->Play(false); 
		isBombSoundPlaying = true; 
	}

	// Render all Text 
	endGameScore->Draw();
	highScoreTextEnd->Draw();
}

void Source::SpawnObjects()
{
	int numRows = 4; // Jumlah baris dalam grid
	int numCols = 4; // Jumlah kolom dalam grid
	float spacingX = 200.0f; // Jarak horizontal antara kolom
	float spacingY = 20.0f; // Jarak vertikal antara baris
	float startX = (1300 - (numCols * spacingX)) / 2; // Koordinat X awal
	float startY = setting->screenHeight + objects[0]->GetHeight(); // Koordinat Y awal

	int spawnCount = 0;

	// Find Die object to reuse for spawning
	for (GameObject* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();

			// Calculate row and column index
			int row = spawnCount / numCols;
			int col = spawnCount % numCols;

			// Calculate the position based on row and column index
			float x = startX + (col * spacingX);
			float y = startY - (row * spacingY);

			// Add random variation to the position
			float variationX = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0f));
			float variationY = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0f));
			x += variationX;
			y += variationY;

			o->SetPosition(x, y);
			spawnCount++;
		}
	}
}

void Source::ResetGame() {
	// Reset game variables
	totalScore = 0;
	timer = endGameDuration;

	// Reset object positions
	for (GameObject* obj : objects) {
		obj->SetPosition(-1000, -1000); // Set object position off-screen
		obj->SetActive(true); // Activate the object
	}

	// Reset fruit positions
	for (Sprite* fruit : fruits) {
		fruit->SetPosition(-1000, -1000); // Set fruit position off-screen
	}

	// Reset bomb positions
	for (Sprite* bomb : bombs) {
		bomb->SetPosition(-1000, -1000); // Set bomb position off-screen
	}

	// Set the basket's initial position
	basketSprite->SetPosition(0, 0);

	// Set the basket's animation to idle
	basketSprite->PlayAnim("idle");

	// Reset spawn settings
	spawnTimer = 0;
	maxSpawnTime = 1000;
	numObjectPerSpawn = 4;
	fruitSpeed = 1.5f;
	bombSpeed = 1.5f;

	// Reset game over flag
	isGameOver = false;
}

int Source::LoadHighScore()
{
	std::ifstream inputFile("highscore.txt");
	if (inputFile.is_open()) {
		inputFile >> highScore;
		inputFile.close();
	}
	return highScore;
}

void Source::SaveHighScore(int highScore)
{
	std::ofstream outputFile("highscore.txt");
	if (outputFile.is_open()) {
		outputFile << highScore;
		outputFile.close();
	}
}

int main(int argc, char** argv) {
	Setting* setting = new Setting();
	setting->windowTitle = "Fruit Grab";
	setting->screenWidth = 1280;
	setting->screenHeight = 720;
	setting->windowFlag = WindowFlag::FULLSCREEN;
	setting->vsync = true;
	Game* game = new Source(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}

