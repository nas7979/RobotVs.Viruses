#pragma once
class cStage2Scene : public cScene
{
public:
	cStage2Scene();
	~cStage2Scene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

