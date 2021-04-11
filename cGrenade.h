#pragma once
class cGrenade : public cComponent
{
public:
	cGrenade();
	~cGrenade();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Z;
	float m_Speed;
	float m_ZSpeed;
	float m_Timer;
	Vec2 m_Start;
	Vec2 m_End;
};

