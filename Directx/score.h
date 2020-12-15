#pragma once
#include "d3d.h"
#define MAXSCO 8


class score
{
private:
	LPDIRECT3DTEXTURE9 Number_texture;
	int sco[7];
	int count,nowscore;
public:
	score(int=0);
	~score(void);
	void update();
	void rander(int);
	void scoreup(int inp);
	int getscore()
	{	return nowscore;	}
	void setscore(int inp)
	{	nowscore = inp;	}

};