//=============================================================================
//
// �L�[�{�[�h�̓��͏��� [keyboard.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"keyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard()
{
	// �L�[���̃N���A
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));
	
	// �g���K�[
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKeyboard::Update(void)
{
	// ���͏��ۑ��p
	BYTE aKeyState[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^�擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̓��͏��ۑ�
			m_aKeyStateTrigger[nCntKey] = (m_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStatePress[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// �v���X���
//=============================================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
	// �����@? �^�̏ꍇ : �U�̏ꍇ;
}

//=============================================================================
// �g���K�[���
//=============================================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	// �����@? �^�̏ꍇ : �U�̏ꍇ;
}

//=============================================================================
// �����[�X���
//=============================================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
	// �����@? �^�̏ꍇ : �U�̏ꍇ;
}