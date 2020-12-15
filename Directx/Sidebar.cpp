#include "Sidebar.h"


Sidebar::Sidebar(void)
{	
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/side.bmp",
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
		&Sidebar_texture);

	in.open("data/score.txt",ios::in);
	int sco;
	in >> sco;
	in.close();

	nowsco = new score();
	presco = new score(sco);
}
Sidebar::~Sidebar(void)
{
	Sidebar_texture->Release();

	out.open("data/score.txt",ios::app | ios::out);
	out <<endl<<nowsco->getscore();
	out.close();

	delete nowsco;
	delete presco;
}

bool Sidebar::update(int nhp)
{
	nowsco->update();
	if(presco->getscore() <= nowsco->getscore())
		presco->setscore(nowsco->getscore());
	presco->update();


	if(hp.update(nhp) == false)
		return false;

	return true;
}
void Sidebar::rander()
{	
	RECT rc={0,0,200,600};
	D3DXVECTOR3 Pos(600,0,0);
	g_pSprite->Draw(Sidebar_texture,
		&rc,
		NULL,
		&Pos,
		D3DCOLOR_RGBA(255,255,255,255));

	presco->rander(70);
	nowsco->rander(100);
	
	hp.rander(130);
}