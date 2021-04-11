#pragma once
#include "cVirus.h"
class cVirusBlue : public cVirus
{
public:
	cVirusBlue();
	~cVirusBlue();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

