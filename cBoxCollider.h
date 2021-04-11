#pragma once
class cBoxCollider : public cComponent
{
public:
	cBoxCollider();
	~cBoxCollider();

	// cComponent을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Vec2 m_Size;
	RECT m_Rect;
	vector<ObjectTag> m_Collwith;
	function<void(cObject* _Other)> m_CollFunc;
};

