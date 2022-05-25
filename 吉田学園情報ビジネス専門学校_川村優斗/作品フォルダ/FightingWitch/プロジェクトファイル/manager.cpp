//=============================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"keyboard.h"
#include"padx.h"
#include"manager.h"
#include"sound.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include "texture.h"
#include"result2.h"
#include"gameover.h"
#include"fade.h"
#include"help.h"
#include"menu.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CPadX *CManager::m_pPadX = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CGameOver *CManager::m_pGameOver = NULL;
CResult *CManager::m_pResult = NULL;
CResult2 *CManager::m_pResult2 = NULL;
CMenu *CManager::m_pMenu = NULL;
CHelp *CManager::m_pHelp = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_GAME;
CFade *CManager::m_pFade = NULL;
CTexture *CManager::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, true);
	}

	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// �Q�[���p�b�h�̐���
	m_pPadX = new CPadX;
	if (m_pPadX != NULL)
	{
		m_pPadX->Init(hInstance, hWnd);
	}

	// �T�E���h�̐���
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}

	// �e�N�X�`���N���X����
	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	// �t�F�[�h�̐���
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), MODE_TITLE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pPadX != NULL)
	{
		m_pPadX->Uninit();
		delete m_pPadX;
		m_pPadX = NULL;
	}

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// �S�Ă�j������
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����(���ŏ��ɍs��)
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �Q�[���p�b�h�̍X�V����
	if (m_pPadX != NULL)
	{
		m_pPadX->Update();
	}

	// �����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h��ݒ肷��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// �܂��͊e���[�h��j��
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	case MODE_RESULT2:
		if (m_pResult2 != NULL)
		{
			m_pResult2->Uninit();
			m_pResult2 = NULL;
		}
		break;
	case MODE_HELP:
		if (m_pHelp != NULL)
		{
			m_pHelp->Uninit();
			m_pHelp = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pGameOver->Uninit();
			m_pGameOver = NULL;
		}
		break;
	}

	CScene::ReleaseAll();

	// �e�탂�[�h�̏���
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	case MODE_RESULT2:
		m_pResult2 = CResult2::Create();
		break;
	case MODE_MENU:
		m_pMenu = CMenu::Create();
		break;
	case MODE_HELP:
		m_pHelp = CHelp::Create();
	
		break;
	case MODE_GAMEOVER:
		m_pGameOver = CGameOver::Create();
		break;

	}
	m_mode = mode;
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �����_���[�̎擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h���͂̎擾
//=============================================================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// �Q�[���p�b�h���͂̎擾
//=============================================================================
CPadX * CManager::GetPadX(void)
{
	return m_pPadX;
}

//=============================================================================
// �T�E���h�̎擾
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// �w���v�̎擾
//=============================================================================
CHelp * CManager::GetHelp(void)
{
	return m_pHelp;
}

//=============================================================================
// �^�C�g���̎擾
//=============================================================================
CTitle * CManager::GetTitle(void)
{
	return m_pTitle;
}

//=============================================================================
// ���j���[�̎擾
//=============================================================================
CMenu * CManager::GetMenu(void)
{
	return m_pMenu;
}

//=============================================================================
// �Q�[����ʂ̎擾
//=============================================================================
CGame * CManager::GetGame(void)
{
	return m_pGame;
}

//=============================================================================
// �Q�[���I�[�o�[�̎擾
//=============================================================================
CGameOver * CManager::GetGameOver(void)
{
	return m_pGameOver;
}

//=============================================================================
// ���U���g�̎擾
//=============================================================================
CResult * CManager::GetResult(void)
{
	return m_pResult;
}

//=============================================================================
// ���U���g�̎擾
//=============================================================================
CResult2 * CManager::GetResult2(void)
{
	return m_pResult2;
}
