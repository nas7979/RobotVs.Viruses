#include "DXUT.h"
#include "cSystemManager.h"
#include "cPlayer.h"

cSystemManager::cSystemManager()
{
}


cSystemManager::~cSystemManager()
{
}

void cSystemManager::Init()
{
	PlayerInit();
}

void cSystemManager::Update()
{
	m_NSDT = DXUTGetElapsedTime();
	m_DT = m_NSDT * m_TimeScale;
	m_Time -= DT;
	if (m_Time <= 0)
	{
		m_Time = 0;
		OBJECT->m_Player->GC(cPlayer)->m_Hp = 0;
	}
}

void cSystemManager::Render()
{
	IMAGE->CenterRender(IMAGE->Find("Cursor"), INPUT->m_WorldMousePos, Vec2(1, 1), 0, 0.001, 0xffffffff);

	TCHAR Text[64];
	if (OBJECT->m_Player != nullptr)
	{
		cPlayer* Player = OBJECT->m_Player->GC(cPlayer);

		if (Player->m_Damaged > 0)
		{
			IMAGE->CenterRender(IMAGE->Find("Damaged"), Vec2(960, 540), Vec2(6, 6), 0, 0.05, D3DCOLOR_ARGB((int)Player->m_Damaged, 255, 255, 255), true);
		}

		float Scale = 4;
		IMAGE->CenterRender(IMAGE->Find("UI_Hp1"), Vec2(1650, 940), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Hp2"), Vec2(1650, 940), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Hp3"), Vec2(1650, 940), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Hp4"), Vec2(1650, 940), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Hp5"), Vec2(1650, 940), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRenderRect(IMAGE->Find("UI_Hp6"), Vec2(1650 + Scale * 7, 940 + Scale * 13), Vec2(Scale, Scale), 0, 0.1, RECT{0,0, (long)(Clamp(Player->m_Hp / Player->m_MaxHp, 0, 1) * 84), 10}, 0xffffffff, true);

		IMAGE->CenterRender(IMAGE->Find("UI_Timer1"), Vec2(960, 50), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Timer2"), Vec2(960, 50), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		wsprintf(Text, L"%d:%d", (int)(m_Time / 60), (int)m_Time % 60);
		IMAGE->CenterRenderText((m_Time < 10000 ? Text : L"Inf."), Vec2(970, 50), Vec2(0.75, 0.75), 0, 0.1, 0xa0ffffff, true);

		IMAGE->CenterRender(IMAGE->Find("UI_Score1"), Vec2(230, 50), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		wsprintf(Text, L"SCORE:%d", m_Score);
		IMAGE->RenderText(Text, Vec2(25, 25), Vec2(0.75, 0.75), 0, 0.1, 0xa0ffffff, true);

		IMAGE->CenterRender(IMAGE->Find("UI_Coin1"), Vec2(1800, 800), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("UI_Coin2"), Vec2(1800, 800), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		wsprintf(Text, L"%d", m_Coin);
		IMAGE->RenderText(Text, Vec2(1800, 775), Vec2(0.75, 0.75), 0, 0.1, 0xa0ffffff, true);

		IMAGE->CenterRender(IMAGE->Find("UI_Skill"), Vec2(100, 980), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("Bullet_Vaccine"), Vec2(100, 980), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		if (Player->m_Vaccine > 0)
			IMAGE->CenterRenderText(to_wstring((int)Player->m_Vaccine + 1), Vec2(100, 980), Vec2(1, 1), 0, 0.1, 0xffffffff, true);

		IMAGE->CenterRender(IMAGE->Find("UI_Skill"), Vec2(300, 980), Vec2(Scale, Scale), 0, 0.1, 0xa0ffffff, true);
		IMAGE->CenterRender(IMAGE->Find("Shield9"), Vec2(300, 980), Vec2(1, 1), 0, 0.1, 0xa0ffffff, true);
		if (Player->m_Shield > 0)
			IMAGE->CenterRenderText(to_wstring((int)Player->m_Shield + 1), Vec2(300, 980), Vec2(1, 1), 0, 0.1, 0xffffffff, true);
	}
}

void cSystemManager::Release()
{
}

void cSystemManager::PlayerInit()
{
	m_Score = 0;
	m_RevolverAmmo = 6;
	m_RifleAmmo = 30;
	m_RifleAmmoLeft  = 100000;
	m_Coin = 0;
	m_DamageDealt = 0;
}

void cSystemManager::SortRank()
{
	m_Rank.sort([&](Rank _Prev, Rank _Next)->bool {return _Prev.Score > _Next.Score; });
}
