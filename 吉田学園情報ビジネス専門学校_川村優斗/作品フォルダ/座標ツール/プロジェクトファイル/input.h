//=============================================================================
//
// 入力処理のクラス [input.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _INPUT_H_
#define _INPUT_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"main.h"
#include <dinput.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_KEY_MAX (256)// キーの最大数
#define START_KEY (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) == true || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || (pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A)) == true|| (pPadX->GetButtonTrigger(XINPUT_GAMEPAD_START)) == true)
// 決定キー

//*****************************************************************************
// 入力処理のクラスの定義
//*****************************************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	LPDIRECTINPUTDEVICE8  m_pDevice;	// デバイスオブジェクト
	static LPDIRECTINPUT8 m_pInput;		// DirectInputオブジェクト

};

#endif // !_INPUT_H_
