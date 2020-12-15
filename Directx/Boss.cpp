#include "Boss.h"

Boss::Boss(float x, float y,int px,int py,int speed)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/Boss.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000300,NULL,NULL,
		&Boss_texture);

	X = x;
	Y = y;
	this->px = px;
	this->py = py;
	this->speed = speed;
	mfAccumTime = 0.0f;
}
Boss::~Boss(void)
{
	if(Boss_texture)
		Boss_texture->Release();
}

void Boss::rander()
{
	RECT rc = {100*framenumber,0,100*(framenumber+1),150};
	D3DXVECTOR3 Pos(X,Y,0);
	g_pSprite->Draw(Boss_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
}
int Boss::update(float dt)
{
	mfAccumTime+=dt;
	if(mfAccumTime>0.1f)
	{
	}
	return 0;
}

bool Boss::CheckCollision(RECT rectPlayer)
{
	if(Collision(PRect, rectPlayer))
	{
		return true;
	}
	return false;
}
bool Boss::Collision(RECT rectEnemy, RECT rectPlayer)
{
	if(rectPlayer.right>rectEnemy.left&&
		rectPlayer.top<rectEnemy.bottom&&
		rectPlayer.bottom>rectEnemy.top&&
		rectPlayer.left<rectEnemy.right)
	{return true;}
	return false;
}
