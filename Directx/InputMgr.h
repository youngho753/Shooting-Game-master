#pragma once

#include "d3d.h"
#include <dinput.h>

typedef struct tagST_MousePos
{
	LONG lX;		/**< X��ǥ	*/
	LONG lY;		/**< Y��ǥ	*/

}ST_MousePos;

class CInputMgr
{
private:
	ST_MousePos				m_stMousePos;			/**< ���콺�� x��ǥ���� ��Ƴ��� �κ�	*/

	LPDIRECTINPUT8			m_pDi;					/**< ���̷�Ʈ input��ü�� ����Ű�� ������.	*/
	LPDIRECTINPUTDEVICE8	m_pDidevKey;			/**< ���̷�Ʈ input��ü�� ���� ������ input����̽��� ������..(Ű����)	*/
	LPDIRECTINPUTDEVICE8	m_pDidevMouse;			/**< ���̷�Ʈ input��ü�� ���� ������ input����̽��� ������..(���콺)	*/

	BYTE					m_KeyBeforeState[256];	/**< �� Ű���� ���� ���¸� ������ �迭..	*/
	BYTE					m_KeyState[256];		/**< �� Ű���� ���� ���¸� ������ �迭..	*/	

	DIMOUSESTATE			m_MouseBeforeState;		/**< ���콺�� ���� ���¸� ������ ����ü..	*/
	DIMOUSESTATE			m_MouseState;			/**< ���콺�� ���� ���¸� ������ ����ü..	*/
	
	HRESULT					m_hr;					/**< ���̷�Ʈ input��ü�� ����Լ� ȣ���� ���¸� �޾Ƴ��� �������.	*/
	BOOL					m_IsInClientRect;		/**< ���콺�� Ŭ���̾�Ʈ �����ȿ� �ִ����� ��Ÿ���� �÷���	*/

private:
	BOOL KeyProcess(BYTE *bpKey);
	BOOL MouseProcess(DIMOUSESTATE *pstMouseState);	
	BOOL PreProcess();
public:
	//�ʱ�ȭ
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
