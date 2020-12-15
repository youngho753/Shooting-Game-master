#include "Enemy.h"

//	enum {NONE,RANDOM,LINE,NOR,CIRCLE,CSECT,HELIX};

Enemy::Enemy(float x, float y,int px,int py,int speed)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/enemy_l.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000300,NULL,NULL,
		&Enemy_texture);
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/enemy.bmp",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		D3DCOLOR_RGBA(0,0,0,255),NULL,NULL,
		&Enemy_dani);

	X = x;
	Y = y;
	this->px = px;
	this->py = py;
	this->speed = speed;
	df1 = df2 = framenumber = 0;
	mfAccumTime = 0.0f;
	status = NORMAL;
}
Enemy::~Enemy(void)
{
	if(Enemy_texture)
		Enemy_texture->Release();
	if(Enemy_dani)
		Enemy_dani->Release();
}

void Enemy::rander()
{
	if(status == NORMAL)
	{
		RECT rc = {100*framenumber,0,100*(framenumber+1),150};
		D3DXVECTOR3 Pos(X,Y,0);
		g_pSprite->Draw(Enemy_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
	}
	else if(status == DIEANI)
	{
		RECT rct = {df1*95.8,df2*95.8,(df1+1)*95.8,(df2+1)*95.8};
		D3DXVECTOR3 Post(X,Y,0);
		g_pSprite->Draw(Enemy_dani,&rct,NULL,&Post,D3DCOLOR_RGBA(255,255,255,255));
	}

}
int Enemy::update(float dt)
{
	mfAccumTime+=dt;
	if(status == NORMAL)
	{
		if(mfAccumTime>0.1f)
		{
			framenumber++;
			if(framenumber>2)
				framenumber=0;

			mfAccumTime=0.0f;
		}

		double ar = atan2(py - Y, px - X);

		X = X + speed*cos(ar);
		Y = Y + speed*sin(ar);
		SetRect(&PRect, X, Y, X+100, Y+150);
	}
	else if(status == DIEANI)
	{
		if(mfAccumTime > 0.05f)
		{
			df1++;
			if(df1 > 4)
			{
				df1 = 0;
				df2++;
				if(df2 > 3)
					df2 = 0;
			}

			if(df1 == 4 && df2 == 3)
				status = DIE;

			SetRect(&PRect, 800, 0, 800, 0);

			mfAccumTime=0.0f;
		}
	}

	if(Y>=600 || X>=600 || X<=(-30) || status == DIE)
		return 1;
	return 0;
}

bool Enemy::CheckCollision(RECT rectPlayer)
{
	if(Collision(PRect, rectPlayer))
	{
		return true;
	}
	return false;
}
bool Enemy::Collision(RECT rectEnemy, RECT rectPlayer)
{
	if(rectPlayer.right>rectEnemy.left&&
		rectPlayer.top<rectEnemy.bottom&&
		rectPlayer.bottom>rectEnemy.top&&
		rectPlayer.left<rectEnemy.right)
	{return true;}
	return false;
}
