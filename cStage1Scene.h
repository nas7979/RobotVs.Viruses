#pragma once
class cStage1Scene : public cScene
{
public:
	cStage1Scene();
	~cStage1Scene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

