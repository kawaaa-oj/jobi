#ifndef _PADX_H_
#define _PADX_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_BUTTON_MAX (256)

//*****************************************************************************
// ゲームパッドのクラス
//*****************************************************************************
class CPadX : public CInput
{
public:
	typedef enum
	{
		STICK_TYPE_NONE = 0,
		STICK_TYPE_UP,
		STICK_TYPE_DOWN,
		STICK_TYPE_RIGHT,
		STICK_TYPE_LEFT,
		STICK_TYPE_MAX
	} STICK_TYPE;
	// スティックのタイプ

	typedef enum
	{
		TRIGGER_TYPE_NONE = 0,
		TRIGGER_TYPE_RIGHT,
		TRIGGER_TYPE_LEFT,
		TRIGGER_TYPE_MAX
	} TRIGGER_TYPE;
	// トリガーのタイプ

	CPadX();	//デフォルトコンストラクタ
	~CPadX();	//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// ボタン関係
	bool GetButtonPress(int nButton);  
	bool GetButtonTrigger(int nButton);
	bool GetButtonRelease(int nButton);

	// 左スティック関係
	bool GetLeftStick(int nStick);
	bool GetLeftStickTrigger(int nStick);
	bool GetLeftStickRelease(int nStick);

	// 右スティック関係
	bool GetRightStick(int nStick);
	bool GetRightStickTrigger(int nStick);
	bool GetRightStickRelease(int nStick);

	// トリガー関係
	bool GetTriggerPress(int nTrigger);
	bool GetTriggerTrigger(int nTrigger);

	// 振動関係
	void SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond);

private:
	XINPUT_STATE m_State;			// Xinputの状態
	XINPUT_STATE m_StateLast;		// 前の状態
	bool m_bConnect;				// 接続判定
	XINPUT_VIBRATION m_Vibration;	// 振動の情報
	bool m_bVibration;				// 振動判定
	int m_nVibCount;				// 振動時間
};

#endif // !_PADX_H_
