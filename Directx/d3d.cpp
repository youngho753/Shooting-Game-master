#include "d3d.h"

D3DPRESENT_PARAMETERS g_d3dpp;
LPDIRECT3D9    g_pD3D    =  NULL;
LPDIRECT3DDEVICE9  g_pd3dDevice  =  NULL;
LPD3DXSPRITE   g_pSprite   =  NULL;

HRESULT D3DCreate(HWND hWnd, int Width, int Height, bool bWindowed)
{
 HRESULT hRet;
 g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
 if(g_pD3D == NULL)
  return E_FAIL;

 ZeroMemory(&g_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
 g_d3dpp.Windowed = bWindowed;  
 g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
 g_d3dpp.BackBufferFormat    = D3DFMT_X8R8G8B8; 
 g_d3dpp.BackBufferWidth        = Width;  
 g_d3dpp.BackBufferHeight       = Height;  
 g_d3dpp.BackBufferCount        = 1;  

 hRet= g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice);
 if(FAILED(hRet))
  return hRet;
 if(bWindowed)
 {
  DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
  RECT rc      = { 0, 0, Width, Height };
  AdjustWindowRect(&rc, dwStyle, FALSE);
  SetWindowPos(hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);
 }
 return S_OK;
}
void D3DDestroy()
{
 if(g_pd3dDevice) 
  g_pd3dDevice->Release();

 if(g_pD3D)
  g_pD3D->Release();
}
bool D3DLoad()
{
 if( FAILED(D3DXCreateSprite(g_pd3dDevice, &g_pSprite)) )
  return false;
 //if( FAILED(D3DXCreateTextureFromFile(g_pd3dDevice,"back.png",&g_pTexture)))
  //return false;

 return true;
}

void D3DUnload()
{
 if(g_pSprite)
  g_pSprite->Release();
}

void D3DReset()
{
 g_pSprite->OnLostDevice();
 g_pd3dDevice->Reset(&g_d3dpp);
 g_pSprite->OnResetDevice();
}