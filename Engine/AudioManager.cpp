#include "AudioManager.h"




void AudioManager::GrabAudioClips()
{
	pathToDir = "2DEngine\Engine\audio";
	
}

void AudioManager::PlayMusic(string soundPath)
{
	PlaySound(TEXT("soundPath"), NULL, SND_SYNC);
}