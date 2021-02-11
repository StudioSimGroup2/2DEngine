#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <iostream>
#include <list>
#include <algorithm>

#include <stdio.h>
#include <iostream>
using namespace std;

class AudioManager
{
public:
	// Singleton pattern
	static AudioManager* getInstance()
	{
		if (instance == 0)
		{
			instance = new AudioManager;
		}
		return instance;
	}

	AudioManager();
	~AudioManager();

	void GrabAudioClips();
	void PlayMusic(string);
	void StopMusic();

private:
	static AudioManager* instance;

	list<string> audioList;
	string pathToDir;
	string name;
	int playCound;
	
	

};

AudioManager::AudioManager()
{
	
}

AudioManager::~AudioManager()
{
}
