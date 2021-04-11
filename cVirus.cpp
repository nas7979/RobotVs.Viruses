#include "DXUT.h"
#include "cVirus.h"
#include "cVirusGreen.h"
#include "cVirusBlue.h"
#include "cVirusRed.h"
#include "cVirusPurple.h"

cVirus::cVirus()
{
}


cVirus::~cVirus()
{
}

void cVirus::Init()
{
	AC(cRenderer)->m_Image = IMAGE->Find(RandomText(m_Owner->m_Name, 1, 4));
	AC(cRigidBody);
	AC(cCollider)->m_CollWith.push_back(Obj_PlayerBullet);
	GC(cCollider)->m_CollWith.push_back(Obj_Player);
	GC(cCollider)->m_CollWith.push_back(Obj_Enemy);
	GC(cCollider)->m_CollFunc = [&](cObject* _Other)->void {
		switch (_Other->m_Tag)
		{
		case Obj_Enemy:
		{
			if (m_Owner->m_Name == _Other->m_Name && m_Merged == false)
			{
				if (Random(0, (int)(m_MergeChance / DT)) == 0)
				{
					_Other->GC(cVirus)->m_Hp = 0;
					m_Size++;
					m_Hp += _Other->GC(cVirus)->m_MaxHp;
					GC(cRigidBody)->SetMass(m_Size);
					SOUND->Play(RandomText("Virus_Upgrade", 1, 6));
					m_Merged = true;
					_Other->GC(cVirus)->m_Merged = true;
				}
				else
				{
					_Other->GC(cRigidBody)->AddForce(PointDirectionVec(m_Owner->m_Pos, _Other->m_Pos) * 30);
				}
			}
			else
			{
				_Other->GC(cRigidBody)->AddForce(PointDirectionVec(m_Owner->m_Pos, _Other->m_Pos) * 30);
			}
		}break;

		case Obj_PlayerBullet:
		case Obj_EnemyBullet:
		{
			_Other->m_Destroyed = true;
			cBullet* Other = _Other->GC(cBullet);
			DealDamage(Other->m_Damage, RotateVec(Vec2(Other->m_Damage, 0), Other->m_Dir) * 10);
			float Dist;
			for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
			{
				Dist = PointDistance(_Other->m_Pos, iter->m_Pos);
				if (Dist <= Other->m_Damage * 5)
				{
					iter->GC(cRigidBody)->AddForce((Other->m_Damage * 5 - Dist) * PointDirectionVec(_Other->m_Pos, iter->m_Pos));
				}
			}
		}break;

		case Obj_Player:
		{
			cPlayer* Player = _Other->GC(cPlayer);
			if (Player->m_IsShield == false && m_Debuff <= 0)
			{
				m_Debuff = 4;
				if (m_Owner->m_Name == "VirusGreen")
				{
					Player->AddBuff("VirusGreen2", 3, 0.95, 1, 1, 1);
				}
				else if (m_Owner->m_Name == "VirusBlue")
				{
					Player->AddBuff("VirusBlue2", 3, 0.9, 0.95, 1, 1);
				}
				else if (m_Owner->m_Name == "VirusRed")
				{
					Player->AddBuff("VirusRed2", 3, 0.8, 0.9, 1, 1);
				}
				else if (m_Owner->m_Name == "VirusPurple")
				{
					Player->AddBuff("VirusPurple2", 3, 0.95, 0.95, 1, 0.95);
				}
			}
		}break;
		}
	};
	
	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0 :
			m_Vaccine = false;
			GC(cCollider)->m_CollWith.pop_back();
			break;
		}
	};

	m_Scale = 1;
	m_Size = 1;
	m_Vaccine = false;
	m_Merged = false;
	m_Debuff = 0;
}

void cVirus::Update()
{
	m_Debuff -= DT;
	m_Merged = false;
	GC(cRigidBody)->m_Speed = PointDirectionVec(m_Owner->m_Pos, OBJECT->m_Player->m_Pos) * m_Speed;
	if (m_Size == 3)
	{
		m_Hp = 0;
		SOUND->Play(RandomText("Virus_Merge", 1, 3));
		if (m_Owner->m_Name == "VirusGreen")
		{
			cObject* a = OBJECT->AddObject("VirusBlue", m_Owner->m_Pos, m_Owner->m_Depth, Obj_Enemy);
			a->AC(cVirusBlue);
		}
		else if (m_Owner->m_Name == "VirusBlue")
		{
			cObject* a = OBJECT->AddObject("VirusRed", m_Owner->m_Pos, m_Owner->m_Depth, Obj_Enemy);
			a->AC(cVirusRed);
		}
		else if (m_Owner->m_Name == "VirusRed")
		{
			cObject* a = OBJECT->AddObject("VirusPurple", m_Owner->m_Pos, m_Owner->m_Depth, Obj_Enemy);
			a->AC(cVirusPurple);
		}
	}

	if (m_Hp <= 0)
	{
		m_Owner->m_Destroyed = true;
		cPart* Part;
		for (int i = 0; i < 10; i++)
		{
			Part = PART->AddParticle<cPart>(IMAGE->Find(RandomText(m_Owner->m_Name, 1, 4)), m_Owner->m_Pos, Vec2(0.5, 0.5) * m_Owner->m_Scale.x * Random(0.75f, 1.25f), Random(0, 359), 0.6);
			Part->SetRot(Random(-2000, 2000), 0.95);
			Part->SetPos(Random(100, 200) * m_Owner->m_Scale.x, Random(0.93f, 0.95f), Random(0, 359));
			Part->SetScale(Vec2(-0.2, -0.2) * m_Owner->m_Scale.x, 1.1);
		}
	}

	m_Owner->m_Scale = Lerp<Vec2>(m_Owner->m_Scale, Vec2(1, 1) * m_Scale * (m_Size * 0.75) + Vec2(0.5, 0.5) * Random(0.5f, 1.5f), 0.1);
	GC(cCollider)->m_Radius = m_Owner->m_Scale.x * 10;
}

void cVirus::Render()
{
}

void cVirus::Release()
{
}

void cVirus::DealDamage(float _Damage, Vec2 _Force)
{
	GC(cRigidBody)->AddForce(_Force);
	int Before = m_Hp / m_MaxHp;
	m_Hp -= _Damage;
	SYSTEM->m_DamageDealt += _Damage;
	int After = m_Hp / m_MaxHp;
	while (Before != After && m_Size != 1)
	{
		Before--;
		m_Size--;
		cObject* a = OBJECT->AddObject(m_Owner->m_Name, m_Owner->m_Pos, m_Owner->m_Depth, Obj_Enemy);
		if (m_Owner->m_Name == "VirusGreen")
		{
			a->AC(cVirusGreen);
		}
		else if (m_Owner->m_Name == "VirusBlue")
		{
			a->AC(cVirusBlue);
		}
		else if (m_Owner->m_Name == "VirusRed")
		{
			a->AC(cVirusRed);
		}
		else if (m_Owner->m_Name == "VirusPurple")
		{
			a->AC(cVirusPurple);
		}
	}
	m_Owner->m_Scale += Vec2(1,1);

	if (m_Hp <= 0)
	{
		SYSTEM->m_Score += m_MaxHp * 1000;
		//Item
	}
}
