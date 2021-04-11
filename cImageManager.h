#pragma once
#include "cSingleton.h"
struct Light
{
	float Radius;
	D3DCOLOR Color;
	Vec2 Pos;
	list<Light*>::iterator Iter;
};
struct Texture
{
	LPDIRECT3DTEXTURE9 Image;
	D3DXIMAGE_INFO Info;
};
class cImageManager : public cSingleton<cImageManager>
{
public:
	cImageManager();
	~cImageManager();

	void Init();
	void Update();
	void Render();
	void Release();
	void Begin();
	void End();
	void OnLostDevice();
	void OnResetDevice();
	void RenderLight();

	map<string, Texture*> m_Images;
	map<string, vector<Texture*>*> m_Animations;
	LPD3DXSPRITE m_Sprite;
	LPD3DXFONT m_Font;
	LPDIRECT3DSURFACE9 m_LightSuf = nullptr;
	LPDIRECT3DTEXTURE9 m_LightTex = nullptr;
	LPD3DXEFFECT m_LightShader;
	list<Light*> m_Lights;
	RECT m_Rect;
	Vec2 m_Center;
	Matrix m_Mat;
	float m_Darkness = 0;

	Texture* Find(string _Key);
	vector<Texture*>* FindAnimation(string _Key);
	void AddImage(string _Key, string _Path);
	void AddAnimation(string _Key);
	Light* AddLight(float _Radius, D3DCOLOR _Color);
	void DeleteLight(Light* _Light);

	void Render(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRender(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void RenderRect(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRenderRect(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void RenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
	void CenterRenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff, bool _View = false);
};

#define IMAGE cImageManager::GetInstance()