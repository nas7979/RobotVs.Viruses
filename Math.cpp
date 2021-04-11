#include "DXUT.h"
#include "Math.h"


float Math::Clamp(float _Val, float _Min, float _Max)
{
	return max(_Min, min(_Val, _Max));
}

int Math::Random(int _Min, int _Max)
{
	if (_Max == 0)
	{
		_Max = 1;
	}
	return _Min + (rand() | (rand() << 16)) % (_Max - _Min + 1);
}

float Math::Random(float _Min, float _Max)
{
	return Random((int)(_Min * 10000), (int)(_Max * 10000)) * 0.0001;
}

float Math::Sign(float _Val)
{
	if (_Val > 0)
		return 1;
	if (_Val < 0)
		return -1;
	return 0;
}

char * Math::RandomText(string _Text, int _Min, int _Max)
{
	sprintf(StaticText, "%s%d", _Text.c_str(), Random(_Min, _Max));
	return StaticText;
}

Vec2 Math::RotateVec(Vec2 _Vec, float _Rot)
{
	float Rot = D3DXToRadian(_Rot);
	return Vec2(_Vec.x * cos(Rot) + _Vec.y * -sin(Rot), _Vec.x * sin(Rot) + _Vec.y * cos(Rot));
}

float Math::PointDirection(Vec2 _v1, Vec2 _v2)
{
	return D3DXToDegree(atan2(_v2.y - _v1.y, _v2.x - _v1.x));
}

Vec2 Math::PointDirectionVec(Vec2 _v1, Vec2 _v2)
{
	Vec2 Dir;
	D3DXVec2Normalize(&Dir, &(_v2 - _v1));
	return Dir;
}

float Math::PointDistance(Vec2 _v1, Vec2 _v2)
{
	return D3DXVec2Length(&(_v2 - _v1));
}
