#pragma once
#include "cPartBase.h"
#include "cPartAnim.h"
#include "cPartText.h"
#include "cPartFunc.h"
#include "cPart.h"
class cParticleManager : public cSingleton<cParticleManager>
{
public:
	cParticleManager();
	~cParticleManager();

	void Init();
	void Update();
	void Render();
	void Release();

	list<cPartBase*> m_Particles;
	
	template<typename T>
	T* AddParticle(Texture* _Image, Vec2 _Pos, Vec2 _Scale, float _Rot, float _Depth, D3DCOLOR _Color = 0xffffffff)
	{
		T* a = new T;
		a->m_Image = _Image;
		a->m_Pos = _Pos;
		a->m_Sca = _Scale;
		a->m_Rot = _Rot;
		a->m_Depth = _Depth;
		a->m_Color = _Color;
		a->Init();
		m_Particles.push_back(a);
		return a;
	}

	void Explosion(Vec2 _Pos, float _Scale, int _Amount = 6);
};

#define PART cParticleManager::GetInstance()