#pragma once
class cCollider : public cComponent
{
public:
	cCollider();
	~cCollider();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	float m_Radius;
	vector<ObjectTag> m_CollWith;
	function<void(cObject* _Other)> m_CollFunc;
};

