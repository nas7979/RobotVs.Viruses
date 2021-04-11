#pragma once
#include "cEnemy.h"
class cVirus : public cEnemy
{
public:
	cVirus();
	~cVirus();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Scale;
	float m_MergeChance;
	int m_Size;
	bool m_Vaccine;
	float m_Debuff;
	bool m_Merged;

	void DealDamage(float _Damage, Vec2 _Force);
};

