#include "DXUT.h"
#include "cBox.h"
#include "cBullet.h"
#include "cTrap.h"

cBox::cBox()
{
}


cBox::~cBox()
{
}

void cBox::Init()
{
	m_Image = Random(1, 3);
	Texture* Image = IMAGE->Find("Box" + to_string(m_Image) + "_1");
	AC(cRenderer)->m_Image = Image;
	AC(cBoxCollider)->m_Size = Vec2(Image->Info.Width * 0.4, Image->Info.Height * 0.4);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_Player);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_Enemy);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_PlayerBullet);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_EnemyBullet);
	GC(cBoxCollider)->m_CollFunc = [&](cObject* _Other)->void {
		switch (_Other->m_Tag)
		{
		case Obj_Player:
		case Obj_Enemy:
		{
			_Other->m_Pos += D3DXVec2Length(&(_Other->GC(cRigidBody)->m_Velocity + _Other->GC(cRigidBody)->m_Speed)) * 1 * PointDirectionVec(m_Owner->m_Pos, _Other->m_Pos) * DT;
		}break;

		case Obj_PlayerBullet:
		case Obj_EnemyBullet:
		{
			_Other->m_Destroyed = true;
			m_Hp -= _Other->GC(cBullet)->m_Damage;
		}break;
		}
	};

	m_Hp = 300;
}

void cBox::Update()
{
	if (m_Hp <= 100)
	{
		GC(cRenderer)->m_Image = IMAGE->Find("Box" + to_string(m_Image) + "_2");
		if (m_Hp <= 0)
		{
			m_Owner->m_Destroyed = true;
			cPart* Part;
			Vec2 Pos;
			SOUND->Play(RandomText("Box_Break", 1, 5));
			for (int i = 0; i < 20; i++)
			{
				Pos = Vec2(Random(-30, 30), Random(-30, 30));
				Part = PART->AddParticle<cPart>(IMAGE->Find(RandomText("Box_Gibs", 1, 6)), m_Owner->m_Pos + Pos, Vec2(1, 1) * Random(0.75f, 1.25f), Random(0, 359), 0.81);
				Part->SetPos(Random(50, 250), 0.96, PointDirection(m_Owner->m_Pos, Part->m_Pos));
				Part->SetRot(Random(-2000, 2000), 0.95);
			}

			switch (Random(0, 8))
			{
			case 0: OBJECT->AddObject("Spike", m_Owner->m_Pos, 0.51, Obj_Trap)->AC(cTrap); break;
			case 1: OBJECT->AddObject("Mine", m_Owner->m_Pos, 0.51, Obj_Trap)->AC(cTrap); break;
			case 2: OBJECT->AddObject("Trap", m_Owner->m_Pos, 0.51, Obj_Trap)->AC(cTrap); break;
			}
		}
	}
}

void cBox::Render()
{
}

void cBox::Release()
{
}
