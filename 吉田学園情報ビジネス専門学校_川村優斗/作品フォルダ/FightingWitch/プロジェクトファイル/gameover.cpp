//=============================================================================
//
// ���U���g��ʂ̏��� [menu.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "gameover.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"bg.h"
#include"sound.h"
#include"ranking.h"
#include"number.h"
#include"padx.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRanking *CGameOver::m_pRanking = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGameOver::CGameOver()
{
	m_fade = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGameOver::~CGameOver()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGameOver::Init(void)
{
	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGGAMEOVER);

	// �����̃��[�h
	CNumber::Load();

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// ���y�̍Đ��A���ʒ���
	pSound->Play(pSound->SOUND_LABEL_BGM_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_RESULT, 0.15f);

	// �����L���O�̐���
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, 200.0f, 0.0f), D3DXVECTOR2(25.0f, 40.0f), true);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGameOver::Uninit(void)
{
	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// ���y�̒�~
	pSound->Stop(pSound->SOUND_LABEL_BGM_RESULT);

	// �����̃A�����[�h
	CNumber::Unload();

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGameOver::Update(void)
{
	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();

	// �^�C�g���ɖ߂�
	if (START_KEY)
	{
		if (m_fade == false)
		{
			pSound->Play(pSound->SOUND_LABEL_OK);
			pFade->SetFade(CManager::MODE_TITLE);
			m_fade = true;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGameOver::Draw(void)
{
}

//=============================================================================
// ���j���[��ʂ̐���
//=============================================================================
CGameOver * CGameOver::Create(void)
{
	// ��ʂ̃C���X�^���X����
	CGameOver *pGameOver = new CGameOver;

	// ��ʂ̏���
	if (pGameOver != NULL)
	{
		pGameOver->Init();
	}
	return pGameOver;
}

//=============================================================================
// �����L���O�̎擾
//=============================================================================
CRanking * CGameOver::GetRanking(void)
{
	return m_pRanking;
}