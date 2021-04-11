#pragma once
class cSoundManager : public cSingleton<cSoundManager>
{
public:
	cSoundManager();
	~cSoundManager();

	void Init();
	void Update();
	void Render();
	void Release();

	map<string, CSound*> m_Sounds;
	list<LPDIRECTSOUNDBUFFER> m_Channels;
	CSoundManager m_Manager;
	vector<string> m_Played;

	void AddSound(string _Key, string _Path);
	LPDIRECTSOUNDBUFFER Play(string _Key, long _Volume = -1000, bool _Loop = false);
	void StopAll();
};

#define SOUND cSoundManager::GetInstance()