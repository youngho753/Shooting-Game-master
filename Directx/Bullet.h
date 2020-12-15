#pragma once
#include "d3d.h"

class Bullet
{
private:
	LPDIRECT3DTEXTURE9 Bullet_texture;
	float X,Y;
	float px,py;
	float mfAccumTime;
	RECT BRECT;

public:
	Bullet(float _X, float _Y);
	~Bullet(void);
	int update(float dt);
	void rander();
	RECT getRECT()
	{
		SetRect(&BRECT, X, Y, X+20, Y+20);
		return BRECT;
	}
};
