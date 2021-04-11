#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadingScene.h"
#include "cStage1Scene.h"
#include "cStage2Scene.h"
#include "cResultScene.h"
#include "cTitleScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	IMAGE->CreateInstance();
	SOUND->CreateInstance();
	SYSTEM->CreateInstance();
	OBJECT->CreateInstance();
	SCENE->CreateInstance();
	PART->CreateInstance();
	INPUT->CreateInstance();
	CAMERA->CreateInstance();
	SCHEDULE->CreateInstance();

	SCENE->AddScene("LOADING", new cLoadingScene);
	SCENE->AddScene("STAGE1", new cStage1Scene);
	SCENE->AddScene("STAGE2", new cStage2Scene);
	SCENE->AddScene("TITLE", new cTitleScene);
	SCENE->AddScene("RESULT", new cResultScene);

	SCENE->ChangeScene("LOADING");
}

void cMainGame::Update()
{
	INPUT->Update();
	SCENE->Update();
	OBJECT->Update();
	PART->Update();
	SYSTEM->Update();
	CAMERA->Update();
	SOUND->Update();
	SCHEDULE->Update();
}

void cMainGame::Render()
{
	IMAGE->Begin();

	CAMERA->Render();
	SCENE->Render();
	OBJECT->Render();
	PART->Render();

	IMAGE->RenderText(to_wstring(DXUTGetFPS()), Vec2(10, 10), Vec2(1, 1), 0, 0.1, 0xffffffff, true);

	IMAGE->End();
	IMAGE->RenderLight();

	IMAGE->Begin();
	CAMERA->Render();
	SYSTEM->Render();
	IMAGE->End();
}

void cMainGame::Release()
{
	SYSTEM->ReleaseInstance();
	OBJECT->ReleaseInstance();
	SCENE->ReleaseInstance();
	PART->ReleaseInstance();
	INPUT->ReleaseInstance();
	CAMERA->ReleaseInstance();
	SCHEDULE->ReleaseInstance();
	IMAGE->ReleaseInstance();
	SOUND->ReleaseInstance();
}

void cMainGame::OnLostDevice()
{
	IMAGE->OnLostDevice();
}

void cMainGame::OnResetDevice()
{
	IMAGE->OnResetDevice();
}
