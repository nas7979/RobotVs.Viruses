#include "DXUT.h"
#include "cPartFunc.h"


cPartFunc::cPartFunc()
{
}


cPartFunc::~cPartFunc()
{
}

void cPartFunc::Update()
{
	m_Timer += DT;
	if (m_Timer >= m_FuncSpeed)
	{
		m_Timer = 0;
		m_Func(this);
	}
}
