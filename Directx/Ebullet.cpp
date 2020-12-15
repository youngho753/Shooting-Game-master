#include "Ebullet.h"


Ebullet::Ebullet(float x,float y,float px,float py,int speed)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/bullet.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,
		NULL,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,NULL,NULL,
		&Bullet_texture);

	X = x;
	Y = y;
	this->px = px;
	this->py = py;
	this->speed = speed;
	SetRect(&BRECT,X,X+10,Y,Y+10);
}
Ebullet::~Ebullet(void)
{
	if(Bullet_texture)
		Bullet_texture->Release();
}

void Ebullet::rander()
{
	RECT rc={0,0,10,10};
	D3DXVECTOR3 Pos(X,Y,0);
	g_pSprite->Draw(Bullet_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
}
int Ebullet::update()
{
	double ar = atan2(py - Y, px - X);

	X = X + speed*cos(ar);
	Y = Y + speed*sin(ar);
	SetRect(&BRECT, X, Y, X+100, Y+150);

	if(X > 600 || X < -10 || Y > 600 || Y < -10)
		return 0;
	return 1;
}