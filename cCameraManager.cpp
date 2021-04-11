#include "DXUT.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Init()
{
	m_TargetScale = 1;
	m_ShakePos = Vec2(0, 0);
	m_ShakeForce = 0;
}

void cCameraManager::Update()
{
	if (m_ShakeForce != 0)
	{
		m_ShakeForce -= m_ShakeTime * DT;
		if (m_ShakeForce <= 0)
		{
			m_ShakeForce = 0;
			m_ShakePos = Vec2(0, 0);
		}
		else
		{
			m_ShakePos = Vec2(Random(-m_ShakeForce, m_ShakeForce), Random(-m_ShakeForce, m_ShakeForce));
		}
	}

	Matrix p, s;
	D3DXMatrixTranslation(&p, -m_Pos.x + 960 / m_Scale + m_ShakePos.x, -m_Pos.y + 540 / m_Scale + m_ShakePos.y, 0);
	D3DXMatrixScaling(&s, m_Scale, m_Scale, 1);
	m_Mat = p * s;
	D3DXMatrixInverse(&m_InversedMat, NULL, &m_Mat);
}

void cCameraManager::Render()
{
	g_Device->SetTransform(D3DTS_VIEW, &m_Mat);
}

void cCameraManager::Release()
{
}

void cCameraManager::Shake(float _Force, float _Time)
{
	if (_Force > m_ShakeForce)
	{
		m_ShakeForce = _Force;
		m_ShakeTime = _Force / _Time;
	}
}
