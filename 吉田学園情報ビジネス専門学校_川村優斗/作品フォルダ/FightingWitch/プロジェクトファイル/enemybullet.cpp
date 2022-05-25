//=============================================================================
//
// �G�e�̏��� [enemybullet.cpp]
// Author : �쑺�D�l
//
//=============================================================================
#include "enemybullet.h"
#include"explosion.h"
#include"effect.h"
#include"sound.h"
#include"life.h"
#include"time.h"
#include"game.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyBullet::CEnemyBullet()
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_ENEMYBULLET);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyBullet::~CEnemyBullet()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyBullet::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyBullet::Update(void)
{
	// �v���C���[�̈ړ�
	D3DXVECTOR3 pPos = Getposition();

	// ���݂̎��Ԃ��擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// �ړ��ʂ�ݒ�
		pPos += m_move;
	}

	CScene2D::Update();

	//�v���C���[�̈ʒu�ݒ�
	SetPosition(pPos);

	// �v���C���[�̏�Ԃ��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	// �G�t�F�N�g�̐���
	CEffect::Create(D3DXVECTOR3(pPos.x + 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);

	// ���������炷
	m_nLife--;

	if (nTime != 0)
	{
		if (m_nLife == 0)
		{// �������Ȃ��Ȃ�Ɣ�����������
			CExplosion::Create(pPos, D3DXVECTOR2(100.0f, 100.0f), CTexture::TEXTURETYPE_EXPLOSION);
			Uninit();
		}
		else if (-100.0f > pPos.x)
		{// ��ʊO�ɏo��Ə�����
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CEnemyBullet * CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int life, CTexture::TEXTURE_TYPE type)
{
	// �e�̃C���X�^���X����
	CEnemyBullet *pBullet = new CEnemyBullet;

	// �e�̏���
	if (pBullet != NULL)
	{
		pBullet->m_move = move;
		pBullet->m_nLife = life;
		pBullet->Init();
		pBullet->SetPosition(pos);
		pBullet->SetSize(size);
		pBullet->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}

	return pBullet;
}