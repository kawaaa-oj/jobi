//=============================================================================
//
// �Q�[���p�b�h�̓��͏��� [padx.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "padx.h"
#include <Xinput.h>

//=============================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//=============================================================================
CPadX::~CPadX()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPadX::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPadX::Uninit(void)
{
	XInputEnable(false);
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPadX::Update(void)
{
	XINPUT_STATE state;

	DWORD WINAPI XInputGetState
	(
		__in  DWORD         dwUserIndex,  // �f�o�C�X�֘A�̃C���f�b�N�X
		__out XINPUT_STATE* pState        // ���݂̌��ʂ��󂯎��
	);

	// �G���[�R�[�h(DWORD)
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		m_bConnect = true;
	}

	else
	{
		m_bConnect = false;
	}

	// ���X�e�B�b�N�̓���
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	// �E�X�e�B�b�N�̓���
	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}

	// �U��
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
// �{�^���̓��͏��(�v���X���)���擾
//=============================================================================
bool CPadX::GetButtonPress(int nButton)
{
	return m_State.Gamepad.wButtons & nButton ? true : false;
}

//=============================================================================
// �{�^���̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CPadX::GetButtonTrigger(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}

//=============================================================================
// �{�^���̓��͏��(�����[�X���)���擾
//=============================================================================
bool CPadX::GetButtonRelease(int nButton)
{
	return (((m_StateLast.Gamepad.wButtons & nButton) == false) && (m_State.Gamepad.wButtons & nButton)) ? true : false;
}

//=============================================================================
// ���X�e�B�b�N�̓��͏��(�v���X���)���擾
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
// ���X�e�B�b�N�̓��͏��(�g���K�[���)���擾
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
// ���X�e�B�b�N�̓��͏��(�����[�X���)���擾
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
// �E�X�e�B�b�N�̓��͏��(�v���X���)���擾
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
// �E�X�e�B�b�N�̓��͏��(�g���K�[���)���擾
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
// �E�X�e�B�b�N�̓��͏��(�����[�X���)���擾
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
// ���E�g���K�[�̓��͏��(�v���X���)���擾
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
// ���E�g���K�[�̓��͏��(�g���K�[���)���擾
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
// �U��(0�`65535)
//=============================================================================
void CPadX::SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond)
{
	m_Vibration.wLeftMotorSpeed = nLeftMotorSpeed;
	m_Vibration.wRightMotorSpeed = nRightMotorSpeed;
	XInputSetState(0, &m_Vibration);
	m_nVibCount = nSecond;
	m_bVibration = true;
}