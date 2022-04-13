#include "GJHGameEngineSound.h"
#include "GJHGameEngineDebug.h"
#include "GJHGameEnginePath.h"
#include "EngineDefine.h"

FMOD::System* GJHGameEngineSound::m_pSoundSystem;
std::map<GJHString, GJHGameEngineSound*> GJHGameEngineSound::m_AllLoadingSound;
std::map<GJHString, GJHGameEngineSound::SoundPlayer*> GJHGameEngineSound::m_ManagementPlaySound;
std::list< GJHGameEngineSound::SoundPlayer*> GJHGameEngineSound::m_OneShotPlaySound;

GJHGameEngineSound::StaticInit GJHGameEngineSound::Inst = GJHGameEngineSound::StaticInit();

GJHGameEngineSound::StaticInit::StaticInit()
{
	FMOD::System_Create(&GJHGameEngineSound::m_pSoundSystem);
	if (GJHGameEngineSound::m_pSoundSystem == nullptr)
	{
		AssertMsg("if (GJHGameEngineSound::m_pSoundSystem == nullptr)");
	}

	if (GJHGameEngineSound::m_pSoundSystem->init(32, FMOD_DEFAULT, nullptr) != FMOD_OK)
	{
		AssertMsg("if (GJHGameEngineSound::m_AllLoadingSound; _pSoundSystem->init(32, FMOD_DEFAULT, nullptr))");
	}
}

GJHGameEngineSound::StaticInit::~StaticInit()
{
	std::map<GJHString, GJHGameEngineSound*>::iterator Start = m_AllLoadingSound.begin();
	std::map<GJHString, GJHGameEngineSound*>::iterator End = m_AllLoadingSound.end();

	for (; Start != End; ++Start)
	{
		SAFE_DELETE(Start->second);
	}

	if (GJHGameEngineSound::m_pSoundSystem == nullptr)
	{
		GJHGameEngineSound::m_pSoundSystem->release();
		GJHGameEngineSound::m_pSoundSystem = nullptr;
	}

	std::map<GJHString, SoundPlayer*>::iterator iter = m_ManagementPlaySound.begin();
	std::map<GJHString, SoundPlayer*>::iterator iterEnd = m_ManagementPlaySound.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

void GJHGameEngineSound::LoadSound(const GJHString& _Path)
{
	GJHGameEnginePath Path = _Path;
	if (FindSound(Path.FileName()) != nullptr)
	{
		AssertMsg("if (FindSound(Path.FileName()) != nullptr)");
	}

	GJHGameEngineSound* NewSoundFile = new GJHGameEngineSound();

	NewSoundFile->Load(_Path);

	m_AllLoadingSound.insert(std::map<GJHString, GJHGameEngineSound*>::value_type(Path.FileName(), NewSoundFile));
}

GJHGameEngineSound* GJHGameEngineSound::FindSound(const GJHString& _FileName)
{
	std::map<GJHString, GJHGameEngineSound*>::iterator FindSoundIter = m_AllLoadingSound.find(_FileName);

	if (FindSoundIter == m_AllLoadingSound.end())
	{
		return nullptr;
	}

	return FindSoundIter->second;
}

void GJHGameEngineSound::FadeOut(const GJHString& _ManagementName, float _Time)
{
	SoundPlayer* SoundPlayerPtr = FindSoundPlay(_ManagementName);

	if (SoundPlayerPtr == nullptr)
	{
		return;
	}

	int Rate;
	m_pSoundSystem->getSoftwareFormat(&Rate, 0, 0);

	SoundPlayerPtr->SetFadeOut(Rate, _Time);
}

void GJHGameEngineSound::PlayOneShot(const GJHString& _FileName, float _Volume)
{
	GJHGameEngineSound* SoundPtr = FindSound(_FileName);

	if (SoundPtr == nullptr)
	{
		AssertMsg("if (SoundPtr == nullptr)");
	}

	SoundPlayer* SoundPlayerPtr = new SoundPlayer();

	SoundPlayerPtr->m_pPlaySound = SoundPtr;
	SoundPlayerPtr->StartPlay();
	SoundPlayerPtr->SetVolume(_Volume);

	SAFE_DELETE(SoundPlayerPtr);
}

GJHGameEngineSound::SoundPlayer* GJHGameEngineSound::FindSoundPlay(const GJHString& _ManagementName)
{
	std::map<GJHString, SoundPlayer*>::iterator FindPlayer = m_ManagementPlaySound.find(_ManagementName);

	if (FindPlayer == m_ManagementPlaySound.end())
	{
		return nullptr;
	}

	return FindPlayer->second;
}

void GJHGameEngineSound::PlayManagement(const GJHString& _ManagementName, const GJHString& _FileName, float _Volume, bool _Loop)
{
	GJHGameEngineSound* SoundPtr = FindSound(_FileName);

	if (SoundPtr == nullptr)
	{
		AssertMsg("if (SoundPtr == nullptr)");
	}

	SoundPlayer* SoundPlayerPtr = FindSoundPlay(_ManagementName);

	if (SoundPlayerPtr != nullptr)
	{
		AssertMsg("if (SoundPlayerPtr != nullptr)");
	}

	SoundPlayerPtr = new SoundPlayer();

	SoundPlayerPtr->m_pPlaySound = SoundPtr;
	SoundPlayerPtr->StartPlay();
	SoundPlayerPtr->SetVolume(_Volume);

	if (_Loop == true)
	{
		SoundPlayerPtr->SetLoop();
	}

	m_ManagementPlaySound.insert(std::map<GJHString, SoundPlayer*>::value_type(_ManagementName, SoundPlayerPtr));
}

void GJHGameEngineSound::StopManagement(const GJHString& _ManagementName)
{
	SoundPlayer* SoundPlayerPtr = FindSoundPlay(_ManagementName);

	if (SoundPlayerPtr == nullptr)
	{
		return;
	}

	SoundPlayerPtr->Stop();

	SAFE_DELETE(SoundPlayerPtr);
	m_ManagementPlaySound.erase(_ManagementName);
}

void GJHGameEngineSound::Update()
{
	if (m_pSoundSystem != nullptr)
	{
		m_pSoundSystem->update();
	}
}

void GJHGameEngineSound::SoundPlayer::StartPlay()
{
	if (GJHGameEngineSound::m_pSoundSystem->playSound(m_pPlaySound->m_pSound, nullptr, false, &m_pChannel) != FMOD_OK)
	{
		AssertMsg("if (GJHGameEngineSound::m_pSoundSystem->playSound(m_pPlaySound->m_pSound, nullptr, false, &m_pChannel) != FMOD_OK)");
	}
}

void GJHGameEngineSound::SoundPlayer::Stop()
{
	if (m_pChannel != nullptr)
	{
		m_pChannel->stop();
	}
}

void GJHGameEngineSound::Load(const GJHString& _Path)
{
	if (m_pSoundSystem->createSound(_Path, FMOD_DEFAULT, nullptr, &m_pSound) != FMOD_OK)
	{
		AssertMsg("if (m_pSoundSystem->createSound(_Path, FMOD_DEFAULT, nullptr, &m_pSound) != FMOD_OK)");
	}
}