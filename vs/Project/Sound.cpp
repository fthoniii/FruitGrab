#include "Sound.h"

Engine::Sound::Sound(const char* path)
{
	sound = Mix_LoadWAV(path);
}

Engine::Sound::~Sound()
{
	Mix_FreeChunk(sound);
	muted = false; // Inisialisasi muted dengan nilai awal false
}

bool Engine::Sound::IsPlaying()
{
	return Mix_Playing(-1) == 1; //mengembalikan method, apakah sama dengan 1 maka true
}

void Engine::Sound::Play(bool loop)
{
	Mix_PlayChannel(0, sound, loop ? -1 : 0); //jika loopnya true maka diberikan -1
}

void Engine::Sound::Stop()
{
	Mix_HaltChannel(0);
}

void Engine::Sound::SetVolume(int volume)
{
	this->volume = volume;
	Mix_VolumeChunk(sound, volume * 128 / 100);
}

void Engine::Sound::SetMuted(bool muted)
{
	this->muted = muted;
	if (muted) {
		Mix_VolumeChunk(sound, 0); // Set volume menjadi 0 jika muted
	}
	else {
		Mix_VolumeChunk(sound, volume * 128 / 100); // Set volume kembali ke volume sebelumnya jika tidak muted
	}
}
