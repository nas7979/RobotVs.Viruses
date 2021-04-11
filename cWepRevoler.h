#pragma once
#include "cWep.h"
class cWepRevoler : public cWep
{
public:
	cWepRevoler();
	~cWepRevoler();

	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

