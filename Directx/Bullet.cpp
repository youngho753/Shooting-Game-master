#include "Bullet.h"

Bullet::Bullet(float _X, float _Y)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/bullet.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,
		NULL,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,NULL,NULL,
		&Bullet_texture);

	X=_X;
	Y=_Y;

	mfAccumTime=0.0f;
}
Bullet::~Bullet(void)
{
	if(Bullet_texture)
		Bullet_texture->Release();
}

void Bullet::rander()
{
	RECT rc={0,0,10,10};
	D3DXVECTOR3 Pos(X,Y,0);
	g_pSprite->Draw(Bullet_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
}
int Bullet::update(float dt)
{
	mfAccumTime+=dt;
	if(mfAccumTime<0.1f)
	{
		if(Y<=0.0f)
		{
			return 1;
		}

		Y-=15.0f;
		mfAccumTime=0.0f;
	}
	return 0;
}