#include "DXUT.h"
#include "cPlayer.h"
#include "cWepRevoler.h"
#include "cWepRifle.h"
#include "cGrenade.h"

cPlayer::cPlayer()
{
}


cPlayer::~cPlayer()
{
}

void cPlayer::Init()
{
	m_ChargeTarget = nullptr;
	m_Charging = false;
	m_Charge = 0;
	m_MaxHp = 1500000;
	m_Hp = m_MaxHp;
	m_Vaccine = 0;
	m_IsShield = false;
	m_Shield = 0;
	m_Dash = 0;
	m_DashDir = Vec2(0, 0);
	m_Speed = 1;
	m_AttackSpeed = 1;
	m_Scale = 1;
	m_Damage = 1;
	m_Reloading = false;
	m_Dead = false;
	OBJECT->m_Player = m_Owner;

	AC(cAnimation);
	AC(cRigidBody);
	AC(cLight)->Set(40, 0xffffffff);
	GC(cAnimation)->AddAnimation("Idle", "Player_Idle", 0.15);
	GC(cAnimation)->AddAnimation("Walk", "Player_Walk", 0.12);
	GC(cAnimation)->AddAnimation("Death", "Player_Death", 0.12);
	AC(cCollider)->m_Radius = 10;
	GC(cCollider)->m_CollWith.push_back(Obj_EnemyBullet);
	GC(cCollider)->m_CollFunc = [&](cObject* _Other)->void {
		switch (_Other->m_Tag)
		{
		case Obj_EnemyBullet:
			_Other->m_Destroyed = true;
			if (m_IsShield == false)
			{
				DealDamage(_Other->GC(cBullet)->m_Damage);
			}
			else
			{
				cObject* a = OBJECT->AddObject("PlayerBullet", _Other->m_Pos, 0.6, Obj_PlayerBullet);
				a->AC(cBullet)->m_Damage = _Other->GC(cBullet)->m_Damage;
				a->GC(cBullet)->m_Dir = _Other->GC(cBullet)->m_Dir - 180;
				a->GC(cBullet)->m_Speed = _Other->GC(cBullet)->m_Speed;
				a->GC(cLight)->Set(_Other->GC(cLight)->m_Radius, _Other->GC(cLight)->m_Light->Color);
				memcpy(a->GC(cBullet)->m_PartColor, _Other->GC(cBullet)->m_PartColor, sizeof(float) * 3);
				a->GC(cRenderer)->m_Image = _Other->GC(cRenderer)->m_Image;
				a->GC(cCollider)->m_Radius = _Other->GC(cCollider)->m_Radius;
				a->m_Scale = _Other->m_Scale;
				SOUND->Play(RandomText("Shield_Hit", 1, 3));
			}
			break;
		}
	};
	SetAnim("Idle");

	m_Owner->SetAlarmSize(1);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			m_IsShield = false;
			GC(cRenderer)->m_Color = 0xffffffff;
			break;
		}
	};

	m_Wep = OBJECT->AddObject("Revolver", m_Owner->m_Pos, 0.49, Obj_Weapon);
	m_Wep->AC(cWepRevoler)->m_Player = m_Owner;
}

void cPlayer::Update()
{
	m_Speed = 150;
	m_Damage = 1;
	m_AttackSpeed = 1;
	m_Scale = 1;
	for (auto& iter = m_Buffs.begin(); iter != m_Buffs.end();)
	{
		(*iter)->Time -= DT;
		m_Speed *= (*iter)->Speed;
		m_Damage *= (*iter)->Damage;
		m_AttackSpeed *= (*iter)->AttackSpeed;
		m_Scale *= (*iter)->Scale;
		if ((*iter)->Time <= 0)
		{
			delete *iter;
			iter = m_Buffs.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	if (m_DashDir == Vec2(0, 0))
	{
		bool Moved = false;
		if (INPUT->KeyPress('W'))
		{
			Moved = true;
			m_DashDir.y = -1;
			GC(cRigidBody)->m_Speed.y = -m_Speed;
		}
		if (INPUT->KeyPress('S'))
		{
			Moved = true;
			m_DashDir.y = 1;
			GC(cRigidBody)->m_Speed.y = m_Speed;
		}
		if (INPUT->KeyPress('A'))
		{
			Moved = true;
			m_DashDir.x = -1;
			GC(cRigidBody)->m_Speed.x = -m_Speed;
		}
		if (INPUT->KeyPress('D'))
		{
			Moved = true;
			m_DashDir.x = 1;
			GC(cRigidBody)->m_Speed.x = m_Speed;
		}

		if (INPUT->KeyDown(VK_SPACE))
		{
			if (m_Dash <= 0)
			{
				m_DashDir *= 800;
				m_Dash = 1;
				cPartAnim* Anim = PartAnim(m_Owner->m_Pos, m_Owner->m_Scale, 0, 0.4, 0xffffffff);
				Anim->m_Anim = IMAGE->FindAnimation("Dash_Effect");
				Anim->m_Speed = 0.1;
				SOUND->Play("Dash");
			}
			else
			{
				cPartText* PTex = PART->AddParticle<cPartText>(NULL, Vec2(960, 200), Vec2(2, 2), 0, 0.01, 0xffff0000);
				PTex->SetScale(Vec2(0, -0.01), 1.05);
				PTex->m_Text = L"아직 사용할 수 없습니다.";
			}
		}
		else
		{
			m_DashDir = Vec2(0, 0);
			if (Moved)
			{
				if (GC(cAnimation)->m_CurAnim->Key != "Walk")
				{
					SetAnim("Walk");
				}
			}
			else
			{
				if (GC(cAnimation)->m_CurAnim->Key != "Idle")
				{
					SetAnim("Idle");
				}
			}
		}
	}
	else
	{
		m_DashDir *= pow(0.9, DT * 60);
		if (D3DXVec2Length(&m_DashDir) <= 300)
		{
			m_DashDir = Vec2(0, 0);
		}
		GC(cRigidBody)->m_Speed = m_DashDir;
	}

	if (m_Reloading == false)
	{
		if (INPUT->KeyDown('1'))
		{
			if (m_Wep->m_Name != "Revolver")
			{
				m_Wep->m_Destroyed = true;
				m_Wep = OBJECT->AddObject("Revolver", m_Owner->m_Pos, 0.49, Obj_Weapon);
				m_Wep->AC(cWepRevoler)->m_Player = m_Owner;
			}
		}
		if (INPUT->KeyDown('2'))
		{
			if (m_Wep->m_Name != "Rifle")
			{
				m_Wep->m_Destroyed = true;
				m_Wep = OBJECT->AddObject("Rifle", m_Owner->m_Pos, 0.49, Obj_Weapon);
				m_Wep->AC(cWepRifle)->m_Player = m_Owner;
			}
		}

		if (INPUT->KeyDown('Q'))
		{
			if (m_Vaccine <= 0)
			{
				m_Vaccine = 10;
				cObject* a = OBJECT->AddObject("Vaccine", m_Owner->m_Pos, 0.25, Obj_None);
				a->AC(cGrenade);
			}
			else
			{
				cPartText* PTex = PART->AddParticle<cPartText>(NULL, Vec2(960, 200), Vec2(2, 2), 0, 0.01, 0xffff0000);
				PTex->SetScale(Vec2(0, -0.01), 1.05);
				PTex->m_Text = L"아직 사용할 수 없습니다.";
			}
		}

		if (INPUT->KeyDown('E'))
		{
			if (m_Shield <= 0)
			{
				m_Shield = 10;
				m_IsShield = true;
				m_Owner->SetAlarm(0, 3);
				GC(cRenderer)->m_Color = 0xff00ffff;
				SOUND->Play("Shield_Start");
			}
			else
			{
				cPartText* PTex = PART->AddParticle<cPartText>(NULL, Vec2(960, 200), Vec2(2, 2), 0, 0.01, 0xffff0000);
				PTex->SetScale(Vec2(0, -0.01), 1.05);
				PTex->m_Text = L"아직 사용할 수 없습니다.";
			}
		}

		if (INPUT->KeyPress(VK_RBUTTON))
		{
			if (m_Charging == false)
			{

			}
		}
	}

	m_Dash -= DT;
	m_Vaccine -= DT;
	m_Shield -= DT;
	m_Owner->m_Scale = Lerp<Vec2>(Vec2(abs(m_Owner->m_Scale.x), m_Owner->m_Scale.y), Vec2(1, 1) * m_Scale, 0.1);
	m_Owner->m_Scale.x *= m_Wep->m_Scale.y;
	m_Damaged -= 255 * DT;
}

void cPlayer::Render()
{
	IMAGE->CenterRender(IMAGE->Find("Shadow"), m_Owner->m_Pos, m_Owner->m_Scale, 0, 0.7, 0x90ffffff);
	if (m_IsShield)
	{
		IMAGE->CenterRender(IMAGE->Find("Shield9"), m_Owner->m_Pos, m_Owner->m_Scale * 0.5, 0, 0.48);
	}
}

void cPlayer::Release()
{
	for (auto& iter : m_Buffs)
	{
		delete iter;
	}
	OBJECT->m_Player = nullptr;
}

void cPlayer::AddBuff(string _Key, float _Time, float _Speed, float _AttackSpeed, float _Scale, float _Damage)
{
	Buff* a = new Buff;
	a->Key = _Key;
	a->Time = _Time;
	a->Speed = _Speed;
	a->AttackSpeed = _AttackSpeed;
	a->Scale = _Scale;
	a->Damage = _Damage;
	m_Buffs.push_back(a);
}

void cPlayer::DealDamage(float _Damage)
{
	m_Hp -= _Damage;
	m_Damaged = 255;
	SOUND->Play(RandomText("Damaged", 1, 4));
	CAMERA->Shake(5, 1);
}
