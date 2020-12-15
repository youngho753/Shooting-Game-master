#include "main.h"

//	< ���� ���� >
HWND				g_hWnd				= NULL;		//���� �������� �ڵ�
HINSTANCE			g_Instance			= NULL;		//������ �ν��Ͻ��ڵ�
CInputMgr* g_InputMgr;



LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			delete mGame;
			delete mTitle;
			delete g_InputMgr;
			PostQuitMessage(0);
			return 0;
		case WM_MOUSEMOVE:
		{
			int nX = 0;
			int nY = 0;

			nX = LOWORD(lParam);
			nY = HIWORD(lParam);

			g_InputMgr->SetMousePos(nX, nY);
		}

		break;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	wc.style			= CS_CLASSDC;						// ��Ÿ�� ����
	wc.lpfnWndProc		= MsgProc;							// ������ �޽��� �Լ� ����
	wc.cbClsExtra		= 0;								// �ӽ� ������ Ŭ���� ����
	wc.cbWndExtra		= 0;								// �ӽ� ������ ������ ����
	wc.hInstance		= GetModuleHandle(NULL);			// �ν��Ͻ�(Instance) ����
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);		// ������ ����
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		// ���콺 �Ѽ� ����
	wc.hbrBackground	= NULL;								// ����� �ʿ����� �ʴ�
	wc.lpszMenuName		= NULL;								// �޴��� ������� �ʴ´�
	wc.lpszClassName	= "DirectX";						// Ŭ���� �̸� ����

	RegisterClass(&wc);

	g_Instance=hInstance;

	// ������ ����
	//HWND hWnd 
	g_hWnd	= CreateWindow(	"DirectX",
								"STUDY",	//���¹ٿ� ǥ�õǴ� â �̸� 
								WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, 
								0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
								GetDesktopWindow(),
								NULL,
								wc.hInstance,
								NULL );

	// D3D ����
	if( D3DCreate(g_hWnd, 800, 600, true) != S_OK )		//â ũ�� ����, true/false�� â���/��üȭ����(alt+f4�� ����)
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 0;
	}

	// D3D �ε�
	if( !D3DLoad() )
	{
		D3DDestroy();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 0;
	}
	
	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);

	g_InputMgr= new CInputMgr;
	g_InputMgr->Init();

	gamestate = TITLE;

	mTitle = new title();
	mGame = new game();
	mGameover = new gameover();

	g_fLastTime = timeGetTime() * 0.001f;

	while(1)
	{ 
		MSG msg; 

		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if(	D3DUpdate() == false )
				break;
			D3Drander();
		}
	}

	// D3D ��ε�
	D3DUnload();

	// D3D �ı�
	D3DDestroy();

	UnregisterClass(wc.lpszClassName, wc.hInstance);
	return 0;
}

bool D3DUpdate()
{
	float fCurTime = (float)timeGetTime() * 0.001f;
	g_fSecPerFrame = fCurTime - g_fLastTime;

	g_fLastTime = fCurTime;
	//������Ʈ �ϴ� ��

	switch(gamestate)
	{
	case TITLE:
		if(mTitle->update(g_fSecPerFrame) == 0)
		{
			mGame = new game();
			delete mTitle;
			gamestate = GAME;
		}
		else if(mTitle->update(g_fSecPerFrame) == 1)
		{
			PostQuitMessage(0);
		}
		break;
	case GAME:
		if(mGame->update(g_fSecPerFrame))
		{
			delete mGame;
			gamestate = END;
		}
		break;
	case END:
		if(mGameover->update() == false)
		{
			mTitle = new title();
			gamestate = TITLE;
		}
		break;
	}
	
	g_InputMgr->Update();
	
	return true;
}

void D3Drander()
{
	if( FAILED(g_pd3dDevice->TestCooperativeLevel()) )
		D3DReset();

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(128,128,128), 0.0f, 0);

	g_pd3dDevice->BeginScene();
	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//�������� ���⼭����

	switch(gamestate)
	{
	case TITLE:
		mTitle->rander();
		break;
	case GAME:
		mGame->rander();
		break;
	case END:
		mGameover->rander();
		break;
	}
	//��������

	
	g_pSprite->End();
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}