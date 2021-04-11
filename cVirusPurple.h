#pragma once
#include "cVirus.h"
class cVirusPurple : public cVirus
{
public:
	cVirusPurple();
	~cVirusPurple();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

