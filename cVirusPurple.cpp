#include "DXUT.h"
#include "cVirusPurple.h"


cVirusPurple::cVirusPurple()
{
}


cVirusPurple::~cVirusPurple()
{
}

void cVirusPurple::Init()
{
	cVirus::Init();
	m_MergeChance = 1.5;
	m_Scale = 0.5;
	m_MaxHp = 40;
	m_Hp = m_MaxHp;
}

void cVirusPurple::Update()
{
	m_Speed = Random(125, 175);
	cVirus::Update();
}

void cVirusPurple::Render()
{
	cVirus::Render();
}

void cVirusPurple::Release()
{
	cVirus::Release();
	cObject* a;
	for (int i = 0; i < 5; i++)
	{
		a = OBJECT->AddObject("EnemyBullet", m_Owner->m_Pos, 0.4, Obj_EnemyBullet);
		a->AC(cBullet)->m_Dir = Random(0, 359);
		a->GC(cBullet)->m_Damage = 10;
		a->GC(cBullet)->m_Speed = Random(100, 200);
		a->GC(cBullet)->SetColor(0, 255, 128);
		a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_Purple");
		a->GC(cLight)->Set(40, D3DCOLOR_XRGB(0, 255, 128));
		a->GC(cCollider)->m_Radius = 4;
		a->m_Scale = Vec2(0.5, 0.5);
	}
}
