//=============================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "item.h"
#include"score.h"
#include"game.h"
#include"life.h"
#include"player.h"
#include"sound.h"
#include"time.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CItem::Init(void)
{
	CScene2D::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	switch (m_ItemType)
	{
		// ���C�t��
	case CTexture::TEXTURETYPE_ITEMLIFE:
		SetObjType(CScene::OBJTYPE_ITEM_LIFE);
		break;
		// ���G
	case CTexture::TEXTURETYPE_ITEMMUTEKI:
		SetObjType(CScene::OBJTYPE_ITEM_MUTEKI);
		break;
		// �X�R�A�A�b�v
	case CTexture::TEXTURETYPE_ITEMSCORE:
		SetObjType(CScene::OBJTYPE_ITEM_SCORE);
		break;
		// �A��
	case CTexture::TEXTURETYPE_ITEMGUN:
		SetObjType(CScene::OBJTYPE_ITEM_SUPER);
		break;
	default:
		break;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CItem::Update(void)
{
	// �v���C���[�̏����擾
	D3DXVECTOR3 pPos = Getposition();
	D3DXVECTOR2 pSize = GetSize();

	// ���݂̎��Ԃ��擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// �ړ��ʂ�ݒ�
		pPos += m_move;
	}
	// �v���C���[�̈ʒu�ݒ�
	SetPosition(pPos);

	CScene2D::Update();

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
		{
			// �v���C���[�̏����擾
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objType = pScene->GetObjType();

				// �v���C���[�̈ʒu���擾
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->Getposition();

				// �v���C���[�̑傫�����擾
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// �A�C�e�����擾�����ۂ̏���
				if (objType == OBJTYPE_PLAYER)
				{
					if (pPos.y <= pos.y + size.y && pPos.x <= pos.x + size.x && pPos.y >= pos.y - size.y && pPos.x >= pos.x - size.x)
					{
						ItemGet();
						Uninit();
					}
				}
			}
		}
	}
	if (SCREEN_WIDTH < pPos.x)
	{// ��ʊO�ɏo��Ə�����
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �A�C�e�����擾�����ۂ̏���
//=============================================================================
void CItem::ItemGet(void)
{
	// �T�E���h�擾
	CSound *pSound = CManager::GetSound();

	// �v���C���[�̏�Ԃ��擾
	CPlayer *pPlayer = CGame::GetPlayer();
	CPlayer::PLAYERSTATE state = pPlayer->GetState();

	// ���݂̃��C�t���擾
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	// ���݂̃X�R�A���擾
	CScore *pScore = CGame::GetScore();

	switch (m_ItemType)
	{
	case CTexture::TEXTURETYPE_ITEMSCORE:
		// �A�C�e���擾�T�E���h
		pSound->Play(pSound->SOUND_LABEL_SCOREUP);
		pSound->SetVolume(pSound->SOUND_LABEL_SCOREUP, 0.2f);

		// �X�R�A10�_�A�b�v
		pScore->AddScore(10);
		break;

	case CTexture::TEXTURETYPE_ITEMLIFE:

		// �A�C�e���擾�T�E���h
		pSound->Play(pSound->SOUND_LABEL_SCOREUP);
		pSound->SetVolume(pSound->SOUND_LABEL_SCOREUP, 0.2f);

		// �̗͂����^���̏ꍇ�̓X�R�A�����Z
		if (nLife == 8)
		{
			pScore->AddScore(10);
		}
		else
		{// �̗͉�
			pLife->AddLife(1);
		}
		break;

	case CTexture::TEXTURETYPE_ITEMMUTEKI:
		if (state != CPlayer::STATE_RENSYA && state != CPlayer::STATE_DAMAGE)
		{// ���G�˓�
			pPlayer->ChangeState(CPlayer::STATE_MUTEKI);
		}
		break;
	case CTexture::TEXTURETYPE_ITEMGUN:
		if (state != CPlayer::STATE_MUTEKI && state != CPlayer::STATE_DAMAGE)
		{// �A�˓˓�
			pPlayer->ChangeState(CPlayer::STATE_RENSYA);
		}
		break;
	}
}

//=============================================================================
// ��������
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// �A�C�e���̃C���X�^���X����
	CItem *pItem = new CItem;


	// �A�C�e���̏���
	if (pItem != NULL)
	{
		pItem->m_ItemType = type;
		pItem->m_move = move;
		pItem->Init();
		pItem->SetPosition(pos);
		pItem->SetSize(size);
		pItem->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}
	return pItem;
}