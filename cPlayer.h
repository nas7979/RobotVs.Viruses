#pragma once
struct Buff
{
	float Damage;
	float Speed;
	float AttackSpeed;
	float Scale;
	float Time;
	string Key;
};
class cPlayer : public cComponent
{
public:
	cPlayer();
	~cPlayer();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Hp;
	float m_MaxHp;
	float m_Speed;
	float m_Vaccine;
	float m_Charge;
	bool m_Charging;
	cObject* m_ChargeTarget;
	bool m_IsShield;
	float m_Shield;
	float m_Damage;
	float m_Scale;
	float m_Damaged;
	float m_AttackSpeed;
	cObject* m_Wep;
	float m_Dash;
	Vec2 m_DashDir;
	bool m_Reloading;
	bool m_Dead;
	list<Buff*> m_Buffs;

	void AddBuff(string _Key, float _Time, float _Speed, float _AttackSpeed, float _Scale, float _Damage);
	void DealDamage(float _Damage);
};

