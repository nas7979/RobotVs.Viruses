#include "DXUT.h"
#include "cStage1Scene.h"
#include "cPlayer.h"
#include "cVirusGreen.h"
#include "cVirusBlue.h"
#include "cVirusRed.h"
#include "cVirusPurple.h"
#include "cBox.h"
#include "cWall.h"

cStage1Scene::cStage1Scene()
{
}


cStage1Scene::~cStage1Scene()
{
}

void cStage1Scene::Init()
{
	CAMERA->m_Pos = Vec2(345, 375);
	CAMERA->m_Scale = 3;
	CAMERA->m_TargetScale = 3;
	CAMERA->m_FollowPlayer = true;
	IMAGE->m_Darkness = 0.5;

	OBJECT->AddObject("Player", Vec2(345, 375), 0.5, Obj_Player)->AC(cPlayer);

	for (int i = 0; i < 0; i++)
	{
		OBJECT->AddObject("VirusGreen", Vec2(Random(0,700), Random(0,700)), 0.5, Obj_Enemy)->AC(cVirusGreen);
	}

	for (int i = 0; i < 30; i++)
	{
		OBJECT->AddObject("Box", Vec2(Random(50, 640), Random(100, 700)), 0.6, Obj_Map)->AC(cBox);
	}

	cObject* a = OBJECT->AddObject("Wall", Vec2(-100, 0), 0, Obj_Map);
	a->AC(cWall);
	a->GC(cBoxCollider)->m_Size = Vec2(100, 1000);
	a = OBJECT->AddObject("Wall", Vec2(790, 0), 0, Obj_Map);
	a->AC(cWall);
	a->GC(cBoxCollider)->m_Size = Vec2(100, 1000);
	a = OBJECT->AddObject("Wall", Vec2(0, -20), 0, Obj_Map);
	a->AC(cWall);
	a->GC(cBoxCollider)->m_Size = Vec2(1000, 100);
	a = OBJECT->AddObject("Wall", Vec2(0, 850), 0, Obj_Map);
	a->AC(cWall);
	a->GC(cBoxCollider)->m_Size = Vec2(1000, 100);
}

void cStage1Scene::Update()
{
	if (CAMERA->m_FollowPlayer)
	{
		float Dist = PointDistance(OBJECT->m_Player->m_Pos, INPUT->m_WorldMousePos);
		Vec2 Dir = PointDirectionVec(OBJECT->m_Player->m_Pos, INPUT->m_WorldMousePos);
		Dir = OBJECT->m_Player->m_Pos + Dir * Clamp(Dist, 0, 75);
		CAMERA->m_Pos = Lerp<Vec2>(CAMERA->m_Pos, Vec2(Clamp(Dir.x, 330, 690 - 330), Clamp(Dir.y, 190, 750 - 190)), 0.1);
	}
}

void cStage1Scene::Render()
{
	IMAGE->Render(IMAGE->Find("Stage2"), Vec2(0, 0), Vec2(1, 1), 0, 0.9);
}

void cStage1Scene::Release()
{
}
