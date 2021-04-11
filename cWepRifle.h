#pragma once
#include "cWep.h"
class cWepRifle : public cWep
{
public:
	cWepRifle();
	~cWepRifle();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

