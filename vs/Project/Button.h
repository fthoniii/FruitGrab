#ifndef BUTTON_H
#define BUTTON_H

#include "Sprite.h"

namespace Engine {
	enum class ButtonState { //deklarasikan enumerasi dari state button
		PRESS, //ketika ditekan tombol enter
		HOVER,
		NORMAL,
		MUTE,
		MUTEHOVER
	};
	class Button
	{
	public:
		Button(Sprite* sprite, string name);
		~Button();
		void Update(float deltaTime); //update animasi
		void Draw(); //render
		void SetPosition(float x, float y); //memposisikan button
		vec2 GetPosition(); //dapetin position
		ButtonState GetButtonState(); //mendapatkan state dari button
		void SetButtonState(ButtonState state); //set state dari button
		string GetButtonName(); //dapatkan nama dari button 
		void SetButtonName(string a); //set state dari button
	private:
		ButtonState state; //nyimpen state
		Sprite* sprite; //nyimpen sprite
		string name; //nyimpen name
	};
}

#endif