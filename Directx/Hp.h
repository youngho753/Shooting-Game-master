#pragma once
#include "d3d.h"


class Hp
{
private:
	LPDIRECT3DTEXTURE9 Hp_texture;
	int num;

public:
	Hp();
	~Hp();
	bool update(int);
	void rander(int);
};

