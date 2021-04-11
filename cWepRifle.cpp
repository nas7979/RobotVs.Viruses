#include "DXUT.h"
#include "cWepRifle.h"


cWepRifle::cWepRifle()
{
}


cWepRifle::~cWepRifle()
{
}

void cWepRifle::Init()
{
	cWep::Init();
	AC(cAnimation)->AddAnimation("Idle", "Wep_Rifle_Fire", 0.03, false);
	SetAnim("Idle");
	GC(cAnimation)->m_Frame = 4;

	m_Owner->SetAlarmSize(2);
	m_Owner->m_AlarmFunc = [&](int _Index)->void {
		switch (_Index)
		{
		case 0:
			m_FireAble = true;
			break;

		case 1:
			int Ammo = Clamp(SYSTEM->m_RifleAmmoLeft, 0, 30 - SYSTEM->m_RifleAmmo);
			SYSTEM->m_RifleAmmo = Ammo;
			SYSTEM->m_RifleAmmoLeft -= Ammo;
			m_Player->GC(cPlayer)->m_Reloading = false;
			break;
		}
	};
}

void cWepRifle::Update()
{
	m_Dir = PointDirection(m_Owner->m_Pos, INPUT->m_WorldMousePos);
	m_Owner->m_Rot = m_Dir;
	m_Owner->m_Scale.y = m_Dir < 90 && m_Dir >= -90 ? 1 : -1;
	m_Owner->m_Pos = m_Player->m_Pos + RotateVec(Vec2(10 + m_RecoilPos, 0), m_Dir);
	if (m_RecoilPos != 0)
	{
		m_RecoilVel += 250 * DT;
		m_RecoilPos += m_RecoilVel * DT;
		if (m_RecoilPos >= 0)
		{
			m_RecoilPos = 0;
		}
	}

	if (m_Player->GC(cPlayer)->m_Reloading == false)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (SYSTEM->m_RifleAmmo != 0)
			{
				if (m_FireAble)
				{
					SYSTEM->m_RifleAmmo--;
					cObject* a = OBJECT->AddObject("PlayerBullet", m_Owner->m_Pos, 0.6, Obj_PlayerBullet);
					a->AC(cBullet)->m_Dir = m_Dir + Random(-10, 10);
					a->GC(cBullet)->m_Damage = 10;
					a->GC(cBullet)->m_Speed = 450;
					a->GC(cBullet)->SetColor(255, 204, 136);
					a->GC(cRenderer)->m_Image = IMAGE->Find("Bullet_Rifle");
					a->GC(cLight)->Set(30, D3DCOLOR_XRGB(255, 204, 136));
					a->GC(cCollider)->m_Radius = 8;
					a->m_Scale = Vec2(1.5, 1.5);
					m_FireAble = false;
					m_Owner->SetAlarm(0, 0.1f);
					m_RecoilVel = -15;
					m_RecoilPos = -7;
					CAMERA->Shake(2, 0.5);
					SOUND->Play(RandomText("Rifle_Fire", 1, 2));
					GC(cAnimation)->m_Frame = 1;
					GC(cAnimation)->m_Speed = 1;
					cPart* Part = PART->AddParticle<cPart>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, 0.3);
					Part->SetLight(300, D3DCOLOR_XRGB(255, 204, 136));
					Part->SetAlpha(255, -255 * 5, 1);
				}
			}
			else if(SYSTEM->m_RifleAmmoLeft != 0)
			{
				m_Owner->SetAlarm(1, 1.5);
				SOUND->Play("Rifle_Reload");
				m_Player->GC(cPlayer)->m_Reloading = true;
			}
		}

		if (INPUT->KeyDown('R') && SYSTEM->m_RifleAmmo != 30 && SYSTEM->m_RifleAmmoLeft != 0)
		{
			m_Owner->SetAlarm(1, 1.5);
			SOUND->Play("Rifle_Reload");
			m_Player->GC(cPlayer)->m_Reloading = true;
		}
	}
}

void cWepRifle::Render()
{
}

void cWepRifle::Release()
{
}
