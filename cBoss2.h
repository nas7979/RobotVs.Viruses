#pragma once
#include "cEnemy.h"
class cBoss2 : public cEnemy
{
public:
	cBoss2();
	~cBoss2();

	// cEnemy��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;



	void DealDamage(float _Damage, Vec2 _Force = Vec2(0, 0));
};

