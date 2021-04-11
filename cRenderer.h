#pragma once
class cRenderer : public cComponent
{
public:
	cRenderer();
	~cRenderer();

	// cComponent��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	Texture* m_Image = nullptr;
	D3DCOLOR m_Color = 0xffffffff;
};

