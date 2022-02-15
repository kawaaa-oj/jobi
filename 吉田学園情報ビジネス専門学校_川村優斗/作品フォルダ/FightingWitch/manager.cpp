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
#include"sound.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include "texture.h"
#include"result2.h"
#include"gameover.h"
#include"fade.h"
#include"help.h"
#include"menu.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CPadX *CManager::m_pPadX = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CGameOver *CManager::m_pGameOver = NULL;
CResult *CManager::m_pResult = NULL;
CResult2 *CManager::m_pResult2 = NULL;
CMenu *CManager::m_pMenu = NULL;
CHelp *CManager::m_pHelp = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_GAME;
CFade *CManager::m_pFade = NULL;
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
	m_pInputKeyboard = new CInputKeyboard;
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Init(hInstance, hWnd);
	}

	// ゲームパッドの生成
	m_pPadX = new CPadX;
	if (m_pPadX != NULL)
	{
		m_pPadX->Init(hInstance, hWnd);
	}

	// サウンドの生成
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
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

	// フェードの生成
	m_pFade = CFade::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT), MODE_TITLE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
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

	// サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
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
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
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
// モードを設定する
//=============================================================================
void CManager::SetMode(MODE mode)
{
	// まずは各モードを破棄
	switch (m_mode)
	{
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	case MODE_RESULT2:
		if (m_pResult2 != NULL)
		{
			m_pResult2->Uninit();
			m_pResult2 = NULL;
		}
		break;
	case MODE_HELP:
		if (m_pHelp != NULL)
		{
			m_pHelp->Uninit();
			m_pHelp = NULL;
		}
		break;
	case MODE_MENU:
		if (m_pMenu != NULL)
		{
			m_pMenu->Uninit();
			m_pMenu = NULL;
		}
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pGameOver->Uninit();
			m_pGameOver = NULL;
		}
		break;
	}

	CScene::ReleaseAll();

	// 各種モードの準備
	switch (mode)
	{
	case MODE_TITLE:
		m_pTitle = CTitle::Create();
		break;
	case MODE_GAME:
		m_pGame = CGame::Create();
		break;
	case MODE_RESULT:
		m_pResult = CResult::Create();
		break;
	case MODE_RESULT2:
		m_pResult2 = CResult2::Create();
		break;
	case MODE_MENU:
		m_pMenu = CMenu::Create();
		break;
	case MODE_HELP:
		m_pHelp = CHelp::Create();
	
		break;
	case MODE_GAMEOVER:
		m_pGameOver = CGameOver::Create();
		break;

	}
	m_mode = mode;
}

//=============================================================================
// モードの取得
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
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
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// ゲームパッド入力の取得
//=============================================================================
CPadX * CManager::GetPadX(void)
{
	return m_pPadX;
}

//=============================================================================
// サウンドの取得
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// フェードの取得
//=============================================================================
CFade * CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// テクスチャの取得
//=============================================================================
CTexture *CManager::GetTexture(void)
{
	return m_pTexture;
}

//=============================================================================
// ヘルプの取得
//=============================================================================
CHelp * CManager::GetHelp(void)
{
	return m_pHelp;
}

//=============================================================================
// タイトルの取得
//=============================================================================
CTitle * CManager::GetTitle(void)
{
	return m_pTitle;
}

//=============================================================================
// メニューの取得
//=============================================================================
CMenu * CManager::GetMenu(void)
{
	return m_pMenu;
}

//=============================================================================
// ゲーム画面の取得
//=============================================================================
CGame * CManager::GetGame(void)
{
	return m_pGame;
}

//=============================================================================
// ゲームオーバーの取得
//=============================================================================
CGameOver * CManager::GetGameOver(void)
{
	return m_pGameOver;
}

//=============================================================================
// リザルトの取得
//=============================================================================
CResult * CManager::GetResult(void)
{
	return m_pResult;
}

//=============================================================================
// リザルトの取得
//=============================================================================
CResult2 * CManager::GetResult2(void)
{
	return m_pResult2;
}
