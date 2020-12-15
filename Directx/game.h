#pragma once
#include "d3d.h"
#include "InputMgr.h"
#include "Player.h"
#include "Enemy.h"
#include "Sidebar.h"
#include "Item.h"
#include "Ebullet.h"
#include <list>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

extern CInputMgr* g_InputMgr;

class game
{
private:
	LPDIRECT3DTEXTURE9 BG_texture;
	Player *player;
	Sidebar *sidebar;
	float X,Y;
	float mfAccumTime2,mfAccumTime,tcheck;
	float timeflowcheck;

	list<Enemy> li_1;
	list<Enemy>::iterator it_1;

	list<Item> li_item;
	list<Item>::iterator it_item;

	list<Ebullet> li_b;
	list<Ebullet>::iterator it_b;
	int rad,p1,p2;
	float mftime;
	bool flag;
public:
	int update(float dt);
	void rander();
	game(void);
	~game(void);
};