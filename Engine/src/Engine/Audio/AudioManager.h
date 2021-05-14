// #pragma once

// // disable: "<type> needs to have dll-interface to be used by clients'
// // Happens on STL member variables which are not public therefore is ok
// #   pragma warning (disable : 4251)

//#include <OpenAL-Soft/al.h>
//#include <OpenAL-Soft/alc.h>
//
//#include <vector>
//#include <Utils/Sound.h>
//#include <string>
//
//#include "Engine/Core.h"
//
//namespace Engine
//{
//	class ENGINE_API AudioManager
//	{
//	public:
//		void
//		PlaySoundFile(const std::string& name, float volume, bool loop);
//		void PauseSound(const std::string& name);
//		void StopSound(const std::string& name);
//
//		void Clear();
//
//		void LoadSound(const std::string& name, const std::string& path);
//		void RemoveSound(const std::string& name);
//
//		static AudioManager* GetInstance();
//
//		static void Shutdown();
//
//	private:
//		AudioManager();
//
//		std::vector<Sound*> mSounds;
//
//		static AudioManager* mInstance;
//	};
//}
//
