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
#include"polygon.h"
#include "texture.h"
#include"bg.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CPadX *CManager::m_pPadX = NULL;
CPolygon *CManager::m_pPolygon = NULL;
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
	m_pKeyboard = new CKeyboard;
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Init(hInstance, hWnd);
	}

	// �Q�[���p�b�h�̐���
	m_pPadX = new CPadX;
	if (m_pPadX != NULL)
	{
		m_pPadX->Init(hInstance, hWnd);
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

	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CTexture::TEXTURETYPE_BG);

	// �|���S���̐���
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(40.0f, 40.0f));

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
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
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
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
// �����_���[�̎擾
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h���͂̎擾
//=============================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
// �Q�[���p�b�h���͂̎擾
//=============================================================================
CPadX * CManager::GetPadX(void)
{
	return m_pPadX;
}

//=============================================================================
// �|���S���̎擾
//=============================================================================
CPolygon * CManager::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// �e�N�X�`���̎擾
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}