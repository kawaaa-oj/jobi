//=============================================================================
//
// UI�̏��� [ui.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "ui.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"player.h"
#include"time.h"
#include"game.h"
#include"sound.h"
#include"padx.h"
#include"life.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = CTexture::TEXTURETYPE_NAME;
	m_state = CPlayer::STATE_NORMAL;

	m_fPosU = 0.0f;
	m_fPosV = 0.0f;
	m_nLife = 0;

	m_bBrinkFlag = false;
	m_bBrinkFlag2 = false;
	m_fade = false;
	m_bDisplay = false;
	m_bDisplay2 = false;

	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}

CUI::~CUI()
{
}

HRESULT CUI::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

void CUI::Update(void)
{
	//UI�̑傫����ݒ�
	D3DXVECTOR3 pPos = Getposition();

	// UI�̃T�C�Y��ݒ�
	D3DXVECTOR3 pSize = GetSize();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//�t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();

	// ���[�h�̎擾
	m_mode = CManager::GetMode();

	// �Q�[�����[�h�ȊO�Ŗ\�����Ȃ��悤��
	if (m_mode == CManager::MODE_GAME)
	{
		// ���Ԑ؂�̂Ƃ��̓X�R�A�����Ȃ��悤��
		m_pTime = CGame::GetTime();
		m_pPlayer = CGame::GetPlayer();
		m_state = m_pPlayer->GetState();
		int nTime = m_pTime->GetTime();
	}

	CScene2D::Update();

	// �^�C�v���Ƃɓ������w��
	switch (m_type)
	{
		// �^�C�g�����S
	case CTexture::TEXTURETYPE_NAME:
		if (m_bBrinkFlag2 == false)
		{
			m_col.a = 0.0f;
		}
		m_col.a += 0.01f;
		if (START_KEY)
		{
			if (m_bDisplay2 == false)
			{
				pPos.y = STOP_PUSH;
				m_col.a = 0.9f;
				m_bDisplay2 = true;
			}
		}
		m_bBrinkFlag2 = true;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_bDisplay = true;
		}

		//�F�ݒ�
		SetColor(m_col);

		//���X�ɍ~��Ă�
		pPos.y += MOVE_PUSH;
		if (pPos.y >= STOP_PUSH)
		{
			//�^�񒆂Ŏ~�܂�
			pPos.y -= MOVE_PUSH;
			if (START_KEY)
			{
				if (m_fade == false)
				{
					if (m_bDisplay == true)
					{
						//�Q�[���s��
						pSound->Play(pSound->SOUND_LABEL_OK);
						pFade->SetFade(CManager::MODE_MENU);
						m_fade = true;
					}
				}
			}
		}
		break;
	// PUSH SPACE
	case CTexture::TEXTURETYPE_PUSH:
		//�_�ł�����
		if (m_bBrinkFlag == false)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_bBrinkFlag = true;
			}
		}
		else
		{
			m_col.a += 0.01f;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_bBrinkFlag = false;
			}
		}

		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_PLAYER:
		if (m_mode == CManager::MODE_TITLE)
		{
			CScene2D::SetVtxTex(0, 0.25f, 0.25f, 1.0f);

			//����E���E�������Ƃ�
			pPos.x += MOVE_PICT;

			//�[�܂ōs�����烏�[�v
			if (pPos.x >= 1400.0f)
			{
				pPos.x = -70.0f;
			}
		}
		break;
	
	// ��ԕ\���̏���
	case CTexture::TEXTURETYPE_NORMAL:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_NORMAL)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_DAMAGE:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_DAMAGE)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_SUPER:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_RENSYA)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_MUTEKI:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_MUTEKI)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_SINISOU:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_SINISOU)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_NUMBER:

		break;
	default:
		break;
	}
	//�v���C���[�̈ʒu�ݒ�
	SetPosition(pPos);

}

//=============================================================================
// �`�揈��
//============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CUI * CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// UI�̃C���X�^���X����
	CUI *pUI = new CUI;

	// UI�̏���
	if (pUI != NULL)
	{
		pUI->m_type = type;
		pUI->Init();
		pUI->SetPosition(pos);
		pUI->SetSize(size);
		pUI->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}
	return pUI;
}