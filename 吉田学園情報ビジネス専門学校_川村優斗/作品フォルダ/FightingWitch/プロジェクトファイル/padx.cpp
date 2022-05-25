//=============================================================================
//
// ゲームパッドの入力処理 [padx.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "padx.h"
#include <Xinput.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CPadX::CPadX()
{
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	ZeroMemory(&m_StateLast, sizeof(XINPUT_STATE));
	m_bConnect = false;
	ZeroMemory(&m_Vibration, sizeof(XINPUT_VIBRATION));
	m_nVibCount = 0;
	m_bVibration = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPadX::~CPadX()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPadX::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPadX::Uninit(void)
{
	XInputEnable(false);
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPadX::Update(void)
{
	XINPUT_STATE state;

	DWORD WINAPI XInputGetState
	(
		__in  DWORD         dwUserIndex,  // デバイス関連のインデックス
		__out XINPUT_STATE* pState        // 現在の結果を受け取る
	);

	// エラーコード(DWORD)
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		m_bConnect = true;
	}

	else
	{
		m_bConnect = false;
	}

	// 左スティックの入力
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	// 右スティックの入力
	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}

	// 振動
	if (m_nVibCount >= 0)
	{
		m_nVibCount--;
	}

	if (m_nVibCount <= 0 && m_bVibration == true)
	{
		SetVibe(0, 0, 0);
		m_bVibration = false;
	}

	m_StateLast = m_State;

	m_State = state;
}

//=============================================================================
// ボタンの入力情報(プレス情報)を取得
//=============================================================================
bool CPadX::GetButtonPress(int nButton)
{
	return m_State.Gamepad.wButtons & nButton ? true : false;
}

//=============================================================================
// ボタンの入力情報(トリガー情報)を取得
//=============================================================================
bool CPadX::GetButtonTrigger(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}

//=============================================================================
// ボタンの入力情報(リリース情報)を取得
//=============================================================================
bool CPadX::GetButtonRelease(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}

//=============================================================================
// 左スティックの入力情報(プレス情報)を取得
//=============================================================================
bool CPadX::GetLeftStick(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_LEFT:
		return m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// 左スティックの入力情報(トリガー情報)を取得
//=============================================================================
bool CPadX::GetLeftStickTrigger(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// 左スティックの入力情報(リリース情報)を取得
//=============================================================================
bool CPadX::GetLeftStickRelease(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// 右スティックの入力情報(プレス情報)を取得
//=============================================================================
bool CPadX::GetRightStick(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return m_State.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return m_State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return m_State.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;

	case STICK_TYPE_LEFT:
		return m_State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;

	default:
		return false;
		break;
	}

}

//=============================================================================
// 右スティックの入力情報(トリガー情報)を取得
//=============================================================================
bool CPadX::GetRightStickTrigger(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// 右スティックの入力情報(リリース情報)を取得
//=============================================================================
bool CPadX::GetRightStickRelease(int nStick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nStick)
	{
	case STICK_TYPE_UP:
		return (((m_StateLast.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_DOWN:
		return (((m_StateLast.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	case STICK_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;;
		break;

	case STICK_TYPE_LEFT:
		return (((m_StateLast.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) == false) && (m_State.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)) ? true : false;
		break;

	default:
		return false;
		break;
	}
}

//=============================================================================
// 左右トリガーの入力情報(プレス情報)を取得
//=============================================================================
bool CPadX::GetTriggerPress(int nTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGER_TYPE_RIGHT:
		return m_State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case TRIGGER_TYPE_LEFT:
		return m_State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=============================================================================
// 左右トリガーの入力情報(トリガー情報)を取得
//=============================================================================
bool CPadX::GetTriggerTrigger(int nTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGER_TYPE_RIGHT:
		return (((m_StateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case TRIGGER_TYPE_LEFT:
		return (((m_StateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_State.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}

}

//=============================================================================
// 振動(0～65535)
//=============================================================================
void CPadX::SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond)
{
	m_Vibration.wLeftMotorSpeed = nLeftMotorSpeed;
	m_Vibration.wRightMotorSpeed = nRightMotorSpeed;
	XInputSetState(0, &m_Vibration);
	m_nVibCount = nSecond;
	m_bVibration = true;
}