#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Quad.h"
#include "BoundingBox.h"
#include <GLM/gtc/matrix_transform.hpp>

using namespace glm;

namespace Engine {
	struct AnimData { // digunakan untuk menyimpan data animasi
		string name; //nama animasi
		int startFrameIndex, endFrameIndex; //mulai frame berapa sampe berapa
	};

	class Sprite
	{
	public:
		Sprite(Texture* texture, Shader* shader, Quad* quad);
		~Sprite();
		void Draw();
		void Update(float deltaTime);
		void AddAnimation(string name, int startFrameIndex, int endFrameIndex); //untuk menambahkan animasi
		void PlayAnim(string name); //untuk mengaktifkan animasi
		void SetFlipHorizontal(bool flipHorizontal);
		void SetFlipVertical(bool flipVertical);
		void SetAnimationDuration(float maxFrameDuration);
		void SetEnableAnimation(bool enableAnimation);
		void SetPosition(float x, float y);
		void SetRotation(float degree);
		void SetNumXFrames(int numXFrames); //untuk memberitahu ada berapa baris
		void SetNumYFrames(int numYFrames); //untuk memberitahu ada berapa kolom
		int GetTotalFrames(); //ada berapa potongan nantinya xframe * yframe
		float GetRotation();
		void SetScale(float s);
		float GetScale();
		void SetSize(float width, float height);
		float GetScaleWidth();
		float GetScaleHeight();
		BoundingBox* GetBoundingBox();
		vec2 GetPosition();
		vec2 GetRotatedPoint(float x, float y);
		void SetBoundingBoxSize(float w, float h);
		void SetScore(int value);
		int GetScore() const { return score; }
		float GetSpeed();
		void SetSpeed(float newSpeed);
	private:
		BoundingBox* boundingBox;
		vec4 min;
		Shader* shader;
		Quad* quad;
		Texture* texture;
		float width = 0, height = 0, s = 1, degree = 0, frameDuration = 0, maxFrameDuration = 80;
		bool flipHorizontal = false, flipVertical = false, enableAnimation = false;
		int numXFrames = 1, numYFrames = 1, frameIndex = 0;
		mat4 CreateTransform();
		void UpdateShaderData();
		AnimData* GetAnimData(string name); //dimulai dari index berapa ke berapa
		vec2 position, boundingBoxSize;
		vector<AnimData*> animationData; //array dinamis untuk menyimpan data-data animasi
		AnimData* currentAnim = NULL; //sebagai pointer untuk menunjuk ke animasi yang sedang dijalankan
		int score;
		float speed;

	};
}

#endif

