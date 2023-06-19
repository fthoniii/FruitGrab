#include "Button.h"

Engine::Button::Button(Sprite* sprite, string name)
{
	state = Engine::ButtonState::NORMAL;
	this->sprite = sprite;
	this->name = name;
}

Engine::Button::~Button()
{
	delete sprite;
	sprite = NULL;
}

void Engine::Button::Update(float deltaTime)
{
	if (Engine::ButtonState::NORMAL == state) { //jika button state normal
		sprite->PlayAnim("normal"); //tampilkan animasi normal
	}
	else if (Engine::ButtonState::HOVER == state) {
		sprite->PlayAnim("hover");
	}
	else if (Engine::ButtonState::PRESS == state) {
		sprite->PlayAnim("press");
	}
	else if (Engine::ButtonState::MUTE == state) {
		sprite->PlayAnim("mute");
	}
	else if (Engine::ButtonState::MUTEHOVER == state) {
		sprite->PlayAnim("muteHover");
	}

	sprite->Update(deltaTime);
}

void Engine::Button::Draw()
{
	sprite->Draw();
}

void Engine::Button::SetPosition(float x, float y)
{
	sprite->SetPosition(x, y);
}

Engine::ButtonState Engine::Button::GetButtonState()
{
	return state;
}

void Engine::Button::SetButtonState(ButtonState state)
{
	this->state = state;
}

string Engine::Button::GetButtonName()
{
	return name;
}

vec2 Engine::Button::GetPosition()
{
	return sprite->GetPosition();
}
