#include "DXUT.h"
#include "cVirusRed.h"


cVirusRed::cVirusRed()
{
}


cVirusRed::~cVirusRed()
{
}

void cVirusRed::Init()
{
	cVirus::Init();
	m_Scale = 1.5;
	m_MergeChance = 1.5;
	m_MaxHp = 250;
	m_Hp = m_MaxHp;
}

void cVirusRed::Update()
{
	m_Speed = Random(100, 150);
	cVirus::Update();
}

void cVirusRed::Render()
{
	cVirus::Render();
}

void cVirusRed::Release()
{
	cVirus::Release();
	cObject* a;
	for (int i = 0; i < 20; i++)
	{
		a = OBJECT->AddObject("EnemyBullet", m_Owner->m_Pos, 0.4, Obj_EnemyBullet);
		a->AC(cBullet)->m_Dir = Random(0, 359);
		a->GC(cBullet)->m_Damage = 10;
		a->GC(cBullet)->m_Speed = Random(100, 200);
		a->GC(cBullet)->SetColor(255, 0, 0);
		a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_Red");
		a->GC(cLight)->Set(40, D3DCOLOR_XRGB(255, 0, 0));
		a->GC(cCollider)->m_Radius = 4;
		a->m_Scale = Vec2(0.5, 0.5);
	}
}
