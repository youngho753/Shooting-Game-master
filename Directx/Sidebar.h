#pragma once
#include "d3d.h"
#include "score.h"
#include "Hp.h"
using namespace std;
#define MAXSCO 8

class Sidebar
{
private:
	LPDIRECT3DTEXTURE9 Sidebar_texture,Score_texture;
	score *nowsco,*presco;
	Hp hp;
	
	ifstream in;
	ofstream out;
public:
	Sidebar(void);
	~Sidebar(void);
	void rander();
	bool update(int);
	void scoreup()
	{	nowsco->scoreup(100);	}
};

