#include "DXUT.h"
#include "cVirusGreen.h"


cVirusGreen::cVirusGreen()
{
}


cVirusGreen::~cVirusGreen()
{
}

void cVirusGreen::Init()
{
	cVirus::Init();
	m_MergeChance = 1.5;
	m_Scale = 0.5;
	m_MaxHp = 10;
	m_Hp = m_MaxHp;
}

void cVirusGreen::Update()
{
	m_Speed = Random(50, 100);
	cVirus::Update();
}

void cVirusGreen::Render()
{
	cVirus::Render();
}

void cVirusGreen::Release()
{
	cVirus::Release();
	cObject* a;
	for (int i = 0; i < 2; i++)
	{
		a = OBJECT->AddObject("EnemyBullet", m_Owner->m_Pos, 0.4, Obj_EnemyBullet);
		a->AC(cBullet)->m_Dir = Random(0,359);
		a->GC(cBullet)->m_Damage = 10;
		a->GC(cBullet)->m_Speed = Random(100, 200);
		a->GC(cBullet)->SetColor(0, 255, 0);
		a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_Green");
		a->GC(cLight)->Set(40, D3DCOLOR_XRGB(0, 255, 0));
		a->GC(cCollider)->m_Radius = 4;
		a->m_Scale = Vec2(0.5, 0.5);
	}
}
