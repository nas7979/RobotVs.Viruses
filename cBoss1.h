#pragma once
#include "cEnemy.h"
class cBoss1 : public cEnemy
{
public:
	cBoss1();
	~cBoss1();

	// cEnemy을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
	float m_Blocked;

	void DealDamage(float _Damage, Vec2 _Force = Vec2(0,0));
};

