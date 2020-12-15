#include "Hp.h"


Hp::Hp(void)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/hp.png",
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0xff000300,
		NULL,
		NULL,
		&Hp_texture);

	num = 5;
}
Hp::~Hp(void)
{
	Hp_texture->Release();
}

bool Hp::update(int inp)
{
	if(inp < 0)
		return false;
	
	num = inp;
	return true;
}
void Hp::rander(int location)
{
	for(int i=0;i<num;i++)
	{
		RECT rc= {0,0,20,20};
		D3DXVECTOR3 Pos((i*20)+620+(i*5),location,0);
		g_pSprite->Draw(Hp_texture,
			&rc,
			NULL,
			&Pos,
			D3DCOLOR_RGBA(255,255,255,255));
	}
}