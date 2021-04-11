#include "DXUT.h"
#include "cPart.h"


cPart::cPart()
{
}


cPart::~cPart()
{
}

void cPart::Init()
{
}

void cPart::Update()
{
	if (m_Light)
	{
		m_Light->Pos = m_Pos;
		m_Light->Radius = m_Radius * m_Sca.x;
		m_Light->Color = (m_Light->Color & 0x00ffffff) | ((int)min(255, m_Alp) << 24);
	}
}

void cPart::Release()
{
	if (m_Light)
	{
		IMAGE->DeleteLight(m_Light);
	}
}

void cPart::SetLight(float _Radius, D3DCOLOR _Color)
{
	m_Radius = _Radius;
	m_Light = IMAGE->AddLight(_Radius, _Color);
}
