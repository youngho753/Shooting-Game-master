#include "game.h"

game::game(void)
{
	D3DXCreateTextureFromFileEx(
		g_pd3dDevice,
		"pic/บุด็.png",
		D3DX_DEFAULT,D3DX_DEFAULT,D3DX_DEFAULT,NULL,
		D3DFMT_UNKNOWN,D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,D3DX_FILTER_NONE,
		0xff000000,NULL,NULL,
		&BG_texture);

	player = new Player();
	sidebar = new Sidebar();

	X = 0.0f;
	Y = 2000.0f;
	mfAccumTime = mfAccumTime2 = tcheck = 0.0f;
	timeflowcheck = 140.0f;
	mftime = 0.0f;
	rad = 0;
	flag = true;
	p1 = rand()%600;
	p2 = rand()%600;
	PlaySound("data/SHK - T-SERIAL.wav", NULL, SND_ASYNC|SND_LOOP);
}
game::~game(void)
{
	BG_texture->Release();
	li_1.clear();
	li_item.clear();
	li_b.clear();
	delete player;
	delete sidebar;
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
}

void game::rander()
{
	RECT rc = {0,0,850,2000};
	D3DXVECTOR3 Pos(X,Y,0);
	g_pSprite->Draw(BG_texture,&rc,NULL,&Pos,D3DCOLOR_RGBA(255,255,255,255));

	RECT rc1 = {0,0,850,2000};
	D3DXVECTOR3 Pos1(X,Y-2000,0);
	g_pSprite->Draw(BG_texture,&rc1,NULL,&Pos1,D3DCOLOR_RGBA(255,255,255,255));

	for(it_1=li_1.begin();it_1!=li_1.end();it_1++)
		it_1->rander();

	player->rander();

	for(it_b=li_b.begin();it_b!=li_b.end();it_b++)
		it_b->rander();

	for(it_item=li_item.begin();it_item!=li_item.end();it_item++)
		it_item->rander();

	sidebar->rander();

}

int game::update(float dt)
{
	tcheck += dt;
	mfAccumTime+=dt;
	mfAccumTime2+=dt;
	timeflowcheck+=dt;
	mftime += dt;

	if(tcheck > 0.005f)
	{
		Y -= 1;

		tcheck = 0.0f;

		player->update(dt);

		if(mfAccumTime > 2.0f)
		{
			li_item.push_back(*( new Item() ) );
			li_item.push_back(*( new Item() ) );
			mfAccumTime = 0.0f;
		}

		if(timeflowcheck < 15.0f)
		{
			if(mfAccumTime2 > 0.6f)
			{
				li_1.push_back(*( new Enemy(10,0,650,650) ));
				li_1.push_back(*( new Enemy(500,0,-50,650) ));
				mfAccumTime2=0.0f;
			}
			if(mftime > 0.5f)
			{
				while(rad <= 360)
				{
					li_b.push_back(*new Ebullet(p2,p1,cos(rad)*1000,sin(rad)*1000,2) );
					rad += 25;
				}
				rad = 0;
				if((int)timeflowcheck % 4 == 0)
				{
					p1 = rand()%600;
					p2 = rand()%600;
				}
				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 20.0f)
		{ }
		else if(timeflowcheck < 35.0f)
		{
			if(mfAccumTime2 > 0.5f)
			{
				if(timeflowcheck < 25.0f)
					li_1.push_back(*( new Enemy(50,0,0,650)));
				else if(timeflowcheck < 30.0f)
					li_1.push_back(*( new Enemy(250,0,250,650)));
				else
					li_1.push_back(*( new Enemy(500,0,500,650)));
				mfAccumTime2=0.0f;
			}
			if(mftime > 0.05f)
			{
				if(timeflowcheck < 25.0f)
				{
					li_b.push_back(*(new Ebullet(100,200,cos(rad)*1000,sin(rad)*1000) ) );
					li_b.push_back(*(new Ebullet(500,200,cos(rad)*1000,sin(rad)*1000) ) );
				}
				else if(timeflowcheck < 30.0f)
				{
					li_b.push_back(*(new Ebullet(100,200,cos(rad)*1000,sin(rad)*1000) ) );
					li_b.push_back(*(new Ebullet(300,200,cos(rad)*1000,sin(rad)*1000) ) );
				}
				else if(timeflowcheck < 35.0f)
				{
					li_b.push_back(*(new Ebullet(300,200,cos(rad)*1000,sin(rad)*1000) ) );
					li_b.push_back(*(new Ebullet(500,200,cos(rad)*1000,sin(rad)*1000) ) );
				}
				rad += 13;
				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 40.0f)
		{ }
		else if(timeflowcheck < 55.0f)
		{
			if(mfAccumTime2 > 0.6f)
			{
				li_1.push_back(*( new Enemy(0,40,250,100)));
				mfAccumTime2 = 0.0f;
			}
			if(mftime > 0.3f)
			{
				int x = rand()%600;

				li_b.push_back(*new Ebullet(100,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(100,100,x,650,3) );
				li_b.push_back(*new Ebullet(100,100,x+30,650,3) );

				x = rand()%600;
				li_b.push_back(*new Ebullet(500,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(500,100,x,650,3) );
				li_b.push_back(*new Ebullet(500,100,x+30,650,3) );

				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 60.0f)
		{ }
		else if(timeflowcheck < 75.0f)
		{
			if(mfAccumTime2 > 0.6f)
			{
				li_1.push_back(*( new Enemy(500,40,250,100)));
				mfAccumTime2 = 0.0f;
			}
			if(mftime > 0.3f)
			{
				int x = rand()%600;

				li_b.push_back(*new Ebullet(100,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(100,100,x,650,3) );
				li_b.push_back(*new Ebullet(100,100,x+30,650,3) );

				x = rand()%600;
				li_b.push_back(*new Ebullet(500,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(500,100,x,650,3) );
				li_b.push_back(*new Ebullet(500,100,x+30,650,3) );

				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 80.0f)
		{ }
		else if(timeflowcheck < 95.0f)
		{
			if(mfAccumTime2 > 0.6f)
			{
				li_1.push_back(*( new Enemy(500,0,0,100) ));
				mfAccumTime2 = 0.0f;
			}
			if(mftime > 0.3f)
			{
				li_b.push_back(*new Ebullet(30,0,rand()%600,640,2) );
				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 100.0f)
		{ }
		else if(timeflowcheck < 115.0f)
		{
			if(mfAccumTime2 > 0.6f)
			{
				li_1.push_back(*( new Enemy(0,0,500,100) ));
				mfAccumTime2 = 0.0f;
			}
		}/////////////////////////////////////////
		else if(timeflowcheck < 120.0f)
		{ }
		else if(timeflowcheck < 135.0f)
		{
			if(mfAccumTime2 > 1.5f)
			{
				li_1.push_back(*( new Enemy(250, -30, 300, 650) ));
				li_1.push_back(*( new Enemy(250,-30,-50,650) ));
				li_1.push_back(*( new Enemy(250,-30,650,650) ));
				mfAccumTime2 = 0.0f;
			}
			if(mftime > 1.5f)
			{
				int x = rand()%600;
				for(int i=1;i<=5;i++)
				{
					li_b.push_back(*new Ebullet(300,0,x,800,i) );
				}
				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 140.0f)
		{ }
		else if(timeflowcheck < 155.0f)
		{
			if(mfAccumTime2 > 1.5f)
			{
				li_1.push_back(*( new Enemy(500, -30, 0, 200) ));
				li_1.push_back(*( new Enemy(0, -30, 500, 200) ));
				mfAccumTime2 = 0.0f;
			}
			if(mftime > 0.3f)
			{
				int x = rand()%600;

				li_b.push_back(*new Ebullet(100,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(100,100,x,650,3) );
				li_b.push_back(*new Ebullet(100,100,x+30,650,3) );

				x = rand()%600;
				li_b.push_back(*new Ebullet(500,100,x-30,650,3) );
				li_b.push_back(*new Ebullet(500,100,x,650,3) );
				li_b.push_back(*new Ebullet(500,100,x+30,650,3) );

				mftime = 0.0f;
			}
		}
		else if(timeflowcheck < 160.0f)
		{ }
		else if(timeflowcheck < 175.0f)
		{
			if(flag ==true)
			{
				li_1.push_back(*( new Enemy(270, 240, 270, 240) ));
				flag = false;
			}
			if(mftime > 0.5f)
			{
				while(rad <= 360)
				{
					li_b.push_back(*new Ebullet(300,300,cos(rad)*1000,sin(rad)*1000,2) );
					rad += 30;
				}
				rad = 0;
				mftime = 0.0f;
			}
		}
		else
		{
			li_b.push_back(*new Ebullet(250,-100,250,100));
		}
		///////////////////////////////////////

		for(it_1=li_1.begin();it_1!=li_1.end();)
		{
			bool flag=false;
			if(it_1->CheckCollision(player->getRect()))
			{
//				player->sethp(-1);
//				player->setStateDie();
//				it_1 = li_1.erase(it_1);
//				continue;
			}
			if(it_1->update(dt) == 1)
			{
				it_1=li_1.erase(it_1);
				continue;
			}
			for(player->it=player->li.begin();player->it!=player->li.end();)
			{
				if(it_1->CheckCollision(player->it->getRECT()))
				{
					it_1->changeStatusDie();
					player->it=player->li.erase(player->it);
					flag=true;
					sidebar->scoreup();
					break;
				}
				player->it++;
			}
			///////////////////////////////////
			if(timeflowcheck > 140.0f)
			{
				if(it_1->getPoint().x <= 0){
					if(it_1->getPoint().y == 200)
						it_1->changePoint(500, 600);}
				if(it_1->getPoint().x >= 500){
					if(it_1->getPoint().y == 200)
						it_1->changePoint(0, 600);
				}
			}
			else if(timeflowcheck > 120.0f)
			{	}/////////////////////////////////
			else if(timeflowcheck > 100.0f)
			{
				if(it_1->getPoint().y == 100)
					it_1->changePoint(100,200);
				if(it_1->getPoint().y == 200)
					it_1->changePoint(100,650);
			}
			else if(timeflowcheck > 100.0f)
			{
				if(it_1->getPoint().y == 100)
					it_1->changePoint(100,200);
				if(it_1->getPoint().y == 200)
					it_1->changePoint(100,650);
			}
			else if(timeflowcheck > 80.0f)
			{
				if(it_1->getPoint().y == 100)
					it_1->changePoint(400,200);
				if(it_1->getPoint().y == 200)
					it_1->changePoint(400,650);
			}
			else if(timeflowcheck > 60.0f)
			{
				if(it_1->getPoint().y == 100)
					it_1->changePoint(-50,40);
			}
			else if(timeflowcheck > 40.0f)
			{
				if(it_1->getPoint().y == 100)
					it_1->changePoint(650,40);
			}

			if(flag!=true)
				it_1++;
		}

		for(it_item=li_item.begin();it_item!=li_item.end();)
		{
			int res = it_item->update(player->getRect());
			if(res == 0)
			{
				it_item = li_item.erase(it_item);
				continue;
			}
			else if(res == 2)
			{
				it_item = li_item.erase(it_item);
				player->setleftbullet();
				continue;
			}
			it_item++;
		}

		for(it_b=li_b.begin();it_b!=li_b.end();)
		{
			if(it_b->update()==0)
			{
				it_b=li_b.erase(it_b);
				continue;
			}
			it_b++;
		}
		if(Y <= 0)
			Y = 2000;

		if(sidebar->update(player->gethp()) == false)
			return 1;

	}

	return 0;
}
