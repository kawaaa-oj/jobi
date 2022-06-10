//=============================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"keyboard.h"
#include"padx.h"
#include"manager.h"
#include"polygon.h"
#include "texture.h"
#include"bg.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CPadX *CManager::m_pPadX = NULL;
CPolygon *CManager::m_pPolygon = NULL;
CTexture *CManager::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, true);
	}

	// キーボードの生成
	m_pKeyboard = new CKeyboard;
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Init(hInstance, hWnd);
	}

	// ゲームパッドの生成
	m_pPadX = new CPadX;
	if (m_pPadX != NULL)
	{
		m_pPadX->Init(hInstance, hWnd);
	}

	// テクスチャクラス生成
	m_pTexture = new CTexture;
	if (m_pTexture != NULL)
	{
		if (m_pTexture != NULL)
		{
			m_pTexture->Init();
		}
	}

	CBg::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CTexture::TEXTURETYPE_BG);

	// ポリゴンの生成
	m_pPolygon = CPolygon::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(40.0f, 40.0f));

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	// ゲームパッドの破棄
	if (m_pPadX != NULL)
	{
		m_pPadX->Uninit();
		delete m_pPadX;
		m_pPadX = NULL;
	}

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Uninit();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	// 全てを破棄する
	CScene::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// キーボードの更新処理(※最初に行う)
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}

	// ゲームパッドの更新処理
	if (m_pPadX != NULL)
	{
		m_pPadX->Update();
	}

	// レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// レンダラーの描画処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// レンダラーの取得
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボード入力の取得
//=============================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
// ゲームパッド入力の取得
//=============================================================================
CPadX * CManager::GetPadX(void)
{
	return m_pPadX;
}

//=============================================================================
// ポリゴンの取得
//=============================================================================
CPolygon * CManager::GetPolygon(void)
{
	return m_pPolygon;
}

//=============================================================================
// テクスチャの取得
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}