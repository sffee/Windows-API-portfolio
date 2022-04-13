#pragma once
#include <fmod.hpp>
#include <fmod_errors.h>
#include <map>
#include <list>
#include "GJHString.h"

#ifdef _DEBUG
#pragma comment(lib, "fmodL_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

class GJHGameEngineSound
{
private:
	static FMOD::System* m_pSoundSystem;

private:
	class StaticInit
	{
	public:
		StaticInit();
		~StaticInit();
	};
	static StaticInit Inst;

	static std::map<GJHString, GJHGameEngineSound*> m_AllLoadingSound;

public:
	class SoundPlayer
	{
		friend GJHGameEngineSound;

	private:
		FMOD::Channel* m_pChannel;
		GJHGameEngineSound* m_pPlaySound;
		float m_Volume;

	private:
		void StartPlay();
		void Stop();

	private:
		void SetPlaySound(GJHGameEngineSound* _pPlaySound)
		{
			m_pPlaySound = _pPlaySound;
		}

		void SetVolume(float _Volume)
		{
			m_Volume = _Volume;
			m_pChannel->setVolume(_Volume);
		}

		void SetLoop()
		{
			m_pChannel->setMode(FMOD_LOOP_NORMAL);
		}

		void SetFadeOut(int _Rate, float _Time)
		{
			unsigned long long DspClock;

			m_pChannel->getDSPClock(0, &DspClock);
			m_pChannel->addFadePoint(DspClock, m_Volume);
			m_pChannel->addFadePoint(DspClock + ((unsigned long long)_Rate * (unsigned long long)_Time), 0.f);
		}
	};

	static std::map<GJHString, SoundPlayer*> m_ManagementPlaySound;
	static std::list<SoundPlayer*> m_OneShotPlaySound;

public:
	static SoundPlayer* FindSoundPlay(const GJHString& _ManagementName);

public:
	static void LoadSound(const GJHString& _Path);
	static GJHGameEngineSound* FindSound(const GJHString& _FileName);

	static void FadeOut(const GJHString& _ManagementName, float _Time);

	static void PlayOneShot(const GJHString& _FileName, float _Volume = 1.f);
	static void PlayManagement(const GJHString& _ManagementName, const GJHString& _FileName, float _Volume = 1.f, bool _Loop = false);
	static void StopManagement(const GJHString& _ManagementName);
	static void Update();

private:
	FMOD::Sound* m_pSound;

public:
	void Load(const GJHString& _Path);
};