#include "DXUT.h"
#include "cTrap.h"
#include "cPlayer.h"

cTrap::cTrap()
{
}


cTrap::~cTrap()
{
}

void cTrap::Init()
{
	if (m_Owner->m_Name == "Spike")
	{
		AC(cAnimation)->AddAnimation("Idle", "Spike", 1000);
		GC(cAnimation)->AddAnimation("Close", "Spike_Close", 0.1, false);
	}
	else if (m_Owner->m_Name == "Mine")
	{
		AC(cAnimation)->AddAnimation("Idle", "Mine", 1000);
		GC(cAnimation)->AddAnimation("Close", "Mine_Triggered", 0.05, false);
	}
	else
	{
		AC(cAnimation)->AddAnimation("Idle", "Trap", 0.1);
		GC(cAnimation)->AddAnimation("Close", "Trap_Close", 0.1, false);
	}
	GC(cAnimation)->m_OnAnimationEnd = [&](string _Key)->void {
		if(_Key == "Close")
			m_Owner->m_Destroyed = true;
	};
	SetAnim("Idle");

	m_Owner->m_Scale = Vec2(0.75, 0.75);
	AC(cCollider)->m_Radius = 10;
	GC(cCollider)->m_CollWith.push_back(Obj_Player);
	GC(cCollider)->m_CollFunc = [&](cObject* _Other)->void {
		GC(cCollider)->m_Enable = false;
		SetAnim("Close");
		cPlayer* Player = _Other->GC(cPlayer);
		if (m_Owner->m_Name == "Spike")
		{
			Player->DealDamage(20);
			SOUND->Play(RandomText("Spike", 1, 2));
		}
		else if (m_Owner->m_Name == "Mine")
		{
			Player->DealDamage(10);
			Player->AddBuff("Mine1", 5, 0.8, 1, 1, 1);
			Player->AddBuff("Mine1", 4, 0.8, 1, 1, 1);
			Player->AddBuff("Mine1", 3, 0.8, 1, 1, 1);
			Player->AddBuff("Mine1", 2, 0.8, 1, 1, 1);
			Player->AddBuff("Mine1", 1, 0.8, 1, 1, 1);
			PART->Explosion(m_Owner->m_Pos, 1);
			SOUND->Play(RandomText("Grenade_Explode", 1, 3));
		}
		else
		{
			Player->DealDamage(0);
			Player->AddBuff("Trap1", 5, 1, 1, 1.2, 1);
			Player->AddBuff("Trap1", 4, 1, 1, 1.2, 1);
			Player->AddBuff("Trap1", 3, 1, 1, 1.2, 1);
			Player->AddBuff("Trap1", 2, 1, 1, 1.2, 1);
			Player->AddBuff("Trap1", 1, 1, 1, 1.2, 1);
			SOUND->Play("Trap");
		}
	};

}

void cTrap::Update()
{
}

void cTrap::Render()
{
}

void cTrap::Release()
{
}
