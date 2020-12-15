#include "gameover.h"


gameover::gameover(void)
{
		D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/ending.bmp",
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
		&BG_texture);
}
gameover::~gameover(void)
{
	BG_texture->Release();
}

void gameover::rander()
{
	RECT rc = {0,0,800,600};
	D3DXVECTOR3 Pos(0,0,0);
	g_pSprite->Draw(BG_texture,
		&rc,
		NULL,
		&Pos,
		D3DCOLOR_RGBA(255,255,255,255));
}

bool gameover::update()
{
	if(g_InputMgr->IsKeyPushing(DIK_SPACE))
	{
		return false;
	}
	return true;
}