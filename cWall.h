#pragma once
class cWall : public cComponent
{
public:
	cWall();
	~cWall();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

