#include "DXUT.h"
#include "cParticleManager.h"


cParticleManager::cParticleManager()
{
}


cParticleManager::~cParticleManager()
{
}

void cParticleManager::Init()
{
}

void cParticleManager::Update()
{
	for (auto& iter = m_Particles.begin(); iter != m_Particles.end();)
	{
		(*iter)->m_PosVel *= pow((*iter)->m_PosFri, DT * 60);
		(*iter)->m_ScaVel *= pow((*iter)->m_ScaFri, DT * 60);
		(*iter)->m_RotVel *= pow((*iter)->m_RotFri, DT * 60);
		(*iter)->m_AlpVel *= pow((*iter)->m_AlpFri, DT * 60);

		(*iter)->m_Pos += RotateVec(Vec2((*iter)->m_PosVel, 0), (*iter)->m_Dir) * DT;
		(*iter)->m_Sca += (*iter)->m_ScaVel * DT;
		(*iter)->m_Rot += (*iter)->m_RotVel * DT;
		(*iter)->m_Alp += (*iter)->m_AlpVel * DT;

		(*iter)->m_Color = ((*iter)->m_Color & 0x00ffffff) | ((int)min(255, (*iter)->m_Alp) << 24);
		(*iter)->Update();

		if ((*iter)->m_Alp <= 0 || (*iter)->m_Sca.x <= 0 || (*iter)->m_Sca.y <= 0)
		{
			(*iter)->Release();
			delete *iter;
			iter = m_Particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void cParticleManager::Render()
{
	for (auto& iter : m_Particles)
	{
		iter->Render();
	}
}

void cParticleManager::Release()
{
	for (auto& iter : m_Particles)
	{
		iter->Release();
		delete iter;
	}
	m_Particles.clear();
}

void cParticleManager::Explosion(Vec2 _Pos, float _Scale, int _Amount)
{
	float Dist;
	for (auto& iter : m_Particles)
	{
		if (abs(iter->m_Depth - 0.81) <= FLT_EPSILON)
		{
			Dist = PointDistance(_Pos, iter->m_Pos);
			if (Dist < 75 * _Scale)
			{
				iter->SetPos(((100 * _Scale) - Dist) * 4, Random(0.9f, 0.95f), PointDirection(_Pos, iter->m_Pos));
			}
		}
	}

	cPartAnim* Anim = PART->AddParticle<cPartAnim>(NULL, _Pos, Vec2(1, 1) * _Scale * Random(0.75f, 1.25f), Random(0, 359), 0.3);
	Anim->m_Anim = IMAGE->FindAnimation("Explosion_Large");
	Anim->m_Speed = 0.075;
	cPart* Part = PART->AddParticle<cPart>(NULL, _Pos, Vec2(1, 1) * _Scale, 0, 0.2, D3DCOLOR_XRGB(255, 224, 130));
	Part->SetLight(200, D3DCOLOR_XRGB(255, 224, 130));
	Part->SetAlpha(2000, -255 * 10, 1);
	cPartFunc* Func;
	for (int i = 0; i < _Amount; i++)
	{
		Func = PART->AddParticle<cPartFunc>(NULL, _Pos, Vec2(1, 1) * Random(0.75f, 1.25f) * _Scale, 0, 0.3);
		Func->SetPos(Random(150, 200) * _Scale, 0.96, Random(0, 359));
		Func->SetScale(Vec2(-1.5, -1.5) * _Scale, 1);
		Func->m_FuncSpeed = 0.05;
		Func->m_Func = [=](cPartFunc* _Part)->void {
			cPart* Part = PART->AddParticle<cPart>(IMAGE->Find(RandomText("Fire", 1, 7)), _Part->m_Pos, _Part->m_Sca * 2, Random(0, 359), 0.31);
			Part->SetScale(Vec2(-0.5, -0.5) * _Scale, 1.02);
			Part->SetLight(20, D3DCOLOR_XRGB(255, 224, 130));
		};
	}
	CAMERA->Shake(3 * _Scale, 1 * _Scale);
}
