#pragma once
class cBullet : public cComponent
{
public:
	cBullet();
	~cBullet();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Dir;
	float m_Speed;
	float m_Damage;
	float m_Friction;
	float m_EndSpeed;
	float m_PartColor[3];

	void SetColor(float _R, float _G, float _B);
};

