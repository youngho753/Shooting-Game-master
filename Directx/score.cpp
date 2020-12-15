#include "score.h"


score::score(int fis)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/numbers2.png",
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		0xff000000,
		NULL,
		NULL,
		&Number_texture);

	nowscore = fis;
	count = 0;

	if(fis)
	{	
		int temp = fis;
		for(int i=MAXSCO-1;i>=0;i--)
		{
			int res = temp%10;
			sco[i] = res;
			temp = temp/10;
		}
	}
	else
	{
		for(int i=0;i<MAXSCO;i++)
			sco[i] = 0;
	}

//	for(int i=0;i<MAXSCO;i++)
//		sco[i] = 0;
}
score::~score()
{
	Number_texture->Release();
}

void score::scoreup(int inp)
{
	nowscore += inp;
	count += 100;
}
void score::update()
{
	int temp = nowscore,res;

	for(int i=MAXSCO-1;i>=0;i--)
	{
		sco[i] = 0;
		res = temp%10;
		sco[i] = res;
		temp = temp/10;
	}
	
}
void score::rander(int location)
{
	for(int i=0;i<MAXSCO;i++)
	{
		RECT rc2 = {18*sco[i],0,18*(sco[i]+1),30};
		if(sco[i] > 4)
		{
			rc2.left -= 2;
			rc2.right -= 2;
		}	
		D3DXVECTOR3 Pos2((i*20)+620,location,0);
		g_pSprite->Draw(Number_texture,
			&rc2,
			NULL,
			&Pos2,
			D3DCOLOR_RGBA(255,255,255,255));
	}
}