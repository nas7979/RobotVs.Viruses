#pragma once
#include "cPlayer.h"
#include "cBullet.h"
class cWep : public cComponent
{
public:
	cWep();
	virtual ~cWep();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Dir;
	cObject* m_Player;
	float m_RecoilPos;
	float m_RecoilVel;
	bool m_FireAble;
};

