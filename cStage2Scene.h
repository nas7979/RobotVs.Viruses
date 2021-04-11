#pragma once
class cStage2Scene : public cScene
{
public:
	cStage2Scene();
	~cStage2Scene();

	// cScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

