#pragma once
class cCameraManager : public cSingleton<cCameraManager>
{
public:
	cCameraManager();
	~cCameraManager();

	void Init();
	void Update();
	void Render();
	void Release();

	Vec2 m_Pos;
	Vec2 m_ShakePos;
	float m_ShakeForce;
	float m_ShakeTime;
	float m_Scale;
	Vec2 m_TargetPos;
	float m_TargetScale;
	bool m_FollowPlayer;
	Matrix m_Mat;
	Matrix m_InversedMat;

	void Shake(float _Force, float _Time);
};

#define CAMERA cCameraManager::GetInstance()