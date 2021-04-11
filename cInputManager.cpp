#include "DXUT.h"
#include "cInputManager.h"


cInputManager::cInputManager()
{
}


cInputManager::~cInputManager()
{
}

void cInputManager::Init()
{
}

void cInputManager::Update()
{
	memcpy(m_Old, m_Cur, 128);
	memset(m_Cur, false, 128);

	for (int i = 0; i < 128; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			m_Cur[i] = true;
		}
	}

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	m_MousePos = Vec2(pt.x, pt.y);
	m_WorldMousePos = Vec2(CAMERA->m_Pos.x - (960 - pt.x) / CAMERA->m_Scale, CAMERA->m_Pos.y - (540 - pt.y) / CAMERA->m_Scale);
}

void cInputManager::Render()
{
}

void cInputManager::Release()
{
}
