#pragma once
class cBox : public cComponent
{
public:
	cBox();
	~cBox();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Hp;
	int m_Image;
};

