#include "Item.h"


Item::Item(void)
{
		D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/abitem.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,
		NULL,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,NULL,NULL,
		&Item_texture);

		X = rand()%500;
		Y = 0;
		SetRect(&rect,X,X+13,Y,Y+13);
}
Item::~Item(void)
{
	if(Item_texture)
		Item_texture->Release();
}

void Item::rander()
{
	RECT rc={0,0,13,13};
	D3DXVECTOR3 Pos(X,Y,0);
	g_pSprite->Draw(Item_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
}
int Item::update(RECT prect)
{
	Y += 2;
	if(Y > 600)
		return 0;

	SetRect(&rect,X,X+13,Y,Y+13);

	if(Collision(prect,rect))
		return 2;

	return 1;
}

bool Item::Collision(RECT rc1, RECT rc2)
{
	if(rc1.right>rc2.left && rc1.left<rc2.right && rc1.top<rc2.bottom && rc1.bottom>rc2.top)
		return true;

	return false;
}
