//=============================================================================
//
// �|���S���̕\������ [polygon.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "polygon.h"
#include"manager.h"
#include"keyboard.h"
#include"texture.h"
#include"padx.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon(int nPriority) : CScene2D(nPriority)
{
	m_bTextureFlag = true;
	m_nAns = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// �|���S���̃C���X�^���X����
	CPolygon *pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->m_pos = pos;
		pPolygon->m_size = size;
		pPolygon->Init();
		pPolygon->SetPosition(pos);
		pPolygon->SetSize(size);
		pPolygon->BindTexture(CManager::GetTexture()->SetTextureType(CTexture::TEXTURETYPE_NORMAL));
	}

	return pPolygon;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{
	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾
	CPadX *pPadX = CManager::GetPadX();

	// �V�t�g�����Ȃ���Ŕ�����
	if (pKeyboard->GetPress(DIK_LSHIFT) == true || pKeyboard->GetPress(DIK_RSHIFT) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)
	{
		// �E�ړ�
		if (pKeyboard->GetTrigger(DIK_RIGHT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_pos.x += 1.0f;
		}
		// ���ړ�
		if (pKeyboard->GetTrigger(DIK_LEFT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_pos.x -= 1.0f;
		}
		// ���ړ�
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_pos.y += 1.0f;
		}
		// ��ړ�
		if (pKeyboard->GetTrigger(DIK_UP) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_UP) == true)
		{
			m_pos.y -= 1.0f;
		}

		// �����g��
		if (pKeyboard->GetTrigger(DIK_W) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_UP) == true)
		{
			m_size.y += 1.0f;
		}
		// �����k��
		if (pKeyboard->GetTrigger(DIK_S) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_size.y -= 1.0f;
		}
		// ���g��
		if (pKeyboard->GetTrigger(DIK_D) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_size.x += 1.0f;
		}
		// ���k��
		if (pKeyboard->GetTrigger(DIK_A) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_size.x -= 1.0f;
		}
	}
	else
	{
		// �E�ړ�
		if (pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_pos.x += 4.0f;
		}
		// ���ړ�
		if (pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_pos.x -= 4.0f;
		}
		// ���ړ�
		if (pKeyboard->GetPress(DIK_DOWN) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_pos.y += 4.0f;
		}
		// ��ړ�
		if (pKeyboard->GetPress(DIK_UP) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_UP) == true)
		{
			m_pos.y -= 4.0f;
		}

		// �����g��
		if (pKeyboard->GetPress(DIK_W) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_UP) == true)
		{
			m_size.y += 2.0f;
		}
		// �����k��
		if (pKeyboard->GetPress(DIK_S) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_size.y -= 2.0f;
		}
		// ���g��
		if (pKeyboard->GetPress(DIK_D) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_size.x += 2.0f;
		}
		// ���k��
		if (pKeyboard->GetPress(DIK_A) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_size.x -= 2.0f;
		}
	}

	// �ʒu�������Z�b�g
	if (pKeyboard->GetRelease(DIK_X) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_Y) == true)
	{
		m_size.x = 40.0f;
		m_size.y = 40.0f;
		m_pos.x = SCREEN_CENTER_X;
		m_pos.y = SCREEN_CENTER_Y;
	}

	// �t�@�C���ɏ����o��
	if (pKeyboard->GetTrigger(DIK_P) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
	{
		FILE *pFile = fopen("data//text//pos.txt", "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "D3DXVECTOR3(%.1ff, %.1ff, %.1ff), D3DXVECTOR2(%.1ff, %.1ff)", m_pos.x, m_pos.y, m_pos.z, m_size.x, m_size.y);
		}
	}
		// �e�N�X�`�����f/����
	if (pKeyboard->GetTrigger(DIK_RETURN) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		if (m_bTextureFlag == true)
		{
			// �e�N�X�`��������
			DeleteTexture();
			m_bTextureFlag = false;
		}
		else if (m_bTextureFlag == false)
		{
			// �e�N�X�`�������蓖��
			BindTexture(CManager::GetTexture()->SetTextureType(CTexture::TEXTURETYPE_NORMAL));
			m_bTextureFlag = true;
		}
	}
		// �ʒu�ݒ�
		SetPosition(m_pos);

		// �傫���ݒ�
		SetSize(m_size);

		CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CPolygon::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �傫���̎擾
//=============================================================================
D3DXVECTOR2 CPolygon::GetSize(void)
{
	return m_size;
}