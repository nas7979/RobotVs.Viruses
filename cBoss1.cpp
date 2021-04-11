#include "DXUT.h"
#include "cBoss1.h"


cBoss1::cBoss1()
{
}


cBoss1::~cBoss1()
{
}

void cBoss1::Init()
{
	AC(cAnimation);
	GC(cAnimation)->AddAnimation("Idle", "Boss1_Idle", 0.1);

	GC(cAnimation)->AddAnimation("Intro", "Boss1_Intro", 0.1);
	GC(cAnimation)->AddNotify("Intro", 5, "Intro_Effect1");

	GC(cAnimation)->AddAnimation("Death", "Boss1_Death", 0.15);
	GC(cAnimation)->AddNotify("Death", 22, "Death_Effect1");
	GC(cAnimation)->AddNotify("Death", 55, "Death_Effect2");

	GC(cAnimation)->AddAnimation("Attack1", "Boss1_Attack1", 0.1);
	GC(cAnimation)->AddNotify("Attack1", 5, "Attack1_Attack1");
	GC(cAnimation)->AddNotify("Attack1", 9, "Attack1_Attack1");

	GC(cAnimation)->AddAnimation("Attack2", "Boss1_Attack2", 0.1);
	GC(cAnimation)->AddNotify("Attack2", 8, "Attack2_Attack1");

	m_MaxHp = 1000;
	m_Hp = m_MaxHp;
	m_Blocked = 0;
	m_Speed = 100;
}

void cBoss1::Update()
{
}

void cBoss1::Render()
{
}

void cBoss1::Release()
{
}

void cBoss1::DealDamage(float _Damage, Vec2 _Force)
{
}
