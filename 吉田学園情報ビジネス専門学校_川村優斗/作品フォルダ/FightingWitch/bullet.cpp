//=============================================================================
//
// 弾の処理 [bullet.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(int nPriority) : CScene2D(nPriority)
{
	// オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BULLET);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	// プレイヤーの移動
	D3DXVECTOR3 pPos = Getposition();
	m_pos = pPos;

	// 敵の情報の取得
	CEnemy *pEnemy = CGame::GetEnemy();
	
	// スコアの取得
	CScore *pScore = CGame::GetScore();

	// 現在の時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// 移動量を設定
		pPos += m_move;
	}

	CScene2D::Update();

	// プレイヤーの位置設定
	SetPosition(pPos);

	// エフェクトの生成
	if (m_nType == 0)
	{
		// 通常弾
		CEffect::Create(D3DXVECTOR3(pPos.x - 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);
	}
	else
	{
		// 連射時
		CEffect::Create(D3DXVECTOR3(pPos.x - 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 30.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);
	}
	for (int nCntPriority = 0; nCntPriority < MAX_PRI; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
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

				// 敵とぶつかったら
				if (objType == OBJTYPE_ENEMY)
				{
					if (pPos.y <= pos.y + size.y && pPos.x <= pos.x + size.x && pPos.y >= pos.y - size.y && pPos.x >= pos.x - size.x)
					{
						// サウンド取得
						CSound *pSound = CManager::GetSound();

						// 爆発音再生
						pSound->Play(pSound->SOUND_LABEL_EXPLOSION);
						pSound->SetVolume(pSound->SOUND_LABEL_EXPLOSION, 0.5f);

						// 敵を消し
						pScene->Uninit();

						// 爆発を生成し
						CExplosion::Create(pos, size, CTexture::TEXTURETYPE_EXPLOSION);
						
						// アイテムを生成し
						ItemCreate();

						// 消える
						Uninit();
						return;
					}
				}
			}
		}
	}
	// 寿命を減らす
	m_nLife--;
	if (nTime != 0)
	{
		if (m_nLife == 0)
		{// 寿命がなくなると爆発し消える
			CExplosion::Create(pPos, D3DXVECTOR2(100.0f, 100.0f), CTexture::TEXTURETYPE_EXPLOSION);
			Uninit();
		}
		else if (880.0f < pPos.x)
		{// 画面外に出ると消える
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// アイテムの生成
//=============================================================================
void CBullet::ItemCreate(void)
{
	int m_nRand, nRand2;

	// アイテムの出現率
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
				// テクスチャ数
				fscanf(pFile, "%s", &aFile[0]);
				fscanf(pFile, "%d", &nItemInterval);
			}
			if (strcmp(&aFile[0], "END_SCRIPT") == 0)
			{
				// 終了
				break;
			}
		}
		fclose(pFile);
	}

	// アイテムを出すか
	m_nRand = rand() % nItemInterval;

	if (m_nRand == 0)
	{
		// なんのアイテムを出すか
		nRand2 = rand() % 4;

		// アイテムを出す
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
// 生成処理
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int type, int life, CTexture::TEXTURE_TYPE ntype)
{
	// 弾のインスタンス生成
	CBullet *pBullet = new CBullet;

	// 弾の準備
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