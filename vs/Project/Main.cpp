#include "Main.h"

Engine::Main::Main(Setting* setting) :Engine::Game(setting)
{
	// Set to mainmenu
	screenState = Engine::ScreenState::MAIN_MENU;
	text = nullptr;
}

Engine::Main::~Main()
{
	delete music;
	delete texture;
}

void Engine::Main::Init()
{
	InitMainMenu();
	InitInGame();
	InitMusic();
	//InitNoSound();
}

void Engine::Main::Update()
{

	if (Engine::ScreenState::MAIN_MENU == screenState) {
		UpdateMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		UpdateInGame();
	}
	else if (Engine::ScreenState::NO_SOUND == screenState) {
		UpdateNoSound();
	}
}

void Engine::Main::Render()
{
	if (Engine::ScreenState::MAIN_MENU == screenState) {
		RenderMainMenu();
	}
	else if (Engine::ScreenState::IN_GAME == screenState) {
		RenderInGame();
	}
	else if (Engine::ScreenState::NO_SOUND == screenState) {
		RenderNoSound();
	}
}

void Engine::Main::InitMainMenu()
{
	// Create a Texture
	Texture* texture = new Texture("btn.png");

	// Create Sprites
	Sprite* playSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	playSprite->SetNumXFrames(4);
	playSprite->SetNumYFrames(3);
	playSprite->AddAnimation("normal", 6, 6);
	playSprite->AddAnimation("hover", 5, 5);
	playSprite->AddAnimation("press", 5, 5);
	playSprite->SetScale(0.9);
	playSprite->SetAnimationDuration(400);

	Sprite* exitSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	exitSprite->SetNumXFrames(4);
	exitSprite->SetNumYFrames(3);
	exitSprite->AddAnimation("normal", 1, 1);
	exitSprite->AddAnimation("hover", 0, 0);
	exitSprite->AddAnimation("press", 0, 0);
	exitSprite->SetScale(0.2);
	exitSprite->SetAnimationDuration(400);

	Sprite* soundSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	soundSprite->SetNumXFrames(4);
	soundSprite->SetNumYFrames(3);
	soundSprite->AddAnimation("normal", 3, 3);
	soundSprite->AddAnimation("hover", 10, 10);
	soundSprite->AddAnimation("press", 10, 10);
	soundSprite->SetScale(0.2);
	soundSprite->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((setting->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		170);
	buttons.push_back(playButton);
	Button* soundButton = new Button(soundSprite, "sound");
	soundButton->SetPosition((setting->screenWidth / 1.15) - (soundSprite->GetScaleWidth() / 1.15),
		25);
	buttons.push_back(soundButton);
	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((setting->screenWidth / 1.05) - (exitSprite->GetScaleWidth() / 1.05),
		25);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = new Text("Bangers-Regular.ttf", 100, defaultTextShader);
	text->SetText("Fruit Grab");
	text->SetPosition(250, setting->screenHeight - 120);
	text->SetColor(235, 214, 52);

	// Add input mappings
	inputManager->AddInputMapping("next", SDLK_DOWN);
	inputManager->AddInputMapping("prev", SDLK_UP);
	inputManager->AddInputMapping("next", SDLK_RIGHT);
	inputManager->AddInputMapping("prev", SDLK_LEFT);
	inputManager->AddInputMapping("press", SDLK_RETURN); //tombol enter

}

void Engine::Main::InitInGame()
{
	Texture* basketTexture = new Texture("basket.png");

	basketSprite = new Sprite(basketTexture, defaultSpriteShader, defaultQuad);
	basketSprite->SetNumXFrames(1);
	basketSprite->SetNumYFrames(1);
	//basketSprite->AddAnimation("walk", 0, 0);
	basketSprite->SetScale(0.3f);
	basketSprite->SetPosition(0, 0);

	//basketSprite->PlayAnim("walk");
	//basketSprite->SetAnimationDuration(100);

	basketSprite->SetBoundingBoxSize(basketSprite->GetScaleWidth() - (16 * basketSprite->GetScale()),
		basketSprite->GetScaleHeight() - (4 * basketSprite->GetScale()));

	// Add input mappings
	inputManager->AddInputMapping("Run Right", SDLK_RIGHT);
	inputManager->AddInputMapping("Run Left", SDLK_LEFT);
	inputManager->AddInputMapping("Jump", SDLK_UP);
	inputManager->AddInputMapping("Attack", SDLK_x);
	inputManager->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	inputManager->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	inputManager->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A);
	inputManager->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X);
	inputManager->AddInputMapping("Quit", SDLK_ESCAPE);
	inputManager->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y);
	inputManager->AddInputMapping("walk-left", SDLK_LEFT);
	inputManager->AddInputMapping("walk-right", SDLK_RIGHT); //keyboard sebelah kanan
	inputManager->AddInputMapping("mainmenu", SDLK_ESCAPE); //kembali ke main menu


	// Spawn setting
	maxSpawnTime = 300;
	numObjectPerSpawn = 1;
	numObjectsInPool = 30;

	// Load a texture
	Texture* fruitTexture = new Texture("fruits.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		GameObject* o = new GameObject(CreateSprite(fruitTexture));
		objects.push_back(o);
	}

	debug = true;
	
}

void Engine::Main::InitNoSound()
{
	// Create a Texture
	Texture* texture = new Texture("btn.png");

	Sprite* NoSoundSprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
	NoSoundSprite->SetNumXFrames(4);
	NoSoundSprite->SetNumYFrames(3);
	NoSoundSprite->AddAnimation("normal", 9, 9);
	NoSoundSprite->AddAnimation("hover", 8, 8);
	NoSoundSprite->AddAnimation("press", 8, 8);
	NoSoundSprite->SetScale(0.2);
	NoSoundSprite->SetAnimationDuration(400);

	Button* NoSoundButton = new Button(NoSoundSprite, "NoSound");
	NoSoundButton->SetPosition((setting->screenWidth / 1.25) - (NoSoundSprite->GetScaleWidth() / 1.25),
		25);
	buttons.push_back(NoSoundButton);
}

void Engine::Main::InitMusic() {
	// Playing music
	music = new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg");
	music->SetVolume(40); //background music volume nya harus lebih rendah dari sound effect agar tidak mengganggu
	music->Play(true);

	//sound = new Sound("jump.wav");
	//sound->SetVolume(100);
}

void Engine::Main::RenderMainMenu()
{

	backgroundSprite->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}

void Engine::Main::RenderInGame()
{
	backgroundSprite->Draw();

	// Render all objects
	for (GameObject* o : objects) {
		o->Draw();
	}
	basketSprite->Draw();

	

}

void Engine::Main::RenderNoSound()
{
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
}

void Engine::Main::UpdateMainMenu() //logic untuk main menu
{	Texture* texture = new Texture("btn.png");

	//Create background
	Texture* bgTexture = new Texture("test.png");
	backgroundSprite = new Sprite(bgTexture, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetSize(setting->screenWidth, setting->screenHeight);
	
	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex; //ternary operator
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}


	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
		else if ("sound" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
		else if ("exit" == b->GetButtonName()) {
			state = Engine::State::EXIT;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(GetGameTime());
	}
}

void Engine::Main::UpdateInGame()
{
	

	// Back to main menu
	if (inputManager->IsKeyReleased("mainmenu")) {
		screenState = Engine::ScreenState::MAIN_MENU;
		return;
	}

	//basketSprite->Update(GetGameTime());

	//float x = basketSprite->GetPosition().x;
	//float y = basketSprite->GetPosition().y;
	//float velocity = 0.07f;
	//if (inputManager->IsKeyPressed("walk-right")) {
	//	x += velocity * GetGameTime(); // velocity adalah kecepatan
	//	basketSprite->SetFlipHorizontal(false);
	//	basketSprite->PlayAnim("walk"); //memainkan animasi berjalan
	//}
	//if (inputManager->IsKeyPressed("walk-left")) {
	//	x -= velocity * GetGameTime();
	//	basketSprite->SetFlipHorizontal(true);
	//	basketSprite->PlayAnim("walk");
	//}

	//basketSprite->SetPosition(x, y);

	vec2 basket = basketSprite->GetPosition();
	float x = basket.x, y = basket.y;
	if (inputManager->IsKeyPressed("Run Right")) {
		basketSprite->PlayAnim("run");
		x += 5.0f * GetGameTime();
		basketSprite->SetFlipHorizontal(false);
	}

	if (inputManager->IsKeyPressed("Run Left")) {
		basketSprite->PlayAnim("run");
		x -= 0.2f * GetGameTime();
		basketSprite->SetFlipHorizontal(true);
	}
	
	y += yVelocity * GetGameTime();
	basketSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(basketSprite->GetBoundingBox())) {
			//revert x position if collided
			x = basket.x;
			basketSprite->SetPosition(x, y);

			yVelocity = 0;
			jump = false;
			break;
		}
	}

	basketSprite->Update(GetGameTime());


	// Set background
	Texture* bgTextureInGame = new Texture("forest.png");
	backgroundSprite = new Sprite(bgTextureInGame, defaultSpriteShader, defaultQuad);
	backgroundSprite->SetSize(setting->screenWidth, setting->screenHeight);

	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (GameObject* o : objects) {
		o->Update(GetGameTime());
	}
	// Count spawn duration
	spawnDuration += GetGameTime();


}

void Engine::Main::UpdateNoSound()
{
	Texture* texture = new Texture("btn.png");
	if (inputManager->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = currentButtonIndex < buttons.size() - 1 ? currentButtonIndex + 1 : currentButtonIndex; //ternary operator
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (inputManager->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}


	if (inputManager->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("NoSound" == b->GetButtonName()) {
			screenState = Engine::ScreenState::IN_GAME;
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(GetGameTime());
	}
}

Engine::Sprite* Engine::Main::CreateSprite(Texture* texture)
{
	Sprite* sprite = new Sprite(texture,
		defaultSpriteShader,
		defaultQuad);
	sprite->SetNumXFrames(5);
	sprite->SetNumYFrames(3);
	sprite->AddAnimation("hit", 0, 2);
	sprite->AddAnimation("spikes", 3, 4);
	sprite->AddAnimation("idle-1", 5, 6);
	sprite->AddAnimation("idle-2", 7, 8);
	sprite->AddAnimation("spikes-out", 9, 14);
	sprite->PlayAnim("spikes");
	sprite->SetScale(3);
	sprite->SetAnimationDuration(150);

	return sprite;
}

void Engine::Main::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (GameObject* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn
			o->SetSpawn();
			// Random spawn position
			int min = 0;
			int max = setting->screenWidth - o->GetWidth();
			float x = rand() % (max - min + 1) + min;
			float y = setting->screenHeight + o->GetHeight();
			o->SetPosition(x, y);
			spawnCount++;
		}
	}
}


//int main(int argc, char** argv) {
//	Engine::Setting* setting = new Engine::Setting();
//	setting->windowTitle = "GUI Demo";
//	setting->screenWidth = 900;
//	setting->screenHeight = 600;
//	setting->windowFlag = Engine::WindowFlag::WINDOWED;
//	setting->vsync = false;
//	setting->targetFrameRate = 0;
//	Engine::Game* game = new Engine::Main(setting);
//	game->Run();
//	delete setting;
//	delete game;
//
//	return 0;
//}

