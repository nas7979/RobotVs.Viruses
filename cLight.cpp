#include "DXUT.h"
#include "cLight.h"


cLight::cLight()
{
}


cLight::~cLight()
{
}

void cLight::Init()
{
}

void cLight::Update()
{
	m_Light->Pos = m_Owner->m_Pos;
	m_Light->Radius = m_Radius * m_Owner->m_Scale.x;
}

void cLight::Render()
{
}

void cLight::Release()
{
	IMAGE->DeleteLight(m_Light);
}

void cLight::Set(float _Radius, D3DCOLOR _Color)
{
	m_Radius = _Radius;
	m_Light = IMAGE->AddLight(_Radius, _Color);
}
