#include "DXUT.h"
#include "cGrenade.h"
#include "cVirus.h"


cGrenade::cGrenade()
{
}


cGrenade::~cGrenade()
{
}

void cGrenade::Init()
{
	m_Start = m_Owner->m_Pos;
	m_End = INPUT->m_WorldMousePos;
	m_Z = 0;
	m_Speed = PointDistance(m_Start, m_End) / 1.5;
	m_ZSpeed = 1000 / (m_Speed * 0.1);
	m_Timer = 0;
}

void cGrenade::Update()
{
	m_Timer += DT;
	m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), PointDirection(m_Owner->m_Pos, m_End)) * DT;
	Vec2 Center = (m_Start + m_End) * 0.5f;
	m_Z += (PointDistance(m_Owner->m_Pos, Center) / PointDistance(m_Start, Center)) * m_ZSpeed * Sign(0.75 - m_Timer) * DT;

	if (m_Timer >= 1.45)
	{
		m_Owner->m_Destroyed = true;
		SOUND->Play(RandomText("Grenade_Explode", 1, 3));
		float Dist;
		for (auto& iter : PART->m_Particles)
		{
			if (abs(iter->m_Depth - 0.81) <= FLT_EPSILON)
			{
				Dist = PointDistance(m_Owner->m_Pos, iter->m_Pos);
				if (Dist < 75 * 1.5)
				{
					iter->SetPos(((100 * 1.5) - Dist) * 4, Random(0.9f, 0.95f), PointDirection(m_Owner->m_Pos, iter->m_Pos));
				}
			}
		}
		cPartAnim* Anim = PART->AddParticle<cPartAnim>(NULL, m_Owner->m_Pos, Vec2(1, 1) * 1.5 * Random(0.75f, 1.25f), Random(0, 359), 0.3);
		Anim->m_Anim = IMAGE->FindAnimation("Explosion_Large");
		Anim->m_Speed = 0.075;
		cPart* Part = PART->AddParticle<cPart>(NULL, m_Owner->m_Pos, Vec2(1, 1) * 1.5, 0, 0.2, D3DCOLOR_XRGB(255, 224, 130));
		Part->SetLight(200, D3DCOLOR_XRGB(255, 224, 130));
		Part->SetAlpha(2000, -255 * 10, 1);
		cPartFunc* Func;
		for (int i = 0; i < 10; i++)
		{
			Func = PART->AddParticle<cPartFunc>(NULL, m_Owner->m_Pos, Vec2(1, 1) * Random(0.75f, 1.25f) * 1.5, 0, 0.3);
			Func->SetPos(Random(150, 200) * 1.5, 0.96, Random(0, 359));
			Func->SetScale(Vec2(-1.5, -1.5) * 1.5, 1);
			Func->m_FuncSpeed = 0.05;
			Func->m_Func = [](cPartFunc* _Part)->void {
				cPart* Part = PART->AddParticle<cPart>(IMAGE->Find("Point"), _Part->m_Pos, _Part->m_Sca * 10, Random(0, 359), 0.31, 0xff00ffff);
				Part->SetScale(Vec2(-3, -3) * 1.5, 1.02);
				Part->SetLight(5, 0xff00ffff);
			};
		}
		CAMERA->Shake(3 * 1.5, 1 * 1.5);

		for (auto& iter : OBJECT->m_Objects[Obj_Enemy])
		{
			if (PointDistance(m_Owner->m_Pos, iter->m_Pos) < 100)
			{
				cVirus* Virus = iter->GC(cVirus);
				if (Virus != nullptr && Virus->m_Vaccine == false)
				{
					Virus->m_Vaccine = true;
					Virus->m_Owner->SetAlarm(0, 3);
					iter->GC(cCollider)->m_CollWith.push_back(Obj_EnemyBullet);
				}
			}
		}
	}
}

void cGrenade::Render()
{
	IMAGE->CenterRender(IMAGE->Find("Shadow"), m_Owner->m_Pos, Vec2(1, 1) * (1 + 1 / m_Z * 0.02), 0, 0.4, 0x90ffffff);
	IMAGE->CenterRender(IMAGE->Find("Bullet_Vaccine"), Vec2(m_Owner->m_Pos.x, m_Owner->m_Pos.y - m_Z), Vec2(1, 1) * (1 + m_Z * 0.02), timeGetTime() * 0.1, 0.25);
}

void cGrenade::Release()
{
}
