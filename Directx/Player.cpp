#include "Player.h"


Player::Player(void)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/player/preload.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,
		NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,
		NULL,NULL,
		&Player_dtexture);
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/player/pshoot.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,
		NULL,NULL,
		&Player_stexture);
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/boom.jpg",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		D3DCOLOR_RGBA(0,0,0,255),
		NULL,NULL,
		&Player_dani);

	speed = 8;
	bullettime = 0.07f;
	mfAccumTime = mfAccumTime1 = 0.0f;
	framenumber = sframenumber = 0;
	df1 = df2 = 0;
	PX = 400.0f;
	PY = 400.0f;
	hp = 3;
	state = NORMAL;
	leftbullet = 10;
}
Player::~Player(void)
{
	if(Player_dtexture)
		Player_dtexture->Release();
	if(Player_stexture)
		Player_stexture->Release();
	if(Player_dani)
		Player_dani->Release();
	li.clear();
}

void Player::rander()
{
	if(state == NORMAL)
	{
		RECT rc = {102*framenumber,0,102*(framenumber+1),124};
		D3DXVECTOR3 Pos(PX,PY,0);
		g_pSprite->Draw(Player_dtexture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
	}
	else if(state == SHOT)
	{
		RECT rc = {82*sframenumber,0,82*(sframenumber+1),124};
		D3DXVECTOR3 Pos(PX,PY,0);
		g_pSprite->Draw(Player_stexture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));
	}
	else if(state == DIE)
	{	
		RECT rct = {df1*128,df2*128,(df1+1)*128,(df2+1)*128};
		D3DXVECTOR3 Post(PX,PY,0);
		g_pSprite->Draw(Player_dani,&rct,NULL,&Post,D3DCOLOR_RGBA(255,255,255,255) );
	}

	for(it=li.begin();it!=li.end();it++)
		it->rander();
}
bool Player::update(float dt)
{
	mfAccumTime += dt;
	mfAccumTime1+=dt;

	if(state != DIE)
	{
		if(g_InputMgr->IsKeyPushing(DIK_RIGHT))
		{
			PX+=speed;
			if(PX>=536)
				PX=536;
		}
		if(g_InputMgr->IsKeyPushing(DIK_LEFT))
		{
			PX-=speed;
			if(PX<=0)
				PX=0;
		}
		if(g_InputMgr->IsKeyPushing(DIK_UP))
		{
			PY-=speed;
			if(PY<=0)
				PY=0;
		}
		if(g_InputMgr->IsKeyPushing(DIK_DOWN))
		{
			PY += speed;
			if(PY>=536)
				PY=536;
		}

		if(g_InputMgr->IsKeyPushing(DIK_LSHIFT))
			speed = 4;
		else
			speed = 8;

		if(mfAccumTime1>=bullettime)
		{
			if(g_InputMgr->IsKeyPushing(DIK_Z) && leftbullet > 0)
			{
				li.push_back(*(new Bullet(PX+40,PY-20)));
				li.push_back(*(new Bullet(PX+55,PY-20)));
				state = SHOT;
				leftbullet -= dt;
			}
			else
				state = NORMAL;
			mfAccumTime1=0.0f;
		}
		SetRect(&PLAYERRECT, PX, PY, PX+63, PY+64);
	}

	if(mfAccumTime>0.1f)
	{
		if(state == NORMAL)
		{
			framenumber++;
			if(framenumber>4)
				framenumber = 0;
		}
		else if(state == SHOT)
		{
			sframenumber++;
			if(sframenumber > 2)
				sframenumber = 0;
		}
		else if(state == DIE)
		{
			df1++;
			if(df1 > 4)
			{
				df1 = 0;
				df2++;
				if(df2 > 2)
					df2 = 0;
			}
			if(df1 == 4 && df2 == 2)
			{
				state = NORMAL;
				PX = 300;
				PY = 400;
			}
			SetRect(&PLAYERRECT, 800,0,800,0);
		}
		mfAccumTime = 0.0f;
	}

	for(it=li.begin();it!=li.end();)
	{
		if(it->update(dt))
		{
			it=li.erase(it);
			continue;
		}
		it++;
	}
	return true;
}
