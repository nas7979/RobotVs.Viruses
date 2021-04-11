#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet()
{
}


cBullet::~cBullet()
{
}

void cBullet::Init()
{
	AC(cRenderer);
	AC(cCollider);
	AC(cLight);
	m_Friction = 1;
	m_EndSpeed = 0;
}

void cBullet::Update()
{
	m_Speed *= pow(m_Friction, DT * 60);
	if (m_Friction > 1)
	{
		if (m_Speed >= m_EndSpeed)
		{
			m_Friction = 1;
			m_Speed = m_EndSpeed;
		}
	}
	else
	{
		if (m_Speed <= m_EndSpeed)
		{
			m_Friction = 1;
			m_Speed = m_EndSpeed;
		}
	}
	m_Owner->m_Pos += RotateVec(Vec2(m_Speed, 0), m_Dir) * DT;
	m_Owner->m_Rot = m_Dir;
}

void cBullet::Render()
{
}

void cBullet::Release()
{
	float Rand;
	D3DCOLOR Color;
	cPart* Part;
	for (int i = 0; i < 10; i++)
	{
		Rand = Random(0.f, 1.f);
		Color = D3DCOLOR_XRGB(255 - (int)(m_PartColor[0] * Rand), 255 - (int)(m_PartColor[1] * Rand), 255 - (int)(m_PartColor[2] * Rand));
		Part = PART->AddParticle<cPart>(IMAGE->Find("Point"), m_Owner->m_Pos, Vec2(1, 1) * Random(4.f, 8.f), Random(0, 359), 0.3, Color);
		Part->SetLight(3, Color);
		Part->SetRot(Random(-2000, 2000), 0.95);
		Part->SetPos(Random(100, 300), Random(0.93f, 0.95f), Random(0, 359));
		Part->SetScale(Vec2(-3, -3), 1.05);
	}
	Part = PART->AddParticle<cPart>(NULL, m_Owner->m_Pos, Vec2(1, 1), 0, 0.3);
	Part->SetLight(150, D3DCOLOR_XRGB((int)m_PartColor[0], (int)m_PartColor[1], (int)m_PartColor[2]));
	Part->SetAlpha(255, -255 * 5, 1);
}

void cBullet::SetColor(float _R, float _G, float _B)
{
	m_PartColor[0] = 255 - _R;
	m_PartColor[1] = 255 - _G;
	m_PartColor[2] = 255 - _B;
}
