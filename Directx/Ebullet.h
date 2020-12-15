#pragma once
#include "d3d.h"

class Ebullet
{
private:
	LPDIRECT3DTEXTURE9 Bullet_texture;
	float X,Y;
	float px,py;
	RECT BRECT;
	int speed;
public:
	Ebullet(float x,float y,float px,float py,int speed=2);
	~Ebullet(void);
	int update();
	void rander();
	RECT getRECT()
	{
		SetRect(&BRECT, X, Y, X+20, Y+20);
		return BRECT;
	}
};
