//=============================================================================
//
// ゲーム部分の処理 [game.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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
// 静的メンバ変数
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
// コンストラクタ
//=============================================================================
CGame::CGame()
{
	// メンバ変数の初期化
	m_nEnemyCnt = 0;
	m_fPos = 0.0f;

	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// 音楽の再生、音量調整
	pSound->Play(pSound->SOUND_LABEL_BGM_GAME);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_GAME, 0.2f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	// 数字のテクスチャロード
	CNumber::Load();

	// 設定の読み込み
	LoadFile();

	// 背景の生成
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 100.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 1.5f, SCREEN_HEIGHT / 1.5f), CBg::BGTYPE_GAME1, CTexture::TEXTURETYPE_BGGAME1);
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 350.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CBg::BGTYPE_GAME2, CTexture::TEXTURETYPE_BGGAME2);
	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y + 350.0f, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), CBg::BGTYPE_GAME3, CTexture::TEXTURETYPE_BGGAME2);

	// 右のステータスの生成
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 2), CTexture::TEXTURETYPE_RIGHT);

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(350.0f, 300.0f, 0.0f), D3DXVECTOR2(80.0f, 60.0f), CTexture::TEXTURETYPE_PLAYER);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_CENTER_X + 330.0f, 650.0f, 0.0f), D3DXVECTOR2(25.0f, 47.0f));

	// ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(SCREEN_CENTER_X + 300.0f, 240.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), m_nLife);

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(SCREEN_CENTER_X + 380.0f, 90.0f, 0.0f), D3DXVECTOR2(25.0f, 47.0f), m_nTime);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// サウンドの取得
	CSound *pSound = CManager::GetSound();
	
	// 音楽の停止
	pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

	// 数字のテクスチャアンロード
	CNumber::Unload();

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// 現在の残り時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		m_nEnemyCnt++;
		if (m_nItemPer != 0)
		{
			while (m_nEnemyCnt >= m_nItemPer)
			{
				float nPos = 0.0f;	// ランダム変数格納用
				float nPos2 = 0.0f;	// ランダム変数格納用

				// 出現位置が被りすぎなくなるまで無限ループ
				while (1)
				{
					// 敵の出現位置をランダムで決める
					nPos = rand() % 550;
					nPos2 = nPos - m_fPos;

					if (nPos != m_fPos)
					{
						if (nPos2 > 0)
						{
							if (nPos2 >= 200)
							{
								// どの敵を出すか
								int type = rand() % 6;
								// 敵の生成
								// かぼちゃ
								if (type == CEnemy::ENEMY_NORMAL)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_NORMAL, CTexture::TEXTURETYPE_ENEMYJACK);
								}
								// 黒い鳥
								if (type == CEnemy::ENEMY_JIGZAG)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(7.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_JIGZAG, CTexture::TEXTURETYPE_ENEMYBIRD);
								}
								// 魔女
								if (type == CEnemy::ENEMY_SUPER)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_SUPER, CTexture::TEXTURETYPE_ENEMYWITCH);
								}
								// 戦闘機
								if (type == CEnemy::ENEMY_PLANE)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_PLANE, CTexture::TEXTURETYPE_ENEMYPLANE);
								}
								// 赤い鳥
								if (type == CEnemy::ENEMY_HOMING)
								{
									CEnemy::Create(D3DXVECTOR3(850.0f, nPos + 100.0f, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), CEnemy::ENEMY_HOMING, CTexture::TEXTURETYPE_ENEMYBIRD2);
								}
								m_fPos = nPos;
								break;
							}
						}
						// 出現位置が被りすぎないように設定
						else if (nPos2 < 0)
						{
							if (nPos2 <= -200)
							{
								int type = rand() % 5;	// 敵の種類

								// 敵の生成
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
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
}

//=============================================================================
// ファイルの読み込み
//=============================================================================
void CGame::LoadFile(void)
{
	char aFile[256];
	FILE *pFile = fopen("data//text//setting.txt", "r");

	if (pFile != NULL)
	{
		// END_SCRIPTまで無限に読み込む
		while (true)
		{
			fscanf(pFile, "%s", &aFile[0]);
			if (strcmp(&aFile[0], "TIME_LIMIT") == 0)
			{
				// テクスチャ数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nTime);
			}
			if (strcmp(&aFile[0], "LIFE") == 0)
			{
				// テクスチャ数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nLife);
			}
			if (strcmp(&aFile[0], "ENEMY_INTERVAL") == 0)
			{
				// アイテムの出現率
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &m_nItemPer);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// 終了
				break;
			}
		}
		fclose(pFile);
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CGame * CGame::Create(void)
{
	// ゲームのインスタンス生成
	CGame *pGame = new CGame;

	// ゲームの準備
	if (pGame != NULL)
	{
		pGame->Init();
	}
	return pGame;
}

//=============================================================================
// 背景の取得
//=============================================================================
CBg * CGame::GetBg(void)
{
	return m_pBg;
}

//=============================================================================
// 弾の取得
//=============================================================================
CBullet * CGame::GetBullet(void)
{
	return m_pBullet;
}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// スコアの取得
//=============================================================================
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// ライフの取得
//=============================================================================
CLife * CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// エフェクトの取得
//=============================================================================
CEffect * CGame::GetEffect(void)
{
	return m_pEffect;
}

//=============================================================================
// 時間の取得
//=============================================================================
CTime * CGame::GetTime(void)
{
	return m_pTime;
}

//=============================================================================
// アイテムの取得
//=============================================================================
CItem * CGame::GetItem(void)
{
	return m_pItem;
}

//=============================================================================
// 敵の取得
//=============================================================================
CEnemy * CGame::GetEnemy(void)
{
	return m_pEnemy;
}

//=============================================================================
// 敵弾の取得
//=============================================================================
CEnemyBullet * CGame::GetEnemyBullet(void)
{
	return m_pEnemyBullet;
}