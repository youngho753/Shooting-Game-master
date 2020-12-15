#pragma once
#include <d3d9.h>
#include <d3dx9.h>
//======임시 추가
#include <fstream>
//======
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
//전역 변수 선언
extern D3DPRESENT_PARAMETERS g_d3dpp;
extern LPDIRECT3D9    g_pD3D ;
extern LPDIRECT3DDEVICE9  g_pd3dDevice;

extern LPD3DXSPRITE   g_pSprite;

extern HWND g_hWnd;
extern HINSTANCE g_Instance;




HRESULT D3DCreate(HWND hWnd, int Width, int Height, bool bWindowed);
void D3DDestroy();
bool D3DLoad();
void D3DUnload();
void D3DReset();
void D3Drander();


