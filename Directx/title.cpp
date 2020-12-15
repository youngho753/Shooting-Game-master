#include "title.h"


title::title(void)
{
		D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/start/start.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000300,NULL,NULL,
		&BG_texture);

		D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/start/ebutton.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		NULL,NULL,NULL,
		&Menu_texture);

		D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/start/mark.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		NULL,NULL,NULL,
		&MK_texture);

		X = 520.0f;
		Y = 310.0f;
		sw = 1;
}
title::~title(void)
{
	if(BG_texture)
		BG_texture->Release();
	if(MK_texture)
		MK_texture->Release();
}

void title::rander()
{
	RECT rc = {0,0,800,600};
	D3DXVECTOR3 Pos(0,0,0);
	g_pSprite->Draw(BG_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));

	RECT rc1 = {0,0,60,60};
	D3DXVECTOR3 Pos1(X,Y+(sw*100),0);
	g_pSprite->Draw(MK_texture,&rc1,NULL,&Pos1,D3DCOLOR_RGBA(255,255,255,255));

	RECT rc2 = {0,0,500,500};
	D3DXVECTOR3 Pos2(440,350,0);
	g_pSprite->Draw(Menu_texture,&rc2,NULL,&Pos2,D3DCOLOR_RGBA(255,255,255,255));

}

int title::update(float dt)
{
	if(g_InputMgr->IsKeyPushing(DIK_UP))
		sw = 1;
	if(g_InputMgr->IsKeyPushing(DIK_DOWN))
		sw = 2;
	if(g_InputMgr->IsKeyPushing(DIK_Z))
	{
		switch(sw)
		{
		case 1:
			return 0;
		case 2:
			return 1;
		}
	}
	return 3;
}