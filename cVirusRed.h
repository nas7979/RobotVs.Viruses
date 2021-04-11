#pragma once
#include "cVirus.h"
class cVirusRed : public cVirus
{
public:
	cVirusRed();
	~cVirusRed();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

