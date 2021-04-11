#pragma once
class cPartFunc : public cPartBase
{
public:
	cPartFunc();
	~cPartFunc();

	virtual void Update() override;

	function<void(cPartFunc* _Part)> m_Func;
	float m_FuncSpeed;
	float m_Timer = 0;
};

