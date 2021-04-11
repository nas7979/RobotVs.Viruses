#include "DXUT.h"
#include "cRigidBody.h"


cRigidBody::cRigidBody()
{
}


cRigidBody::~cRigidBody()
{
}

void cRigidBody::Init()
{
	SetMass(1);
	m_Force = Vec2(0, 0);
	m_Velocity = Vec2(0, 0);
	m_Speed = Vec2(0, 0);
}

void cRigidBody::Update()
{
	m_Velocity *= pow(m_Friction, 60 * DT);
	m_Owner->m_Pos += m_Velocity * DT;
	m_Owner->m_Pos += m_Speed * DT;
	m_Force = (m_Velocity + m_Speed) * m_Mass;
}

void cRigidBody::Render()
{
	m_Speed = Vec2(0, 0);
}

void cRigidBody::Release()
{
}

void cRigidBody::AddForce(Vec2 _Force)
{
	m_Velocity += _Force / m_Mass;
}

void cRigidBody::SetMass(float _Mass, float _Friction)
{
	m_Mass = _Mass;
	m_Friction = pow(_Friction, 1 / _Mass);
}
