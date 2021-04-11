#pragma once
struct Rank
{
	wstring Name;
	int Score;
};
#include "cSingleton.h"
class cSystemManager : public cSingleton<cSystemManager>
{
public:
	cSystemManager();
	~cSystemManager();

	void Init();
	void Update();
	void Render();
	void Release();

	float m_DT;
	float m_NSDT;
	float m_TimeScale = 1;
	float m_Alarm[5];
	int m_RevolverAmmo;
	int m_RifleAmmo;
	int m_RifleAmmoLeft;
	int m_Score;
	int m_Coin;
	float m_DamageDealt;
	float m_Time;
	list<Rank> m_Rank;

	void PlayerInit();
	void SortRank();
};

#define SYSTEM cSystemManager::GetInstance()