#pragma once
class cWall : public cComponent
{
public:
	cWall();
	~cWall();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

