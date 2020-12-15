#pragma once
#include <windows.h>
#include <time.h>
#include "d3d.h"
#include "InputMgr.h"
#include "game.h"
#include "title.h"
#include "gameover.h"

enum {TITLE,GAME,END};
int gamestate;

game *mGame;
title *mTitle;
gameover *mGameover;

extern CInputMgr* g_InputMgr;

bool D3DUpdate();
void D3Drander();

float g_fSecPerFrame;
float g_fLastTime;
float mfAccumTime;