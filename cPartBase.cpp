#include "DXUT.h"
#include "cPartBase.h"


cPartBase::cPartBase()
{
}


cPartBase::~cPartBase()
{
}

void cPartBase::Init()
{
}

void cPartBase::Update()
{
}

void cPartBase::Render()
{
	if(m_Image)
	IMAGE->CenterRender(m_Image, m_Pos, m_Sca, m_Rot, m_Depth, m_Color);
}

void cPartBase::Release()
{
}

void cPartBase::SetPos(float _Vel, float _Fri, float _Dir)
{
	m_PosVel = _Vel;
	m_PosFri = _Fri;
	m_Dir = _Dir;
}

void cPartBase::SetScale(Vec2 _Vel, float _Fri)
{
	m_ScaVel = _Vel;
	m_ScaFri = _Fri;
}

void cPartBase::SetRot(float _Vel, float _Fri)
{
	m_RotVel = _Vel;
	m_RotFri = _Fri;
}

void cPartBase::SetAlpha(float _Alpha, float _Vel, float _Fri)
{
	m_Alp = _Alpha;
	m_AlpVel = _Vel;
	m_AlpFri = _Fri;
}
