//=============================================================================
//
// �Q�[�������̏��� [game.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "game.h"
#include"manager.h"
#include"player.h"
#include"manager.h"
#include"bullet.h"
#include"sound.h"
#include"explosion.h"
#include"bg.h"
#include"enemy.h"
#include"number.h"
#include"score.h"
#include"polygon.h"
#include"life.h"
#include"effect.h"
#include"fade.h"
#include"time.h"
#include"ui.h"
#include"enemybullet.h"
#include"item.h"
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CBg *CGame::m_pBg = NULL;
CBullet *CGame::m_pBullet = NULL;
CPlayer *CGame::m_pPlayer = NULL;
CScore *CGame::m_pScore = NULL;
CLife *CGame::m_pLife = NULL;
CEffect *CGame::m_pEffect = NULL;
CTime *CGame::m_pTime = NULL;
CItem *CGame::m_pItem = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CEnemyBullet *CGame::m_pEnemyBullet = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	// �����o�ϐ��̏�����
	m_nEnemyCnt = 0;
	m_fPos = 0.0f;

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// ���y�̍Đ��A���ʒ���
	pSound->Play(pSound->SOUND_LABEL_BGM_GAME);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_GAME, 0.2f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init(void)
{
	// �����̃e�N�X�`�����[�h
	CNumber::Load();

	// �ݒ�̓ǂݍ���
	LoadFile();

	// �w�i�̐���
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 100.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f), CBg::BGTYPE_GAME1, CTexture::TEXTURETYPE_BGGAME1);
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 350.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CBg::BGTYPE_GAME2, CTexture::TEXTURETYPE_BGGAME2);
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 350.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CBg::BGTYPE_GAME3, CTexture::TEXTURETYPE_BGGAME2);

	// �E�̃X�e�[�^�X�̐���
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 2), CTexture::TEXTURETYPE_RIGHT);

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(350.0f, 300.0f, 0.0f), D3DXVECTOR2(80.0f, 60.0f), CTexture::TEXTURETYPE_PLAYER);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_CENTER_X + 330.0f, 650.0f, 0.0f), D3DXVECTOR2(25.0f, 47.0f));

	// ���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(SCREEN_CENTER_X + 300.0f, 240.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), m_nLife);

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_CENTER_X + 380.0f, 90.0f, 0.0f), D3DXVECTOR2(25.0f, 47.0f), m_nTime);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();
	
	// ���y�̒�~
	pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

	// �����̃e�N�X�`���A�����[�h
	CNumber::Unload();

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �t�F�[�h�̎擾
	CFade *pFade = CManager::GetFade();

	// ���݂̎c�莞�Ԃ��擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		m_nEnemyCnt++;
		if (m_nItemPer != 0)
		{
			while (m_nEnemyCnt >= m_nItemPer)
			{
				float nPos = 0.0f;	// �����_���ϐ��i�[�p
				float nPos2 = 0.0f;	// �����_���ϐ��i�[�p

				// �o���ʒu����肷���Ȃ��Ȃ�܂Ŗ������[�v
				while (1)
				{
					// �G�̏o���ʒu�������_���Ō��߂�
					nPos = rand() % 550;
					nPos2 = nPos - m_fPos;

					if (nPos != m_fPos)
					{
						if (nPos2 > 0)
						{
							if (nPos2 >= 200)
							{
								// �ǂ̓G���o����
								int type = rand() % 6;
								// �G�̐���
								// ���ڂ���
								if (type == CEnemy::ENEMY_NORMAL)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_NORMAL, CTexture::TEXTURETYPE_ENEMYJACK);
								}
								// ������
								if (type == CEnemy::ENEMY_JIGZAG)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_JIGZAG, CTexture::TEXTURETYPE_ENEMYBIRD);
								}
								// ����
								if (type == CEnemy::ENEMY_SUPER)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_SUPER, CTexture::TEXTURETYPE_ENEMYWITCH);
								}
								// �퓬�@
								if (type == CEnemy::ENEMY_PLANE)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_PLANE, CTexture::TEXTURETYPE_ENEMYPLANE);
								}
								// �Ԃ���
								if (type == CEnemy::ENEMY_HOMING)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_HOMING, CTexture::TEXTURETYPE_ENEMYBIRD2);
								}
								m_fPos = nPos;
								break;
							}
						}
						// �o���ʒu����肷���Ȃ��悤�ɐݒ�
						else if (nPos2 < 0)
						{
							if (nPos2 <= -200)
							{
								int type = rand() % 5;	// �G�̎��

								// �G�̐���
								if (type == CEnemy::ENEMY_NORMAL)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(5.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_NORMAL, CTexture::TEXTURETYPE_ENEMYJACK);
								}
								if (type == CEnemy::ENEMY_JIGZAG)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_JIGZAG, CTexture::TEXTURETYPE_ENEMYBIRD);
								}
								if (type == CEnemy::ENEMY_SUPER)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_SUPER, CTexture::TEXTURETYPE_ENEMYWITCH);
								}
								if (type == CEnemy::ENEMY_PLANE)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR2(60.0f, 50.0f), CEnemy::ENEMY_PLANE, CTexture::TEXTURETYPE_ENEMYPLANE);
								}
								if (type == CEnemy::ENEMY_HOMING)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_HOMING, CTexture::TEXTURETYPE_ENEMYBIRD2);
								}
								m_fPos = nPos;
								break;
							}
						}
					}
				}
				m_nEnemyCnt = 0;
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// �t�@�C���̓ǂݍ���
//=============================================================================
void CGame::LoadFile(void)
{
	char aFile[256];
	FILE *pFile = fopen("data//text//setting.txt", "r");

	if (pFile != NULL)
	{
		// END_SCRIPT�܂Ŗ����ɓǂݍ���
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "TIME_LIMIT") == 0)
			{
				// �e�N�X�`����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nTime);
			}
			if (strcmp(&aFile[0], "LIFE") == 0)
			{
				// �e�N�X�`����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nLife);
			}
			if (strcmp(&aFile[0], "ENEMY_INTERVAL") == 0)
			{
				// �A�C�e���̏o����
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nItemPer);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// �I��
				break;
			}
		}
		fclose(pFile);
	}
}

//=============================================================================
// ��������
//=============================================================================
CGame * CGame::Create(void)
{
	// �Q�[���̃C���X�^���X����
	CGame *pGame = new CGame;

	// �Q�[���̏���
	if (pGame != NULL)
	{
		pGame->Init();
	}
	return pGame;
}

//=============================================================================
// �w�i�̎擾
//=============================================================================
CBg * CGame::GetBg(void)
{
	return m_pBg;
}

//=============================================================================
// �e�̎擾
//=============================================================================
CBullet * CGame::GetBullet(void)
{
	return m_pBullet;
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ���C�t�̎擾
//=============================================================================
CLife * CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// �G�t�F�N�g�̎擾
//=============================================================================
CEffect * CGame::GetEffect(void)
{
	return m_pEffect;
}

//=============================================================================
// ���Ԃ̎擾
//=============================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
CItem * CGame::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// �G�̎擾
//=============================================================================
CEnemy * CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// �G�e�̎擾
//=============================================================================
CEnemyBullet * CGame::GetEnemyBullet(void)
{
	return m_pEnemyBullet;
}