//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"sound.h"
#include"game.h"
#include"time.h"
#include"item.h"
#include"texture.h"
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	// �v���C���[�̈ړ�
	D3DXVECTOR3 pPos = Getposition();
	m_pos = pPos;

	// �G�̏��̎擾
	CEnemy *pEnemy = CGame::GetEnemy();
	
	// �X�R�A�̎擾
	CScore *pScore = CGame::GetScore();

	// ���݂̎��Ԃ��擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// �ړ��ʂ�ݒ�
		pPos += m_move;
	}

	CScene2D::Update();

	// �v���C���[�̈ʒu�ݒ�
	SetPosition(pPos);

	// �G�t�F�N�g�̐���
	if (m_nType == 0)
	{
		// �ʏ�e
		CEffect::Create(D3DXVECTOR3(pPos.x - 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);
	}
	else
	{
		// �A�ˎ�
		CEffect::Create(D3DXVECTOR3(pPos.x - 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 30.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);
	}
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			// �G�̏����擾
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objType = pScene->GetObjType();

				// �G�̈ʒu���擾
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->Getposition();

				// �G�̑傫�����擾
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// �G�ƂԂ�������
				if (objType == OBJTYPE_ENEMY)
				{
					if (pPos.y <= pos.y + size.y && pPos.x <= pos.x + size.x && pPos.y >= pos.y - size.y && pPos.x >= pos.x - size.x)
					{
						// �T�E���h�擾
						CSound *pSound = CManager::GetSound();

						// �������Đ�
						pSound->Play(pSound->SOUND_LABEL_EXPLOSION);
						pSound->SetVolume(pSound->SOUND_LABEL_EXPLOSION, 0.5f);

						// �G������
						pScene->Uninit();

						// �����𐶐���
						CExplosion::Create(pos, size, CTexture::TEXTURETYPE_EXPLOSION);
						
						// �A�C�e���𐶐���
						ItemCreate();

						// ������
						Uninit();
						return;
					}
				}
			}
		}
	}
	// ���������炷
	m_nLife--;
	if (nTime != 0)
	{
		if (m_nLife == 0)
		{// �������Ȃ��Ȃ�Ɣ�����������
			CExplosion::Create(pPos, D3DXVECTOR2(100.0f, 100.0f), CTexture::TEXTURETYPE_EXPLOSION);
			Uninit();
		}
		else if (880.0f < pPos.x)
		{// ��ʊO�ɏo��Ə�����
			Uninit();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �A�C�e���̐���
//=============================================================================
void CBullet::ItemCreate(void)
{
	int m_nRand, nRand2;

	// �A�C�e���̏o����
	int nItemInterval;

	char aFile[256];
	FILE *pFile = fopen("data//text//setting.txt", "r");

	if (pFile != NULL)
	{
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "ITEM_INTERVAL") == 0)
			{
				// �e�N�X�`����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nItemInterval);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// �I��
				break;
			}
		}
		fclose(pFile);
	}

	// �A�C�e�����o����
	m_nRand = rand() % nItemInterval;

	if (m_nRand == 0)
	{
		// �Ȃ�̃A�C�e�����o����
		nRand2 = rand() % 4;

		// �A�C�e�����o��
		if (nRand2 == 0)
		{
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CTexture::TEXTURETYPE_ITEMLIFE);
		}
		if (nRand2 == 1)
		{
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CTexture::TEXTURETYPE_ITEMMUTEKI);
		}
		if (nRand2 == 2)
		{
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(-3.0f, 0.0f, 0.0f), D3DXVECTOR2(70.0f, 50.0f), CTexture::TEXTURETYPE_ITEMSCORE);
		}
		if (nRand2 == 3)
		{
			CItem::Create(D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f), D3DXVECTOR3(-6.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 50.0f), CTexture::TEXTURETYPE_ITEMGUN);
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int type, int life, CTexture::TEXTURE_TYPE ntype)
{
	// �e�̃C���X�^���X����
	CBullet *pBullet = new CBullet;

	// �e�̏���
	if (pBullet != NULL)
	{
		pBullet->m_nLife = life;
		pBullet->m_nType = type;
		pBullet->m_move = move;
		pBullet->Init();
		pBullet->SetPosition(pos);
		pBullet->SetSize(size);
		pBullet->BindTexture(CManager::GetTexture()->SetTextureType(ntype));
	}
	return pBullet;
}