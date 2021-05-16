#pragma once

#include <string>

class Sound
{
public:
	Sound(const std::string& name, const std::string& path, bool isMusic = false);
	~Sound();

	void Play(float volume, bool loop = false);
	void Stop();
	void Pause();

	void GetSourceState();

	const std::string& GetName() { return mName; }

protected:
	std::string mName;
	
	int mSourceState = -1;

private:
	void LoadSound(const std::string& path);

	unsigned int mSoundBuffer{};
	unsigned int mSoundSource{};
};

