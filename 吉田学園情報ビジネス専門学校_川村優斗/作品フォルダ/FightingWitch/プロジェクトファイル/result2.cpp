//=============================================================================
//
// ���U���g��ʂ̏��� [menu.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "result2.h"
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
CRanking *CResult2::m_pRanking = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult2::CResult2()
{
	m_fade = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult2::~CResult2()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult2::Init(void)
{
	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGRESULT2);

	// �����̃��[�h
	CNumber::Load();

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// ���y�̍Đ��A���ʒ���
	pSound->Play(pSound->SOUND_LABEL_BGM_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_RESULT, 0.35f);

	// �����L���O�̐���
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, 200.0f, 0.0f), D3DXVECTOR2(25.0f, 40.0f), false);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult2::Uninit(void)
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
void CResult2::Update(void)
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
			pFade->SetFade(CManager::MODE_MENU);
			m_fade = true;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult2::Draw(void)
{
}

//=============================================================================
// ���j���[��ʂ̐���
//=============================================================================
CResult2 * CResult2::Create(void)
{
	// ��ʂ̃C���X�^���X����
	CResult2 *pResult2 = new CResult2;

	// ��ʂ̏���
	if (pResult2 != NULL)
	{
		pResult2->Init();
	}
	return pResult2;
}

//=============================================================================
// �����L���O�̎擾
//=============================================================================
CRanking * CResult2::GetRanking(void)
{
	return m_pRanking;
}