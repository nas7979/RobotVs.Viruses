#pragma once
struct Animation
{
	vector<Texture*>* Anim;
	float Speed;
	int Size;
	bool Loop;
	string Key;
	vector<string> Notify;
};
class cAnimation : public cComponent
{
public:
	cAnimation();
	~cAnimation();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	map<string, Animation*> m_Animations;
	float m_Speed;
	float m_Frame;
	int m_Last;
	Animation* m_CurAnim;
	function<void(string _Key)> m_OnAnimationEnd = nullptr;
	function<void(string _Key)> m_OnAnimationNotify = nullptr;

	void AddAnimation(string _Key, string _Resource, float _Speed, bool _Loop = true);
	void AddNotify(string _Anim, int _Frame, string _Key);
	void SetAnimation(string _Key);
};

