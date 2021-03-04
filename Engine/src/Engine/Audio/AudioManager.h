#pragma once
#include <OpenAL-Soft/al.h>
#include <OpenAL-Soft/alc.h>

#include <vector>
#include <Utils/Sound.h>
#include <string>

namespace Engine
{
	class AudioManager
	{
	public:
		void PlaySoundFile(const std::string& name, float volume, bool loop = false, bool isMusic = false);
		void PauseSound(const std::string& name);
		void StopSound(const std::string& name);

		void Clear();

		void LoadSound(const std::string& name, const std::string& path);
		void RemoveSound(const std::string& name);

		static AudioManager* GetInstance();

	private:
		AudioManager();

		std::vector<Sound*> mSounds;

		static AudioManager* mInstance;
	};
}

