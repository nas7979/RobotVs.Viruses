#pragma once
#include "cComponent.h"
enum ObjectTag
{
	Obj_Player,
	Obj_Weapon,
	Obj_Enemy,
	Obj_PlayerBullet,
	Obj_EnemyBullet,
	Obj_Item,
	Obj_Map,
	Obj_Trap,
	Obj_None,
	Obj_End
};
class cObject
{
public:
	cObject();
	~cObject();

	void Init();
	void Update();
	void Render();
	void Release();

	Vec2 m_Pos;
	Vec2 m_Scale = Vec2(1, 1);
	string m_Name;
	ObjectTag m_Tag;
	float m_Rot = 0;
	float m_Depth;
	float* m_Alarm = nullptr;
	int m_AlarmSize = 0;
	bool m_Destroyed = false;
	function<void(int _Index)> m_AlarmFunc;
	list<cComponent*> m_Components;

	void SetAlarmSize(int _Size);
	void SetAlarm(int _Index, float _Time);

	template<typename T>
	T* AddComponent()
	{
		T* a = new T;
		a->m_Owner = this;
		m_Components.push_back(a);
		a->Init();
		return a;
	}

	template<typename T>
	T* GetComponent()
	{
		for (auto& iter : m_Components)
		{
			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}

		T* Cast = nullptr;
		for (auto& iter : m_Components)
		{
			Cast = dynamic_cast<T*>(iter);
			if (Cast != nullptr)
			{
				return Cast;
			}
		}
		return nullptr;
	}
};

