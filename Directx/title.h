#pragma once
#include "d3d.h"
#include "InputMgr.h"
using namespace std;

extern CInputMgr* g_InputMgr;

class title
{
private:
	LPDIRECT3DTEXTURE9 BG_texture,MK_texture,Menu_texture;
	float X,Y;
	int sw;

public:
	title(void);
	~title(void);
	int update(float dt);
	void rander();

};
