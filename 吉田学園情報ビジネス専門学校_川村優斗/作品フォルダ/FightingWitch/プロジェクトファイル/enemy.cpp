//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "enemy.h"
#include"effect.h"
#include"player.h"
#include"score.h"
#include"sound.h"
#include"game.h"
#include"time.h"
#include"life.h"
#include"enemybullet.h"
#include"explosion.h"
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDeadFlag = false;
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);
	m_BulletCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();

	// ���̏��������߂�i�ォ�����j
	int nRand = rand() % 100;
	if (nRand % 2 == 0)
	{
		m_bFlag = false;
	}
	else
	{
		m_bFlag = true;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// �[�����ŏ��������e���������ď�������
	switch (m_bDeadFlag)
	{
	case true:
		// �[�ŏ������ꍇ�̓X�R�A�����Z���Ȃ�
		break;
	case false:
		// �v���C���[�̈ړ��ƍ��W�̑��
		D3DXVECTOR3 pPos = Getposition();

		// �X�R�A�̏��̎擾
		CScore *pScore = CGame::GetScore();

		// �ꕔ�̓G�̓X�R�A���߂�
		if (m_type == ENEMY_PLANE)
		{
			pScore->AddScore(20);
		}
		else
		{
			// ���݂̎��Ԃ��擾
			CTime *pTime = CGame::GetTime();
			int nTime = pTime->GetTime();
			// �^�C���A�b�v���̓G�̏I�������ŃX�R�A������Ȃ��悤��
			if (nTime != 0)
			{
				pScore->AddScore(10);
			}
		}
		// �G�t�F�N�g�̐���
		CEffect::Create(D3DXVECTOR3(pPos.x, pPos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100.0f, 50, 0.001f, CTexture::TEXTURETYPE_EFFECT);
		break;
	}
	CScene2D::Uninit();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �v���C���[�̈ړ��ƍ��W�̑��
	D3DXVECTOR3 pPos = Getposition();
	m_pos = pPos;
	D3DXVECTOR2 pSize = GetSize();

	// ���݂̎��Ԃ��擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	// �v���C���[�̏�Ԃ��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	if (nTime != 0)
	{
		EnemyMove();
	}

	CScene2D::Update();

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
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

				// �X�R�A���擾
				CScore *pScore = CGame::GetScore();

				// �v���C���[�ƂԂ�������
				if (objType == OBJTYPE_PLAYER)
				{
					if (pPos.y <= pos.y + size.y && pPos.x <= pos.x + size.x && pPos.y >= pos.y - size.y && pPos.x >= pos.x - size.x)
					{// ���G���ԓ˓�
						CPlayer::PLAYERSTATE state = pPlayer->GetState();
						if (state == CPlayer::STATE_MUTEKI)
						{
							// �T�E���h�擾
							CSound *pSound = CManager::GetSound();
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);
							pSound->SetVolume(pSound->SOUND_LABEL_EXPLOSION, 0.5f);
							
							// �����𐶐���
							CExplosion::Create(pPos, pSize, CTexture::TEXTURETYPE_EXPLOSION);

							// �G�t�F�N�g�̐���
							CEffect::Create(D3DXVECTOR3(pPos.x, pPos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100.0f, 50, 0.001f, CTexture::TEXTURETYPE_EFFECT);
							
							// �X�R�A���Z
							pScore->AddScore(10);

							Uninit();
						}
					}
				}
			}
		}
	}

	// ���C�t�擾
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	// ��ʊO�ɏo���Ƃ��ƃ��C�t0�ŃQ�[���I�[�o�[�ɂȂ����������
	if (pPos.x <= -50.0f || nLife == 0)
	{
		m_bDeadFlag = true;
		Uninit();
	}
}

//=============================================================================
// ��������
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CEnemy::ENEMYTYPE type, CTexture::TEXTURE_TYPE ntype)
{
	// �G�̃C���X�^���X����
	CEnemy *pEnemy = new CEnemy;

	// �G�̏���
	if (pEnemy != NULL)
	{
		pEnemy->m_type = type;
		pEnemy->m_move = move;
		pEnemy->Init();
		pEnemy->SetPosition(pos);
		pEnemy->SetSize(size);
		pEnemy->BindTexture(CManager::GetTexture()->SetTextureType(ntype));

		// �A�j���[�V�����̏����ݒ�
		if (type == ENEMY_NORMAL)
		{
			pEnemy->SetVtxTex(0, 0.5f, 0.5f, 1.0f);
		}
	}

	return pEnemy;
}

//=============================================================================
// �G�̎�ނ��擾
//=============================================================================
CEnemy::ENEMYTYPE CEnemy::GetEnemyType(void)
{
	return m_type;
}

//=============================================================================
// ���C�t���炵
//=============================================================================
void CEnemy::LifeDamage(void)
{
	m_nLife--;
}

void CEnemy::EnemyMove(void)
{
	// �v���C���[�̏�Ԃ��擾
	CPlayer *pPlayer = CGame::GetPlayer();

	// �v���C���[�̈ʒu���擾
	m_PlayerPos = pPlayer->GetPos();

	//�ړ��ʂ�ݒ�
	m_pos.x -= m_move.x;

	if (m_type == ENEMY_JIGZAG)
	{
		if (m_pos.y < 0)
		{
			m_bFlag = true;
		}
		else if (m_pos.y > SCREEN_HEIGHT)
		{
			m_bFlag = false;
		}
		// ��ړ�
		if (m_bFlag == false)
		{
			m_pos.y -= 7.0f;
		}
		// ���ړ�
		else
		{
			m_pos.y += 7.0f;
		}
	}
	if (m_type == ENEMY_HOMING)
	{
		// ��ړ�
		if (m_pos.y > m_PlayerPos.y)
		{
			m_pos.y -= 7.0f;
		}
		// ���ړ�
		else if (m_pos.y < m_PlayerPos.y)
		{
			m_pos.y += 7.0f;
		}
		else if (m_pos.y == m_PlayerPos.y)
		{

		}
	}
	if (m_type == ENEMY_NORMAL)
	{
		m_nCounterAnim++;
		if (m_nCounterAnim > 18)
		{
			m_nCounterAnim = 0;

			m_nPatternAnim++;

			CScene2D::SetVtxTex(m_nPatternAnim, 0.5f, 0.5f, 1.0f);
		}
	}

	// �G�̈ʒu�ݒ�
	SetPosition(m_pos);

	// �G�e�̔���
	if (m_type == ENEMY_SUPER || m_type == ENEMY_PLANE)
	{
		m_BulletCount++;
		if (m_BulletCount == 50)
		{
			CEnemyBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, 0.0f), D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 60, CTexture::TEXTURETYPE_ENEMYBULLET);
			m_BulletCount = 0;
		}
	}
}
