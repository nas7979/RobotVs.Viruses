#pragma once
class cPartAnim : public cPartBase
{
public:
	cPartAnim();
	~cPartAnim();

	virtual void Update() override;

	float m_Frame = 0;
	float m_Speed = 1;
	vector<Texture*>* m_Anim;
};

