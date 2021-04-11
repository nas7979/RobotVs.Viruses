#include "DXUT.h"
#include "cPartText.h"


cPartText::cPartText()
{
}


cPartText::~cPartText()
{
}

void cPartText::Render()
{
	IMAGE->CenterRenderText(m_Text, m_Pos, m_Sca, m_Rot, m_Depth, m_Color, m_Depth <= 0.1 ? true : false);
}
