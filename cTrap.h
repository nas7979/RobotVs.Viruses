#pragma once
class cTrap : public cComponent
{
public:
	cTrap();
	~cTrap();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

