#pragma once
class cRigidBody : public cComponent
{
public:
	cRigidBody();
	~cRigidBody();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
	Vec2 m_Velocity;
	Vec2 m_Speed;
	Vec2 m_Force;
	float m_Mass;
	float m_Friction;

	void AddForce(Vec2 _Force);
	void SetMass(float _Mass, float _Friction = 0.97);

};

