#pragma once
class cLight : public cComponent
{
public:
	cLight();
	~cLight();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Light* m_Light = nullptr;
	float m_Radius;
	
	void Set(float _Radius, D3DCOLOR _Color);
};

