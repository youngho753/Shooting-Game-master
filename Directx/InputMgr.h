#pragma once

#include "d3d.h"
#include <dinput.h>

typedef struct tagST_MousePos
{
	LONG lX;		/**< X좌표	*/
	LONG lY;		/**< Y좌표	*/

}ST_MousePos;

class CInputMgr
{
private:
	ST_MousePos				m_stMousePos;			/**< 마우스의 x좌표값을 담아놓을 부분	*/

	LPDIRECTINPUT8			m_pDi;					/**< 다이렉트 input객체를 가리키는 포인터.	*/
	LPDIRECTINPUTDEVICE8	m_pDidevKey;			/**< 다이렉트 input객체로 부터 생성한 input디바이스의 포인터..(키보드)	*/
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;			/**< 다이렉트 input객체로 부터 생성한 input디바이스의 포인터..(마우스)	*/

	BYTE					m_KeyBeforeState[256];	/**< 각 키들의 이전 상태를 저장할 배열..	*/
	BYTE					m_KeyState[256];		/**< 각 키들의 현재 상태를 저장할 배열..	*/	

	DIMOUSESTATE			m_MouseBeforeState;		/**< 마우스의 이전 상태를 저장할 구조체..	*/
	DIMOUSESTATE			m_MouseState;			/**< 마우스의 현재 상태를 저장할 구조체..	*/
	
	HRESULT					m_hr;					/**< 다이렉트 input객체의 멤버함수 호출후 상태를 받아놓을 멤버변수.	*/
	BOOL					m_IsInClientRect;		/**< 마우스가 클라이언트 영역안에 있는지를 나타내는 플래그	*/

private:
	BOOL KeyProcess(BYTE *bpKey);
	BOOL MouseProcess(DIMOUSESTATE *pstMouseState);	
	BOOL PreProcess();
public:
	//초기화
	BOOL InitKeyboard();
	BOOL InitMouse();
	BOOL Init();
	BOOL InitDirectInput(BOOL IsKeyboard, BOOL IsMouse);

	BOOL Update();
	BOOL rander();
	BOOL Release();

	BOOL IsKeyPush(DWORD dwKeyCode);
	BOOL IsKeyPushed(DWORD dwKeyCode);
	BOOL IsKeyPushing(DWORD dwKeyCode);

	BOOL IsLButtonClick();
	BOOL IsLButtonClicked();
	BOOL IsLButtonClicking();

	BOOL IsRButtonClick();
	BOOL IsRButtonClicked();
	BOOL IsRButtonClicking();

	ST_MousePos* GetMousePos();
	void SetMousePos(LONG lX, LONG lY);

	CInputMgr(void);
	virtual ~CInputMgr(void);
};
