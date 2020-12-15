#include "InputMgr.h"
#include <tchar.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

#define BEFORE_KEYDOWN(key)	(((m_KeyBeforeState[key]) & 0x80) ? true : false)	
#define BEFORE_KEYUP(key)	(((m_KeyBeforeState[key]) & 0x80) ? false : true)	
#define KEYDOWN(key)		(((m_KeyState[key]) & 0x80) ? true : false)			
#define KEYUP(key)			(((m_KeyState[key]) & 0x80) ? false : true)		

CInputMgr::CInputMgr(void):
  m_pDi(NULL)
, m_pDidevKey(NULL)
, m_pDidevMouse(NULL)
, m_hr(S_OK)
, m_IsInClientRect(FALSE)
{
	memset( &m_stMousePos, 0, sizeof(ST_MousePos) );

	memset( m_KeyBeforeState, 0, sizeof(BYTE)*256 );
	memset( m_KeyState, 0, sizeof(BYTE)*256 );

	memset( &m_MouseBeforeState, 0, sizeof(DIMOUSESTATE) );
	memset( &m_MouseState, 0, sizeof(DIMOUSESTATE) );
}

CInputMgr::~CInputMgr(void)
{
	Release();
}

BOOL CInputMgr::Release()
{
	BOOL IsReturn = TRUE;

	if(m_pDi)
	{
		if(m_pDidevKey)
		{
			m_pDidevKey->Unacquire();
			m_pDidevKey->Release();
			m_pDidevKey = NULL;
		}
		if(m_pDidevMouse)
		{
			m_pDidevMouse->Unacquire();
			m_pDidevMouse->Release();
			m_pDidevMouse = NULL;
		}
		m_pDi->Release();
		m_pDi = NULL;
	}

	return IsReturn;
}


BOOL CInputMgr::InitKeyboard()
{
	BOOL IsReturn = TRUE;

	if(FAILED(m_pDi->CreateDevice(GUID_SysKeyboard, &m_pDidevKey, NULL)))
		return FALSE;														//실패하면 false를 리턴..
	if(FAILED(m_pDidevKey->SetDataFormat(&c_dfDIKeyboard)))
		return FALSE;
	if(FAILED(m_pDidevKey->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY)))
		return FALSE;

	while(m_pDidevKey->Acquire() == DIERR_INPUTLOST);
	return IsReturn;
}

BOOL CInputMgr::InitMouse()
{
	BOOL IsReturn = TRUE;

	if(FAILED(m_pDi->CreateDevice(GUID_SysMouse, &m_pDidevMouse, NULL)))
		return false;														//실패하면 false를 리턴..
	if(FAILED(m_pDidevMouse->SetDataFormat(&c_dfDIMouse)))
		return false;
	if(FAILED(m_pDidevMouse->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		return false;
	while(m_pDidevMouse->Acquire() == DIERR_INPUTLOST);

	return IsReturn;
}

BOOL CInputMgr::Init()
{
	BOOL IsReturn = TRUE;

	InitDirectInput(TRUE, TRUE);
	memset( &m_KeyBeforeState, 0, sizeof(BYTE) * 256);		
	memset( &m_MouseBeforeState, 0, sizeof(DIMOUSESTATE));	
	memset( &m_KeyState, 0, sizeof(BYTE) * 256);			
	memset( &m_MouseState, 0, sizeof(DIMOUSESTATE));		

	return IsReturn;
}

BOOL CInputMgr::InitDirectInput(BOOL IsKeyboard, BOOL IsMouse)
{
	HRESULT hr;

	//다이렉트 input객체를 생성
	if(FAILED(hr = DirectInput8Create(g_Instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDi, NULL)))
	{
		return FALSE;
	}
	if(IsKeyboard)InitKeyboard();
	if(IsMouse)InitMouse();
	
	return TRUE;		
}

BOOL CInputMgr::PreProcess()
{	
	memcpy( &m_KeyBeforeState, &m_KeyState, sizeof(BYTE) * 256);
	memcpy( &m_MouseBeforeState, &m_MouseState, sizeof(DIMOUSESTATE));
	return TRUE;
}

BOOL CInputMgr::KeyProcess(BYTE *bpKey)
{
	//해당 배열을 0으로 초기화..
	ZeroMemory(bpKey, 256);

    if( !m_pDidevKey )
		return FALSE;

	//key배열에 256크기로 값을 받아오기..(키보드의 입력상태..)
	m_hr = m_pDidevKey->GetDeviceState(256, bpKey);
	if(FAILED(m_hr))							
	{
		m_hr = m_pDidevKey->Acquire();			
		while(m_hr == DIERR_INPUTLOST)			
			m_pDidevKey->Acquire();

		return FALSE;							
	}

	return TRUE;		
}

BOOL CInputMgr::MouseProcess(DIMOUSESTATE *pstMouseState)
{
	//해당 배열을 0으로 초기화..
	ZeroMemory(pstMouseState, sizeof(DIMOUSESTATE));

   if( !m_pDidevMouse )
	   return FALSE;

	m_hr = m_pDidevMouse->GetDeviceState(sizeof(DIMOUSESTATE), pstMouseState);
	if(FAILED(m_hr))
	{
		m_hr = m_pDidevMouse->Acquire();	

		while(m_hr == DIERR_INPUTLOST)		
			m_pDidevMouse->Acquire();

		return FALSE;						
	}

	return TRUE;		
}

BOOL CInputMgr::Update()
{
	PreProcess();

	if(!KeyProcess(m_KeyState))
		return FALSE;				
	if(!MouseProcess(&m_MouseState))
		return FALSE;			

	POINT ptAbsMousePos;
	GetCursorPos(&ptAbsMousePos);

	RECT rtWinRect;
	GetWindowRect(g_hWnd, &rtWinRect);

	ShowCursor(TRUE);
	return TRUE;
}




BOOL CInputMgr::IsKeyPush(DWORD dwKeyCode)
{
	BOOL IsReturn = FALSE;

	if( BEFORE_KEYUP(dwKeyCode) )
	{
		if( KEYDOWN(dwKeyCode) )
			IsReturn = TRUE;
	}
	return IsReturn;
}

BOOL CInputMgr::IsKeyPushed(DWORD dwKeyCode)
{
	BOOL IsReturn = FALSE;

 	if( BEFORE_KEYDOWN(dwKeyCode) )
	{
		if( !KEYDOWN(dwKeyCode) )
			IsReturn = TRUE;
	}
	return IsReturn;
}

BOOL CInputMgr::IsKeyPushing(DWORD dwKeyCode)
{
	BOOL IsReturn = FALSE;

	if( BEFORE_KEYDOWN(dwKeyCode) )
	{
		if( KEYDOWN(dwKeyCode) )
			IsReturn = TRUE;
	}
	return IsReturn;
}

BOOL CInputMgr::IsLButtonClick()
{
	BOOL IsReturn = FALSE;

	if( !m_MouseBeforeState.rgbButtons[0] )
	{
		if( m_MouseState.rgbButtons[0] )
			IsReturn = TRUE;
	}
	return IsReturn;
}


BOOL CInputMgr::IsLButtonClicked()
{
	BOOL IsReturn = FALSE;

	if( m_MouseBeforeState.rgbButtons[0] )
	{
		if( !m_MouseState.rgbButtons[0] )
			IsReturn = TRUE;
	}	
	return IsReturn;
}

BOOL CInputMgr::IsLButtonClicking()
{
	BOOL IsReturn = FALSE;

	if( m_MouseBeforeState.rgbButtons[0] )
	{
		if( m_MouseState.rgbButtons[0] )
			IsReturn = TRUE;
	}
	return IsReturn;
}

BOOL CInputMgr::IsRButtonClick()
{
	BOOL IsReturn = FALSE;

	if( !m_MouseBeforeState.rgbButtons[1] )
	{
		if( m_MouseState.rgbButtons[1] )
			IsReturn = TRUE;
	}

	return IsReturn;
}

BOOL CInputMgr::IsRButtonClicked()
{
	BOOL IsReturn = FALSE;

	if( m_MouseBeforeState.rgbButtons[1] )
	{
		if( m_MouseState.rgbButtons[1] )
			IsReturn = TRUE;
	}

	return IsReturn;
}

BOOL CInputMgr::IsRButtonClicking()
{
	BOOL IsReturn = FALSE;

	if( m_MouseBeforeState.rgbButtons[1] )
	{
		if( m_MouseState.rgbButtons[1] )
			IsReturn = TRUE;
	}

	return IsReturn;
}

ST_MousePos* CInputMgr::GetMousePos()
{
	return &m_stMousePos;
}

void CInputMgr::SetMousePos(LONG lX, LONG lY)
{
	m_stMousePos.lX = lX;
	m_stMousePos.lY = lY;
}