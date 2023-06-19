#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Sprite.h"

namespace Engine {
	enum class GameObjectState {
		SPAWN,
		GROUND,
		DIE
	};
	class GameObject
	{
	public:
		GameObject(Sprite* sprite);
		~GameObject();
		void Update(float deltaTime);
		void Draw();
		void SetPosition(float x, float y);
		void SetSpawn();
		float GetWidth();
		float GetHeight();
		bool IsDie();
		float GetX();
		float GetY();
		bool IsTaken();
		void SetTaken(bool isTaken);
		void SetActive(bool isActive);
		float GetSpeed();
		void SetSpeed(float newSpeed);
		bool IsAlive();

	protected:
		GameObjectState state;
		float groundDur = 0, groundTime = 0, x = 0, y = 0;
		bool taken;
		Sprite* sprite = NULL;
	private:
		float speed;
		bool active;

	};

}

#endif