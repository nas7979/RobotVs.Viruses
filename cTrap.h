#pragma once
class cTrap : public cComponent
{
public:
	cTrap();
	~cTrap();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

