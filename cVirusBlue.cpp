#include "DXUT.h"
#include "cVirusBlue.h"
#include "cVirusGreen.h"

cVirusBlue::cVirusBlue()
{
}


cVirusBlue::~cVirusBlue()
{
}

void cVirusBlue::Init()
{
	cVirus::Init();
	m_Scale = 1;
	m_MergeChance = 1.5;
	m_MaxHp = 50;
	m_Hp = m_MaxHp;
}

void cVirusBlue::Update()
{
	m_Speed = Random(75, 125);
	cVirus::Update();

	if (Random(0, (int)(2.f / DT)) == 0)
	{
		cObject* a;
		float Dir = PointDirection(m_Owner->m_Pos, OBJECT->m_Player->m_Pos);
		for (int i = -m_Size; i <= m_Size; i++)
		{
			a = OBJECT->AddObject("EnemyBullet", m_Owner->m_Pos, 0.4, Obj_EnemyBullet);
			a->AC(cBullet)->m_Dir = Dir + i * 10;
			a->GC(cBullet)->m_Damage = 10;
			a->GC(cBullet)->m_Speed = 175;
			a->GC(cBullet)->SetColor(0, 255, 255);
			a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_SkyBlue");
			a->GC(cLight)->Set(40, D3DCOLOR_XRGB(0, 255, 255));
			a->GC(cCollider)->m_Radius = 4;
			a->m_Scale = Vec2(0.5, 0.5);
		}
	}

	if (Random(0, (int)(4.f / DT)) == 0)
	{
		cObject* a = OBJECT->AddObject("VirusGreem", m_Owner->m_Pos, m_Owner->m_Depth, Obj_Enemy);
		a->AC(cVirusGreen);
		SOUND->Play(RandomText("Virus_Explosion_Large", 1, 6), -1500);
	}
}

void cVirusBlue::Render()
{
	cVirus::Render();
}

void cVirusBlue::Release()
{
	cVirus::Release();
	cObject* a;
	for (int i = 0; i < 8; i++)
	{
		a = OBJECT->AddObject("EnemyBullet", m_Owner->m_Pos, 0.4, Obj_EnemyBullet);
		a->AC(cBullet)->m_Dir = Random(0, 359);
		a->GC(cBullet)->m_Damage = 10;
		a->GC(cBullet)->m_Speed = Random(100, 200);
		a->GC(cBullet)->SetColor(0, 0, 255);
		a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_Blue");
		a->GC(cLight)->Set(40, D3DCOLOR_XRGB(0, 0, 255));
		a->GC(cCollider)->m_Radius = 4;
		a->m_Scale = Vec2(0.5, 0.5);
	}
}
