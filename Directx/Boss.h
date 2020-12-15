#pragma once
#include "d3d.h"
#include <list>

class Boss
{
private:
	LPDIRECT3DTEXTURE9 Boss_texture;
	float X, Y, px, py;
	int speed, framenumber;
	float mfAccumTime;
	RECT PRect;
public:

	Boss(float x, float y,int px,int py,int speed = 5);
	~Boss();
	bool CheckCollision(RECT rectPlayer);
	bool Collision(RECT rectEnemy, RECT rectPlayer);
	int update(float dt);
	void rander();
	inline POINT getPoint()
	{
		POINT p = {X,Y};
		return p;
	}
	inline void changePoint(float x,float y)
	{
		px = x;
		py = y;
	}
};

