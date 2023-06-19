#include "GameObject.h"

Engine::GameObject::GameObject(Sprite* sprite)
{
	this->sprite = sprite;
	state = Engine::GameObjectState::DIE;
	groundDur = 0;
	groundTime = 3000;
}

Engine::GameObject::~GameObject()
{
	
}

void Engine::GameObject::Update(float deltaTime)
{
	if (state == Engine::GameObjectState::DIE) {
		return;
	}

	float x = GetX();
	float y = GetY();
	float yVelocity = 0.07;

	if (Engine::GameObjectState::SPAWN == state && y <= 0) {
		state = Engine::GameObjectState::GROUND;
	}

	if (state == Engine::GameObjectState::GROUND) {
		yVelocity = 0;
		if (groundDur >= groundTime) {
			state = Engine::GameObjectState::DIE;
			groundDur = 0;
		}
		groundDur += deltaTime;
	}

	y -= yVelocity * deltaTime;
	sprite->SetPosition(x, y);
	sprite->Update(deltaTime);
}

void Engine::GameObject::Draw()
{
	if (state == Engine::GameObjectState::DIE) {
		return;
	}

	sprite->Draw();
}



void Engine::GameObject::SetPosition(float x, float y)
{
    sprite->SetPosition(x, y);
}

void Engine::GameObject::SetSpawn()
{
	this->state = Engine::GameObjectState::SPAWN;
}

float Engine::GameObject::GetWidth()
{
	return sprite->GetScaleWidth();
}

float Engine::GameObject::GetHeight()
{
	return sprite->GetScaleHeight();
}

bool Engine::GameObject::IsDie()
{
	return Engine::GameObjectState::DIE == state;
}

float Engine::GameObject::GetX()
{
	return sprite->GetPosition().x;
}

float Engine::GameObject::GetY()
{
	return sprite->GetPosition().y;
}

bool Engine::GameObject::IsTaken()  {
	return taken;
}

void Engine::GameObject::SetTaken(bool isTaken) {
	taken = isTaken;
}

void Engine::GameObject::SetActive(bool isActive) {
	active = isActive;
}

bool Engine::GameObject::IsAlive() {
	return active;
}

float Engine::GameObject::GetSpeed() {
	return speed; // Mengembalikan nilai dari variabel speed
	return speed; // Mengembalikan nilai dari variabel speed
}

void Engine::GameObject::SetSpeed(float newSpeed) {
	speed = newSpeed; // Mengatur nilai variabel speed dengan nilai baru yang diberikan
}



