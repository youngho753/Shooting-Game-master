#pragma once
#include "d3d.h"
#include "InputMgr.h"
using namespace std;

extern CInputMgr* g_InputMgr;
class gameover
{
private:
	LPDIRECT3DTEXTURE9 BG_texture;
public:
	gameover(void);
	~gameover(void);
	bool update();
	void rander();
};