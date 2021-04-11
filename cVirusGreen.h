#pragma once
#include "cVirus.h"
class cVirusGreen : public cVirus
{
public:
	cVirusGreen();
	~cVirusGreen();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

