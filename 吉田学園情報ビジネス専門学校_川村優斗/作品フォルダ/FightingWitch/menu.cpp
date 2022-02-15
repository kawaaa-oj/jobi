//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "menu.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"ui.h"
#include"bg.h"
#include"sound.h"
#include"padx.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CUI *CMenu::m_pUI[6] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMenu::CMenu()
{
	m_fade = false;
	// ������ԁiStart��I��ł����ԁj
	m_nCntSelect = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMenu::~CMenu()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMenu::Init(void)
{
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGMENU);

	// UI�o��
	m_pUI[0] = CUI::Create(D3DXVECTOR3(UITEXT_X, 150.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_GAMESTART);
	m_pUI[1] = CUI::Create(D3DXVECTOR3(UITEXT_X, 270.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_HELP);
	m_pUI[2] = CUI::Create(D3DXVECTOR3(UITEXT_X, 390.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_RANKING);
	m_pUI[3] = CUI::Create(D3DXVECTOR3(UITEXT_X, 510.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_TITLE);
	m_pUI[4] = CUI::Create(D3DXVECTOR3(UITEXT_X, UIINFO_Y, 0.0f), D3DXVECTOR2(UIINFO_WIDTH, UIINFO_HEIGHT), CTexture::TEXTURETYPE_MENUTEXT);
	m_pUI[5] = CUI::Create(D3DXVECTOR3(250.0f, 150.0f, 0.0f), D3DXVECTOR2(55.0f, 50.0f), CTexture::TEXTURETYPE_PLAYER);

	m_pUI[4]->SetVtxTex(0, 0.25f, 0.25f, 1.0f);

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Play(pSound->SOUND_LABEL_BGM_MENU);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_MENU, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMenu::Uninit(void)
{
	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_BGM_MENU);

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMenu::Update(void)
{
	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	//�T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();
	m_pUI[5]->SetVtxTex(0, 0.25f, 0.25f, 1.0f);

	// UI�̐F�X�����iStart�̂Ƃ��ɂ�����o���ATutorial�̂Ƃ��ɂ�����o���c�j
	switch (m_nCntSelect)
	{
	case SELECT_PLAY:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(0, 0.25f, 0.25f, 1.0f);
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 150.0f, 0.0f));
		break;
	case SELECT_TUTORIAL:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(1, 0.25f, 0.25f, 1.0f);
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 270.0f, 0.0f));
		break;
	case SELECT_RANKING:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(2, 0.25f, 0.25f, 1.0f);
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 390.0f, 0.0f));
		break;
	case SELECT_QUIT:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[4]->SetVtxTex(3, 0.25f, 0.25f, 1.0f);
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 510.0f, 0.0f));
		break;
	default:
		break;
	}

	// ���j���[�ړ��i���j
	if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWN) == true || pInputKeyboard->GetKeyboardTrigger(DIK_S) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_DOWN) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_SELECT);
		pSound->SetVolume(pSound->SOUND_LABEL_SELECT, 0.5f);

		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_RANKING;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_PLAY;
			break;
		}
	}

	// ���j���[�ړ��i���j
	if (pInputKeyboard->GetKeyboardTrigger(DIK_UP) == true || pInputKeyboard->GetKeyboardTrigger(DIK_W) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_UP) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		pSound->Play(pSound->SOUND_LABEL_SELECT);
		pSound->SetVolume(pSound->SOUND_LABEL_SELECT, 0.5f);
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_PLAY;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_RANKING;
			break;
		}
	}

	// ����
	if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) == true || pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
	{
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_GAME);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_TUTORIAL:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_HELP);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_RANKING:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RESULT2);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_QUIT:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TITLE);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMenu::Draw(void)
{
}

//=============================================================================
// ���j���[��ʂ̐���
//=============================================================================
CMenu * CMenu::Create(void)
{
	// ��ʂ̃C���X�^���X����
	CMenu *pMenu = new CMenu;

	// ��ʂ̏���
	if (pMenu != NULL)
	{
		pMenu->Init();
	}
	return pMenu;
}