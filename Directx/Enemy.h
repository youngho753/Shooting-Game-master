#pragma once
#include "d3d.h"
#include "Ebullet.h"
#include <list>

class Enemy
{
private:
	enum {NORMAL,DIEANI,DIE};

	LPDIRECT3DTEXTURE9 Enemy_texture,Enemy_dani;
	float X, Y, px, py;
	int speed, framenumber, df1,df2, status;
	float mfAccumTime;
	RECT PRect;
public:

	Enemy(float x, float y,int px,int py,int speed = 4);
	~Enemy();
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
	inline void changeStatusDie()
	{	status = DIEANI;	}

};

