//=============================================================================
//
// �L�[�{�[�h�����̃N���X [keyboard.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"input.h"

//*****************************************************************************
// �L�[�{�[�h�����̃N���X�̒�`
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);			// �v���X���
	bool GetKeyboardTrigger(int nKey);	// �g���K�[���
	bool GetKeyboardRelease(int nKey);	// �����[�X���

private:
	BYTE m_aKeyStatePress[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��(�v���X���)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��(�g���K�[���)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̓��͏��(�����[�X���)
};

#endif // !_KEYBOARD_H_
