#pragma once
#include "d3d.h"

class Item
{
private:
	LPDIRECT3DTEXTURE9 Item_texture;
	float X,Y;
	RECT rect;
public:
	Item(void);
	~Item(void);
	int update(RECT prect);
	void rander();
	bool Collision(RECT rc1, RECT rc2);
};

