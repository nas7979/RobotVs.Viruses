#pragma once
class cTitleScene : public cScene
{
public:
	cTitleScene();
	~cTitleScene();

	// cScene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

