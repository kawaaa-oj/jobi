//=============================================================================
//
// アイテムの処理 [item.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "item.h"
#include"score.h"
#include"game.h"
#include"life.h"
#include"player.h"
#include"sound.h"
#include"time.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CItem::CItem(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(void)
{
	CScene2D::Init();

	// オブジェクトの種類の設定
	switch (m_ItemType)
	{
		// ライフ回復
	case CTexture::TEXTURETYPE_ITEMLIFE:
		SetObjType(CScene::OBJTYPE_ITEM_LIFE);
		break;
		// 無敵
	case CTexture::TEXTURETYPE_ITEMMUTEKI:
		SetObjType(CScene::OBJTYPE_ITEM_MUTEKI);
		break;
		// スコアアップ
	case CTexture::TEXTURETYPE_ITEMSCORE:
		SetObjType(CScene::OBJTYPE_ITEM_SCORE);
		break;
		// 連射
	case CTexture::TEXTURETYPE_ITEMGUN:
		SetObjType(CScene::OBJTYPE_ITEM_SUPER);
		break;
	default:
		break;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	// プレイヤーの情報を取得
	D3DXVECTOR3 pPos = Getposition();
	D3DXVECTOR2 pSize = GetSize();

	// 現在の時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// 移動量を設定
		pPos += m_move;
	}
	// プレイヤーの位置設定
	SetPosition(pPos);

	CScene2D::Update();

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
		{
			// プレイヤーの情報を取得
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				// オブジェクトの種類を取得
				CScene::OBJTYPE objType = pScene->GetObjType();

				// プレイヤーの位置を取得
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->Getposition();

				// プレイヤーの大きさを取得
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// アイテムを取得した際の処理
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
	{// 画面外に出ると消える
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// アイテムを取得した際の処理
//=============================================================================
void CItem::ItemGet(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// プレイヤーの状態を取得
	CPlayer *pPlayer = CGame::GetPlayer();
	CPlayer::PLAYERSTATE state = pPlayer->GetState();

	// 現在のライフを取得
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	// 現在のスコアを取得
	CScore *pScore = CGame::GetScore();

	switch (m_ItemType)
	{
	case CTexture::TEXTURETYPE_ITEMSCORE:
		// アイテム取得サウンド
		pSound->Play(pSound->SOUND_LABEL_SCOREUP);
		pSound->SetVolume(pSound->SOUND_LABEL_SCOREUP, 0.2f);

		// スコア10点アップ
		pScore->AddScore(10);
		break;

	case CTexture::TEXTURETYPE_ITEMLIFE:

		// アイテム取得サウンド
		pSound->Play(pSound->SOUND_LABEL_SCOREUP);
		pSound->SetVolume(pSound->SOUND_LABEL_SCOREUP, 0.2f);

		// 体力が満タンの場合はスコアを加算
		if (nLife == 8)
		{
			pScore->AddScore(10);
		}
		else
		{// 体力回復
			pLife->AddLife(1);
		}
		break;

	case CTexture::TEXTURETYPE_ITEMMUTEKI:
		if (state != CPlayer::STATE_RENSYA && state != CPlayer::STATE_DAMAGE)
		{// 無敵突入
			pPlayer->ChangeState(CPlayer::STATE_MUTEKI);
		}
		break;
	case CTexture::TEXTURETYPE_ITEMGUN:
		if (state != CPlayer::STATE_MUTEKI && state != CPlayer::STATE_DAMAGE)
		{// 連射突入
			pPlayer->ChangeState(CPlayer::STATE_RENSYA);
		}
		break;
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// アイテムのインスタンス生成
	CItem *pItem = new CItem;


	// アイテムの準備
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