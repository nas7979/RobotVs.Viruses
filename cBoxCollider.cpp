#include "DXUT.h"
#include "cBoxCollider.h"


cBoxCollider::cBoxCollider()
{
}


cBoxCollider::~cBoxCollider()
{
}

void cBoxCollider::Init()
{
}

void cBoxCollider::Update()
{
	m_Rect.left = m_Owner->m_Pos.x - m_Size.x;
	m_Rect.right = m_Owner->m_Pos.x + m_Size.x;
	m_Rect.top = m_Owner->m_Pos.y - m_Size.y;
	m_Rect.bottom = m_Owner->m_Pos.y + m_Size.y;
}

void cBoxCollider::Render()
{
}

void cBoxCollider::Release()
{
}
