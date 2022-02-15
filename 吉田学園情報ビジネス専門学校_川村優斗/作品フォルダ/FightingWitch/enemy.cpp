//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "enemy.h"
#include"effect.h"
#include"player.h"
#include"score.h"
#include"sound.h"
#include"game.h"
#include"time.h"
#include"life.h"
#include"padx.h"
#include"enemybullet.h"
#include"explosion.h"
#include <stdlib.h>
#include <time.h>

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bDeadFlag = false;
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);
	m_BulletCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();

	// 鳥の初動を決める（上か下か）
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
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// スコアの情報の取得
	CScore *pScore = CGame::GetScore();

	// 現在の時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	// 端っこで消えたか弾が当たって消えたか
	switch (m_bDeadFlag)
	{
	case true:
		// 端で消えた場合はスコアを加算しない
		break;
	case false:
		// プレイヤーの移動と座標の代入
		D3DXVECTOR3 pPos = Getposition();

		// 一部の敵はスコア高めに
		if (m_type == ENEMY_PLANE)
		{
			pScore->AddScore(20);
		}
		else
		{
			// タイムアップ時の敵の終了処理でスコアが入らないように
			if (nTime != 0)
			{
				pScore->AddScore(10);
			}
		}
		// エフェクトの生成
		CEffect::Create(D3DXVECTOR3(pPos.x, pPos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100.0f, 50, 0.001f, CTexture::TEXTURETYPE_EFFECT);
		break;
	}
	CScene2D::Uninit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// プレイヤーの移動と座標の代入
	D3DXVECTOR3 pPos = Getposition();
	m_pos = Getposition();
	D3DXVECTOR2 pSize = GetSize();

	// 現在の時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// プレイヤーの状態を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	if (nTime != 0)
	{
		//移動量を設定
		pPos.x -= m_move.x;

		if (m_type == ENEMY_JIGZAG)
		{
			if (pPos.y < 0)
			{
				m_bFlag = true;
			}
			else if (pPos.y > SCREEN_HEIGHT)
			{
				m_bFlag = false;
			}
			// 上移動
			if (m_bFlag == false)
			{
				pPos.y -= 7.0f;
			}
			// 下移動
			else
			{
				pPos.y += 7.0f;
			}
		}
		if (m_type == ENEMY_HOMING)
		{
			// プレイヤーの位置を取得
			m_PlayerPos = pPlayer->GetPos();

			// 上移動
			if (pPos.y > m_PlayerPos.y)
			{
				pPos.y -= 7.0f;
			}
			// 下移動
			else if (pPos.y < m_PlayerPos.y)
			{
				pPos.y += 7.0f;
			}
			else if (pPos.y == m_PlayerPos.y)
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
	}

	CScene2D::Update();

	// 敵の位置設定
	SetPosition(pPos);

	// 敵弾の発射
	if (nTime != 0)
	{
		if (m_type == ENEMY_SUPER || m_type == ENEMY_PLANE)
		{
			m_BulletCount++;
			if (m_BulletCount == 50)
			{
				CEnemyBullet::Create(D3DXVECTOR3(pPos.x, pPos.y - 5.0f, 0.0f), D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), 60, CTexture::TEXTURETYPE_ENEMYBULLET);
				m_BulletCount = 0;
			}
		}
	}

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
		{
			// 敵の情報を取得
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);

			if (pScene != NULL)
			{
				// オブジェクトの種類を取得
				CScene::OBJTYPE objType = pScene->GetObjType();

				// 敵の位置を取得
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->Getposition();

				// 敵の大きさを取得
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// スコアを取得
				CScore *pScore = CGame::GetScore();

				// プレイヤーとぶつかったら
				if (objType == OBJTYPE_PLAYER)
				{
					if (pPos.y <= pos.y + size.y && pPos.x <= pos.x + size.x && pPos.y >= pos.y - size.y && pPos.x >= pos.x - size.x)
					{// 無敵時間突入
						CPlayer::PLAYERSTATE state = pPlayer->GetState();
						if (state == CPlayer::STATE_MUTEKI)
						{
							// サウンド取得
							CSound *pSound = CManager::GetSound();
							pSound->Play(pSound->SOUND_LABEL_EXPLOSION);
							pSound->SetVolume(pSound->SOUND_LABEL_EXPLOSION, 0.5f);
							
							// 爆発を生成し
							CExplosion::Create(pPos, pSize, CTexture::TEXTURETYPE_EXPLOSION);

							// エフェクトの生成
							CEffect::Create(D3DXVECTOR3(pPos.x, pPos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100.0f, 50, 0.001f, CTexture::TEXTURETYPE_EFFECT);
							
							// スコア加算
							pScore->AddScore(10);

							Uninit();
						}
					}
				}
			}
		}
	}

	// ライフ取得
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	// 画面外に出たときとライフ0でゲームオーバーになったら消える
	if (pPos.x <= -50.0f || nLife == 0)
	{
		m_bDeadFlag = true;
		Uninit();
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CEnemy::ENEMYTYPE type, CTexture::TEXTURE_TYPE ntype)
{
	// 敵のインスタンス生成
	CEnemy *pEnemy = new CEnemy;

	// 敵の準備
	if (pEnemy != NULL)
	{
		pEnemy->m_type = type;
		pEnemy->m_move = move;
		pEnemy->Init();
		pEnemy->SetPosition(pos);
		pEnemy->SetSize(size);
		pEnemy->BindTexture(CManager::GetTexture()->SetTextureType(ntype));

		// アニメーションの初期設定
		if (type == ENEMY_NORMAL)
		{
			pEnemy->SetVtxTex(0, 0.5f, 0.5f, 1.0f);
		}
	}

	return pEnemy;
}

//=============================================================================
// 敵の種類を取得
//=============================================================================
CEnemy::ENEMYTYPE CEnemy::GetEnemyType(void)
{
	return m_type;
}

//=============================================================================
// ライフ減らし
//=============================================================================
void CEnemy::LifeDamage(void)
{
	m_nLife--;
}