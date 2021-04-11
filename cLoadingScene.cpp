#include "DXUT.h"
#include "cLoadingScene.h"


cLoadingScene::cLoadingScene()
{
}


cLoadingScene::~cLoadingScene()
{
}

void cLoadingScene::Init()
{
	LoadImage("");
	LoadImage("Bullet");
	LoadImage("Effect");
	LoadImage("Enemy");
	LoadImage("Enemy/Boss1");
	LoadImage("Enemy/Boss2");
	LoadImage("Item");
	LoadImage("Player");
	LoadImage("Stage");
	LoadImage("Stage/Stage1");
	LoadImage("Stage/Stage2");
	LoadImage("UI");
	LoadImage("UI/Button");
	LoadImage("UI/Hp");
	LoadImage("UI/Pannel");
	LoadImage("UI/GameStart");
	LoadImage("UI/Stage2Start");
	LoadImage("UI/Window");

	LoadSound("");

	SCENE->ChangeScene("STAGE1");
}

void cLoadingScene::Update()
{
}

void cLoadingScene::Render()
{
}

void cLoadingScene::Release()
{
}

void cLoadingScene::LoadImage(string _Path)
{
	string Searching = "./Resource/Image/" + _Path + "/*.png";
	string Key = "";
	string CurAnim = "";
	string Temp = "";
	int Count = 0;
	int Text = 100;

	_finddata_t Find;
	long Handle = _findfirst(Searching.c_str(), &Find);
	do
	{
		Key = Find.name;
		for (int i = 0; i < 4; i++)
		{
			Key.pop_back();
		}
		Temp.assign(Key.c_str(), min(Text, Key.size()));
		if (Count != 0 && (CurAnim != Temp || abs((int)Key.size() - (int)Temp.size()) > 2))
		{
			IMAGE->AddAnimation(CurAnim);
			CurAnim = "";
			Count = 0;
		}
		if ((CurAnim == "" && Key.back() == '1') || (abs((int)Key.size() - (int)Temp.size()) > 2))
		{
			CurAnim = Key;
			CurAnim.pop_back();
			Text = CurAnim.size();
			Count = 1;
		}
		if (Count != 0)
		{
			Count++;
		}
		IMAGE->AddImage(Key, "./Resource/Image/" + _Path + "/" + Find.name);
	} while (_findnext(Handle, &Find) != -1);
	if (CurAnim != "")
	{
		IMAGE->AddAnimation(CurAnim);
	}
	_findclose(Handle);
}

void cLoadingScene::LoadSound(string _Path)
{
	string Searching = "./Resource/Sound/" + _Path + "/*.wav";
	string Key = "";

	_finddata_t Find;
	long Handle = _findfirst(Searching.c_str(), &Find);
	do
	{
		Key = Find.name;
		for (int i = 0; i < 4; i++)
		{
			Key.pop_back();
		}
		SOUND->AddSound(Key, "./Resource/Sound/" + _Path + "/" + Find.name);
	} while (_findnext(Handle, &Find) != -1);
	_findclose(Handle);
}
