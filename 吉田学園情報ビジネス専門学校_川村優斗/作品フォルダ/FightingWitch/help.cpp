//=============================================================================
//
// �w���v��ʂ̏��� [help.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"sound.h"
#include "help.h"
#include"padx.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CHelp::CHelp(int nPriority) : CScene2D(nPriority)
{
	m_uiNum = 0;
	m_fade = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CHelp::~CHelp()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CHelp::Init(void)
{
	m_pBg[0] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP1, CTexture::TEXTURETYPE_BGHELP1);
	m_pBg[1] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP2, CTexture::TEXTURETYPE_BGHELP2);
	m_pBg[2] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP3, CTexture::TEXTURETYPE_BGHELP3);
	m_pBg[3] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELPPAD, CTexture::TEXTURETYPE_BGHELPPAD);
	
	CScene2D::Init();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	//���y�̍Đ�
	pSound->Play(pSound->SOUND_LABEL_BGM_HELP);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_HELP, 0.3f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CHelp::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	//���y�̍Đ�
	pSound->Stop(pSound->SOUND_LABEL_BGM_HELP);

	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CHelp::Update(void)
{
	// �ړ�
	D3DXVECTOR3 pPos = Getposition();
	D3DXVECTOR2 pSize = GetSize();

	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();

	// �y�[�W�ړ�
	if ((pInputKeyboard->GetKeyboardTrigger(DIK_D) == true) || (pInputKeyboard->GetKeyboardTrigger(DIK_RIGHT) == true) || (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) == true))
	{
		if (m_uiNum == 0)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 1;
		}
		else if (m_uiNum == 1)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 2;
		}
		else if (m_uiNum == 2)
		{
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
	}
	if ((pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
	{
		if (m_uiNum == 0)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 3;
		}
		else if (m_uiNum == 3)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 2;
		}
		else if (m_uiNum == 2)
		{
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
	}
	if ((pInputKeyboard->GetKeyboardTrigger(DIK_A) == true) || (pInputKeyboard->GetKeyboardTrigger(DIK_LEFT) == true))
	{
		if (m_uiNum == 0)
		{
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
		else if (m_uiNum == 1)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 0;
		}
		else if (m_uiNum == 2)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 1;
		}
	}

	if ((pPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
	{
		if (m_uiNum == 0)
		{
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
		else if (m_uiNum == 3)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 0;
		}
		else if (m_uiNum == 2)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 3;
		}
	}


	// �v���C���[�̈ʒu�ݒ�
	SetPosition(pPos);

	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CHelp::Draw(void)
{
	CScene2D::Draw();
}

int CHelp::GetUInum(void)
{
	return m_uiNum;
}

//=============================================================================
// �w���v��ʂ̐���
//=============================================================================
CHelp * CHelp::Create(void)
{
	// ��ʂ̃C���X�^���X����
	CHelp *pMenuUI = new CHelp;

	// ��ʂ̏���
	if (pMenuUI != NULL)
	{
		pMenuUI->Init();
	}
	return pMenuUI;
}