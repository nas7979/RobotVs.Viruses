#pragma once
namespace Math
{
	static char StaticText[256];
	template<typename T>
	T Lerp(T _S, T _E, float _T)
	{
		return _S + (_E - _S) * _T * 60 * DT;
	}

	float Clamp(float _Val, float _Min, float _Max);
	int Random(int _Min, int _Max);
	float Random(float _Min, float _Max);
	float Sign(float _Val);
	char* RandomText(string _Text, int _Min, int _Max);
	Vec2 RotateVec(Vec2 _Vec, float _Rot);
	float PointDirection(Vec2 _v1, Vec2 _v2);
	Vec2 PointDirectionVec(Vec2 _v1, Vec2 _v2);
	float PointDistance(Vec2 _v1, Vec2 _v2);
}
