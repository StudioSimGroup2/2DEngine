#include "Sound.h"

#include <vector>

#include "OpenAL-Soft/al.h"
#include "drwav/dr_wav.h"

Sound::Sound(const std::string& name, const std::string& path, bool isMusic)
{
	mName = name;
	
	LoadSound(path);
}

Sound::~Sound()
{
	alDeleteSources(1, &mSoundSource);
	alDeleteBuffers(1, &mSoundBuffer);
}

void Sound::Play(float volume, bool loop)
{
	alSourcef(mSoundSource, AL_GAIN, volume / 1000);

	alSourcei(mSoundSource, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

	alSourcePlay(mSoundSource);
}

void Sound::Stop()
{
	while (mSourceState == AL_PLAYING)
	{
		// stop
		return;
	}
}

void Sound::Pause()
{
	while (mSourceState == AL_PLAYING)
	{
		// stop
		return;
	}
}

void Sound::GetSourceState()
{
	return alGetSourcei(mSoundSource, AL_SOURCE_STATE, &mSourceState);
}

void Sound::LoadSound(const std::string& path)
{
	unsigned int channels = 0;
	unsigned int sampleRate = 0;
	drwav_uint64 totalFrameCount = 0;
	std::vector<uint16_t> pcmData;

	drwav_int16* source = drwav_open_file_and_read_pcm_frames_s16(path.c_str(), &channels, &sampleRate, &totalFrameCount, nullptr);
	if (source == nullptr)
	{
		// ERROR!
		return;
	}

	if ((totalFrameCount * channels) > drwav_uint64(std::numeric_limits<size_t>::max()))
	{
		drwav_free(source, nullptr);
	}

	pcmData.resize(size_t(totalFrameCount * channels));
	std::memcpy(pcmData.data(), source, pcmData.size() * 2);
	drwav_free(source, nullptr);

	alGenBuffers(1, &mSoundBuffer);
	alBufferData(mSoundBuffer, AL_FORMAT_STEREO16, static_cast<ALvoid*>(pcmData.data()), static_cast<ALsizei>(pcmData.size() * 2), static_cast<ALsizei>(sampleRate));

	alGenSources(1, &mSoundSource);
	alSourcef(mSoundSource, AL_PITCH, 1.0f);
	alSourcef(mSoundSource, AL_PITCH, 1.0f);
	alSourcei(mSoundSource, AL_LOOPING, AL_FALSE);
	alSourcei(mSoundSource, AL_BUFFER, static_cast<ALint>(mSoundBuffer));
}
