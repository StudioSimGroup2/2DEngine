//#include "AudioManager.h"
//#include <iostream>
//#include <algorithm>
//
//namespace Engine
//{
//	AudioManager* AudioManager::mInstance = nullptr;
//	
//	void
//	AudioManager::PlaySoundFile(const std::string& name, float volume, bool loop)
//	{
//		auto index = std::find_if(mInstance->mSounds.begin(), mInstance->mSounds.end(),
//			[&name](Sound* s) {return s->GetName() == name; });
//
//		mInstance->mSounds.at(std::distance(mInstance->mSounds.begin(), index))->Play(volume, loop);
//	}
//
//	void AudioManager::PauseSound(const std::string& name)
//	{
//		auto index = std::find_if(mInstance->mSounds.begin(), mInstance->mSounds.end(),
//			[&name](Sound* s) {return s->GetName() == name; });
//
//		mInstance->mSounds.at(std::distance(mInstance->mSounds.begin(), index))->Pause();
//	}
//
//	void AudioManager::StopSound(const std::string& name)
//	{
//		auto index = std::find_if(mInstance->mSounds.begin(), mInstance->mSounds.end(),
//			[&name](Sound* s) {return s->GetName() == name; });
//
//		mInstance->mSounds.at(std::distance(mInstance->mSounds.begin(), index))->Stop();
//	}
//
//	void AudioManager::Clear()
//	{
//	}
//
//	AudioManager* AudioManager::GetInstance()
//	{
//		if (mInstance == nullptr)
//			mInstance = new AudioManager();
//
//		return mInstance;
//	}
//
//	void AudioManager::Shutdown()
//	{
//		if (mInstance == nullptr)
//			return;
//		
//		for (Sound* s : mInstance->mSounds)
//		{
//			delete s;
//			s = nullptr;
//		}
//
//		delete mInstance;
//	}
//
//	AudioManager::AudioManager()
//	{
//		auto audioDevice = alcOpenDevice(nullptr);
//
//		if (!audioDevice)
//		{
//			std::cout << "Failed to open device." << std::endl;
//			return;
//		}
//
//		auto audioContext = alcCreateContext(audioDevice, nullptr);
//
//		if (!alcMakeContextCurrent(audioContext))
//		{
//			std::cout << "Failed to set context." << std::endl;
//			return;
//		}
//
//		ALfloat listenerPosition[] = { 0.0f, 0.0f, 0.0f };
//		ALfloat listenerVelocity[] = { 0.0f, 0.0f, 0.0f };
//		ALfloat listenerOrientation[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
//
//		alListenerfv(AL_POSITION, listenerPosition);
//		alListenerfv(AL_VELOCITY, listenerVelocity);
//		alListenerfv(AL_ORIENTATION, listenerOrientation);
//	}
//
//	void AudioManager::LoadSound(const std::string& name, const std::string& path)
//	{
//		mInstance->mSounds.push_back(new Sound(name, path));
//	}
//
//	void AudioManager::RemoveSound(const std::string& name)
//	{
//	}
//
//}