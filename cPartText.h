#pragma once
class cPartText : public cPartBase
{
public:
	cPartText();
	~cPartText();

	virtual void Render() override;

	wstring m_Text;
};

