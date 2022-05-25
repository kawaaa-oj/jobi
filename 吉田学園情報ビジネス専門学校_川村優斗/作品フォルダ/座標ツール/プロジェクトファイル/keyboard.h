//=============================================================================
//
// キーボード処理のクラス [keyboard.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"input.h"

//*****************************************************************************
// キーボード処理のクラスの定義
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);			// プレス情報
	bool GetKeyboardTrigger(int nKey);	// トリガー情報
	bool GetKeyboardRelease(int nKey);	// リリース情報

private:
	BYTE m_aKeyStatePress[NUM_KEY_MAX];		// キーボードの入力情報(プレス情報)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードの入力情報(トリガー情報)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// キーボードの入力情報(リリース情報)
};

#endif // !_KEYBOARD_H_
