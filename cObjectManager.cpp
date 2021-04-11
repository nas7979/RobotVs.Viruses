#include "DXUT.h"
#include "cObjectManager.h"


cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::Init()
{
}

void cObjectManager::Update()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter = m_Objects[Tag].begin(); iter != m_Objects[Tag].end();)
		{
			if ((*iter)->m_Destroyed)
			{
				(*iter)->Release();
				delete *iter;
				iter = m_Objects[Tag].erase(iter);
			}
			else
			{
				(*iter)->Update();
				CheckCollision(*iter);
				iter++;
			}
		}
	}
}

void cObjectManager::Render()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Render();
		}
	}
}

void cObjectManager::Release()
{
	for (int Tag = 0; Tag < Obj_End; Tag++)
	{
		for (auto& iter : m_Objects[Tag])
		{
			iter->Release();
			delete iter;
		}
		m_Objects[Tag].clear();
	}
}

cObject * cObjectManager::AddObject(string _Name, Vec2 _Pos, float _Depth, ObjectTag _Tag)
{
	cObject* a = new cObject;
	a->m_Name = _Name;
	a->m_Pos = _Pos;
	a->m_Depth = _Depth;
	a->m_Tag = _Tag;
	m_Objects[_Tag].push_back(a);
	return a;
}

void cObjectManager::CheckCollision(cObject * _Object)
{
	cBoxCollider* Box = _Object->GC(cBoxCollider);
	cCollider* Other;
	if (Box != nullptr)
	{
		if (Box->m_Enable == false)
			return;
		Vec2 Pos;
		for (auto& Tag : Box->m_Collwith)
		{
			for (auto& iter : m_Objects[Tag])
			{
				Other = iter->GC(cCollider);
				if (Other == nullptr || Other->m_Enable == false)
					continue;

				Pos = Vec2(Clamp(iter->m_Pos.x, _Object->m_Pos.x - Box->m_Size.x, _Object->m_Pos.x + Box->m_Size.x), Clamp(iter->m_Pos.y, _Object->m_Pos.y - Box->m_Size.y, _Object->m_Pos.y + Box->m_Size.y));
				if (PointDistance(iter->m_Pos, Pos) <= Other->m_Radius)
				{
					Box->m_CollFunc(iter);
				}
			}
		}
	}
	else
	{
		cCollider* Circle = _Object->GC(cCollider);
		if (Circle == nullptr || Circle->m_Enable == false)
			return;

		for (auto& Tag : Circle->m_CollWith)
		{
			for (auto& iter : m_Objects[Tag])
			{
				Other = iter->GC(cCollider);
				if (Other == nullptr || Other->m_Enable == false || Other == Circle)
					continue;

				if (PointDistance(_Object->m_Pos, iter->m_Pos) <= Circle->m_Radius + Other->m_Radius)
				{
					Circle->m_CollFunc(iter);
				}
			}
		}
	}
}
