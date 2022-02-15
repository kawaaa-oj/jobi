#ifndef _PADX_H_
#define _PADX_H_

#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_BUTTON_MAX (256)

//*****************************************************************************
// �Q�[���p�b�h�̃N���X
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
	// �X�e�B�b�N�̃^�C�v

	typedef enum
	{
		TRIGGER_TYPE_NONE = 0,
		TRIGGER_TYPE_RIGHT,
		TRIGGER_TYPE_LEFT,
		TRIGGER_TYPE_MAX
	} TRIGGER_TYPE;
	// �g���K�[�̃^�C�v

	CPadX();	//�f�t�H���g�R���X�g���N�^
	~CPadX();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �{�^���֌W
	bool GetButtonPress(int nButton);  
	bool GetButtonTrigger(int nButton);
	bool GetButtonRelease(int nButton);

	// ���X�e�B�b�N�֌W
	bool GetLeftStick(int nStick);
	bool GetLeftStickTrigger(int nStick);
	bool GetLeftStickRelease(int nStick);

	// �E�X�e�B�b�N�֌W
	bool GetRightStick(int nStick);
	bool GetRightStickTrigger(int nStick);
	bool GetRightStickRelease(int nStick);

	// �g���K�[�֌W
	bool GetTriggerPress(int nTrigger);
	bool GetTriggerTrigger(int nTrigger);

	// �U���֌W
	void SetVibe(int nLeftMotorSpeed, int nRightMotorSpeed, int nSecond);

private:
	XINPUT_STATE m_State;			// Xinput�̏��
	XINPUT_STATE m_StateLast;		// �O�̏��
	bool m_bConnect;				// �ڑ�����
	XINPUT_VIBRATION m_Vibration;	// �U���̏��
	bool m_bVibration;				// �U������
	int m_nVibCount;				// �U������
};

#endif // !_PADX_H_
