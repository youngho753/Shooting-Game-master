#include "main.h"

//	< 전역 변수 >
HWND				g_hWnd				= NULL;		//현재 윈도우의 핸들
HINSTANCE			g_Instance			= NULL;		//윈도우 인스턴스핸들
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
	wc.style			= CS_CLASSDC;						// 스타일 설정
	wc.lpfnWndProc		= MsgProc;							// 윈도우 메시지 함수 설정
	wc.cbClsExtra		= 0;								// 임시 윈도우 클래스 설정
	wc.cbWndExtra		= 0;								// 임시 윈도우 데이터 설정
	wc.hInstance		= GetModuleHandle(NULL);			// 인스턴스(Instance) 설정
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);		// 아이콘 적재
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		// 마우스 켜서 적재
	wc.hbrBackground	= NULL;								// 배경은 필요하지 않다
	wc.lpszMenuName		= NULL;								// 메뉴는 사용하지 않는다
	wc.lpszClassName	= "DirectX";						// 클래스 이름 설정

	RegisterClass(&wc);

	g_Instance=hInstance;

	// 윈도우 생성
	//HWND hWnd 
	g_hWnd	= CreateWindow(	"DirectX",
								"STUDY",	//상태바에 표시되는 창 이름 
								WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, 
								0, 0, CW_USEDEFAULT, CW_USEDEFAULT,
								GetDesktopWindow(),
								NULL,
								wc.hInstance,
								NULL );

	// D3D 생성
	if( D3DCreate(g_hWnd, 800, 600, true) != S_OK )		//창 크기 변경, true/false로 창모드/전체화면모드(alt+f4로 종료)
	{
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 0;
	}

	// D3D 로드
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

	// D3D 언로드
	D3DUnload();

	// D3D 파괴
	D3DDestroy();

	UnregisterClass(wc.lpszClassName, wc.hInstance);
	return 0;
}

bool D3DUpdate()
{
	float fCurTime = (float)timeGetTime() * 0.001f;
	g_fSecPerFrame = fCurTime - g_fLastTime;

	g_fLastTime = fCurTime;
	//업데이트 하는 곳

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

	//랜더링은 여기서부터

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
	//랜더링끝

	
	g_pSprite->End();
	g_pd3dDevice->EndScene();
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}