//=============================================================================
//
// 敵弾の処理 [enemybullet.cpp]
// Author : 川村優斗
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
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyBullet::CEnemyBullet()
{
	// オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_ENEMYBULLET);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyBullet::~CEnemyBullet()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyBullet::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyBullet::Update(void)
{
	// プレイヤーの移動
	D3DXVECTOR3 pPos = Getposition();

	// 現在の時間を取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	if (nTime != 0)
	{
		// 移動量を設定
		pPos += m_move;
	}

	CScene2D::Update();

	//プレイヤーの位置設定
	SetPosition(pPos);

	// プレイヤーの状態を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	// エフェクトの生成
	CEffect::Create(D3DXVECTOR3(pPos.x + 30.0f, pPos.y, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 20.0f, 5, 0.1f, CTexture::TEXTURETYPE_EFFECT);

	// 寿命を減らす
	m_nLife--;

	if (nTime != 0)
	{
		if (m_nLife == 0)
		{// 寿命がなくなると爆発し消える
			CExplosion::Create(pPos, D3DXVECTOR2(100.0f, 100.0f), CTexture::TEXTURETYPE_EXPLOSION);
			Uninit();
		}
		else if (-100.0f > pPos.x)
		{// 画面外に出ると消える
			Uninit();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyBullet::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CEnemyBullet * CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int life, CTexture::TEXTURE_TYPE type)
{
	// 弾のインスタンス生成
	CEnemyBullet *pBullet = new CEnemyBullet;

	// 弾の準備
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