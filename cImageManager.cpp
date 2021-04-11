#include "DXUT.h"
#include "cImageManager.h"


cImageManager::cImageManager()
{
}


cImageManager::~cImageManager()
{
}

void cImageManager::Init()
{
	D3DXCreateSprite(g_Device, &m_Sprite);
	D3DXCreateFont(g_Device, 64, 0, 0, 1, 0, DEFAULT_CHARSET, 0, 0, 0, L"µÕ±Ù¸ð²Ã", &m_Font);
	LPD3DXBUFFER Error = nullptr;
	D3DXCreateEffectFromFileA(g_Device, "./LightShader.fx", nullptr, nullptr, D3DXSHADER_DEBUG, nullptr, &m_LightShader, &Error);
}

void cImageManager::Update()
{
}

void cImageManager::Render()
{
}

void cImageManager::Release()
{
	for (auto& iter : m_Images)
	{
		iter.second->Image->Release();
		delete iter.second;
	}
	for (auto& iter : m_Animations)
	{
		delete iter.second;
	}
	m_LightTex->Release();
	m_LightSuf->Release();
	m_Font->Release();
	m_Sprite->Release();
	m_LightShader->Release();
}

void cImageManager::Begin()
{
	m_Sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	g_Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_NONE);
	g_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_NONE);
}

void cImageManager::End()
{
	m_Sprite->End();
}

void cImageManager::OnLostDevice()
{
	m_Sprite->OnLostDevice();
	m_LightShader->OnLostDevice();
}

void cImageManager::OnResetDevice()
{
	m_Sprite->OnResetDevice();
	m_LightShader->OnResetDevice();
	LPDIRECT3DSURFACE9 Original;
	D3DSURFACE_DESC Desc;
	g_Device->GetRenderTarget(0, &Original);
	Original->GetDesc(&Desc);
	g_Device->CreateTexture(Desc.Width, Desc.Height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_LightTex, nullptr);
	m_LightTex->GetSurfaceLevel(0, &m_LightSuf);
	Original->Release();
}

void cImageManager::RenderLight()
{
	Texture* Light = IMAGE->Find("Light");
	LPDIRECT3DSURFACE9 Original;
	g_Device->GetRenderTarget(0, &Original);

	g_Device->SetRenderTarget(0, m_LightSuf);
	Begin();
	g_Device->Clear(0, nullptr, D3DCLEAR_TARGET, 0x00000000, 0, 1);
	CAMERA->Render();

	for (auto& iter : m_Lights)
	{
		CenterRender(Light, iter->Pos, Vec2(1, 1) * (iter->Radius / 50), 0, 0.2, iter->Color);
	}

	End();

	g_Device->SetRenderTarget(0, Original);

	m_LightShader->SetTexture((D3DXHANDLE)"LightTexture", m_LightTex);
	m_LightShader->SetFloat((D3DXHANDLE)"Darkness", m_Darkness);

	UINT num = 0;
	m_LightShader->Begin(&num, 0);
	for (int i = 0; i < num; i++)
	{
		Begin();
		m_LightShader->BeginPass(i);

		D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &Vec2(1, 1), NULL, 0, &Vec2(0, 0));
		m_Mat._43 = 0.2;
		m_Sprite->SetTransform(&m_Mat);
		m_Sprite->Draw(m_LightTex, nullptr, nullptr, nullptr, 0xffffffff);

		m_LightShader->EndPass();
		End();
	}
	m_LightShader->End();
	Original->Release();
}

Texture * cImageManager::Find(string _Key)
{
	return m_Images[_Key];
}

vector<Texture*>* cImageManager::FindAnimation(string _Key)
{
	return m_Animations[_Key];
}

void cImageManager::AddImage(string _Key, string _Path)
{
	Texture* Tex = new Texture;
	if (D3DXCreateTextureFromFileExA(g_Device, _Path.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, 0, &Tex->Info, 0, &Tex->Image) == S_OK)
	{
		m_Images.insert(make_pair(_Key, Tex));
		return;
	}
	delete Tex;
}

void cImageManager::AddAnimation(string _Key)
{
	vector<Texture*>* Vec = new vector<Texture*>;
	char Text[64];
	for (int i = 1; true; i++)
	{
		sprintf(Text, "%s%d", _Key.c_str(), i);
		auto Find = m_Images.find(Text);
		if (Find != m_Images.end())
		{
			Vec->push_back(Find._Ptr->_Myval.second);
		}
		else
		{
			break;
		}
	}
	m_Animations.insert(make_pair(_Key, Vec));
}

Light * cImageManager::AddLight(float _Radius, D3DCOLOR _Color)
{
	Light* a = new Light;
	a->Radius = _Radius;
	a->Color = _Color;
	m_Lights.push_back(a);
	a->Iter = m_Lights.end();
	a->Iter--;
	return a;
}

void cImageManager::DeleteLight(Light * _Light)
{
	m_Lights.erase(_Light->Iter);
	delete _Light;
}

void cImageManager::Render(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, nullptr, nullptr, nullptr, _Color);
}

void cImageManager::CenterRender(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	m_Center = Vec2(_Image->Info.Width * 0.5f, _Image->Info.Height * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, nullptr, nullptr, nullptr, _Color);
}

void cImageManager::RenderRect(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, &_Rect, nullptr, nullptr, _Color);
}

void cImageManager::CenterRenderRect(Texture * _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, RECT _Rect, D3DCOLOR _Color, bool _View)
{
	m_Center = Vec2(_Image->Info.Width * 0.5f, _Image->Info.Height * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Sprite->Draw(_Image->Image, &_Rect, nullptr, nullptr, _Color);
}

void cImageManager::RenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth,D3DCOLOR _Color, bool _View)
{
	D3DXMatrixTransformation2D(&m_Mat, NULL, 0, &_Scale, NULL, D3DXToRadian(_Rot), &(_Pos));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, NULL, DT_NOCLIP, _Color);
}

void cImageManager::CenterRenderText(wstring _Text, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color, bool _View)
{
	m_Rect.left = m_Rect.top = 0;
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, &m_Rect, DT_CALCRECT, _Color);
	m_Center = Vec2(m_Rect.right * 0.5f, m_Rect.bottom * 0.5f);
	D3DXMatrixTransformation2D(&m_Mat, &m_Center, 0, &_Scale, &m_Center, D3DXToRadian(_Rot), &(_Pos - m_Center));
	if (_View)m_Mat *= CAMERA->m_InversedMat;
	m_Mat._43 = _Depth;
	m_Sprite->SetTransform(&m_Mat);
	m_Font->DrawTextW(m_Sprite, _Text.c_str(), -1, NULL, DT_NOCLIP | DT_CENTER | DT_VCENTER, _Color);
}
