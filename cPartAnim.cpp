#include "DXUT.h"
#include "cPartAnim.h"


cPartAnim::cPartAnim()
{
}


cPartAnim::~cPartAnim()
{
}

void cPartAnim::Update()
{
	m_Frame += (1 / m_Speed) * DT;
	if (m_Frame >= m_Anim->size())
	{
		m_Alp = 0;
	}
	else
	{
		m_Image = (*m_Anim)[(int)m_Frame];
	}
}
