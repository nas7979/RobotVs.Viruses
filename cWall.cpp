#include "DXUT.h"
#include "cWall.h"


cWall::cWall()
{
}


cWall::~cWall()
{
}

void cWall::Init()
{
	AC(cBoxCollider)->m_Collwith.push_back(Obj_Player);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_PlayerBullet);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_Enemy);
	GC(cBoxCollider)->m_Collwith.push_back(Obj_EnemyBullet);
	GC(cBoxCollider)->m_CollFunc = [&](cObject* _Other)->void {
		switch (_Other->m_Tag)
		{
		case Obj_Player:
		case Obj_Enemy:
			_Other->m_Pos -= (_Other->GC(cRigidBody)->m_Velocity + _Other->GC(cRigidBody)->m_Speed) * DT;
			break;

		case Obj_PlayerBullet:
		case Obj_EnemyBullet:
			_Other->m_Destroyed = true;
			break;
		}
	};
}

void cWall::Update()
{
}

void cWall::Render()
{
}

void cWall::Release()
{
}
