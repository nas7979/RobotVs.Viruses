#pragma once
class cPart : public cPartBase
{
public:
	cPart();
	~cPart();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Release() override;

	Light* m_Light = nullptr;
	float m_Radius;

	void SetLight(float _Radius, D3DCOLOR _Color);
};

