#pragma once
#include "cBullet.h"
#include "cPlayer.h"
class cEnemy : public cComponent
{
public:
	cEnemy();
	~cEnemy();

	// cComponent을(를) 통해 상속됨
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;

	float m_Hp;
	float m_MaxHp;
	float m_Speed;
};

