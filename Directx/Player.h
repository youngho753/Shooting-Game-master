#pragma once
#include "d3d.h"
#include "InputMgr.h"
#include "Bullet.h"
#include <conio.h>
#include <list>
using namespace std;

extern CInputMgr* g_InputMgr;

class Player
{
private:
	enum { NORMAL, SHOT, DIE };

	LPDIRECT3DTEXTURE9 Player_dtexture,Player_stexture,Player_dani;
	int speed, hp, state, leftbullet;
	int framenumber, sframenumber,df1,df2;
	float mfAccumTime, mfAccumTime1;
	float bullettime, PX, PY;
	RECT PLAYERRECT;
public:

	list<Bullet> li;
	list<Bullet>::iterator it;

	Player(void);
	~Player(void);	
	bool update(float dt);
	void rander();

	inline void setStateDie()
	{	state = DIE;	}
	inline void sethp(int inp)
	{	hp += inp;	}
	inline void setleftbullet()
	{
		if(leftbullet < 20)
		leftbullet += 3;
	}
	inline int gethp()
	{	return hp;	}
	inline POINT getpoint()
	{
		POINT p = {PX,PY};
		return p;
	}
	inline RECT getRect()
	{	return PLAYERRECT;	}
	inline int getState()
	{	return state;	}
};