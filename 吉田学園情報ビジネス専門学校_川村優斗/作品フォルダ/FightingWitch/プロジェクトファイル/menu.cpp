//=============================================================================
//
// タイトルの処理 [title.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "menu.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"ui.h"
#include"bg.h"
#include"sound.h"
#include"padx.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CUI *CMenu::m_pUI[6] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CMenu::CMenu()
{
	m_fade = false;

	// 初期状態（Startを選んでいる状態）
	m_nCntSelect = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMenu::~CMenu()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMenu::Init(void)
{
	// 背景の生成
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGMENU);

	// UI出す
	m_pUI[0] = CUI::Create(D3DXVECTOR3(UITEXT_X, 150.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_GAMESTART);
	m_pUI[1] = CUI::Create(D3DXVECTOR3(UITEXT_X, 270.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_HELP);
	m_pUI[2] = CUI::Create(D3DXVECTOR3(UITEXT_X, 390.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_RANKING);
	m_pUI[3] = CUI::Create(D3DXVECTOR3(UITEXT_X, 510.0f , 0.0f), D3DXVECTOR2(UITEXT_WIDTH, UITEXT_HEIGHT), CTexture::TEXTURETYPE_TITLE);
	m_pUI[4] = CUI::Create(D3DXVECTOR3(UITEXT_X, UIINFO_Y, 0.0f), D3DXVECTOR2(UIINFO_WIDTH, UIINFO_HEIGHT), CTexture::TEXTURETYPE_MENUTEXT);
	m_pUI[5] = CUI::Create(D3DXVECTOR3(250.0f, 150.0f, 0.0f), D3DXVECTOR2(55.0f, 50.0f), CTexture::TEXTURETYPE_PLAYER);

	// 説明文のテクスチャ調整
	m_pUI[4]->SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// 音楽の再生、音量調整
	pSound->Play(pSound->SOUND_LABEL_BGM_MENU);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_MENU, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMenu::Uninit(void)
{
	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// 音楽の停止
	pSound->Stop(pSound->SOUND_LABEL_BGM_MENU);

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMenu::Update(void)
{
	// フェードの取得
	CFade *pFade = CManager::GetFade();

	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// キーボードの取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// 選択カーソルのテクスチャ調整
	m_pUI[5]->SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

	// UIの色々処理（Startのときにこれを出す、Tutorialのときにこれを出す…）
	switch (m_nCntSelect)
	{
	case SELECT_PLAY:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 150.0f, 0.0f));
		break;
	case SELECT_TUTORIAL:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(1, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 270.0f, 0.0f));
		break;
	case SELECT_RANKING:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[4]->SetVtxTex(2, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 390.0f, 0.0f));
		break;
	case SELECT_QUIT:
		m_pUI[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[2]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
		m_pUI[3]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUI[4]->SetVtxTex(3, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		m_pUI[5]->SetPosition(D3DXVECTOR3(250.0f, 510.0f, 0.0f));
		break;
	default:
		break;
	}

	// メニュー移動（↓）
	if (pKeyboard->GetTrigger(DIK_DOWN) == true || pKeyboard->GetTrigger(DIK_S) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_DOWN) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN) == true)
	{
		// サウンドの再生、音量調整
		pSound->Play(pSound->SOUND_LABEL_SELECT);
		pSound->SetVolume(pSound->SOUND_LABEL_SELECT, 0.5f);

		// メニュー移動
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_RANKING;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_PLAY;
			break;
		}
	}

	// メニュー移動（↑）
	if (pKeyboard->GetTrigger(DIK_UP) == true || pKeyboard->GetTrigger(DIK_W) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_UP) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_UP) == true)
	{
		// サウンドの再生、音量調整
		pSound->Play(pSound->SOUND_LABEL_SELECT);
		pSound->SetVolume(pSound->SOUND_LABEL_SELECT, 0.5f);

		// メニュー移動
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			m_nCntSelect = SELECT_QUIT;
			break;
		case SELECT_TUTORIAL:
			m_nCntSelect = SELECT_PLAY;
			break;
		case SELECT_RANKING:
			m_nCntSelect = SELECT_TUTORIAL;
			break;
		case SELECT_QUIT:
			m_nCntSelect = SELECT_RANKING;
			break;
		}
	}

	// 決定
	if (START_KEY)
	{
		switch (m_nCntSelect)
		{
		case SELECT_PLAY:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_GAME);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_TUTORIAL:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_HELP);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_RANKING:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RESULT2);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		case SELECT_QUIT:
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_TITLE);
				pSound->Play(pSound->SOUND_LABEL_OK);
				m_fade = true;
			}
			break;
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CMenu::Draw(void)
{
}

//=============================================================================
// メニュー画面の生成
//=============================================================================
CMenu * CMenu::Create(void)
{
	// 画面のインスタンス生成
	CMenu *pMenu = new CMenu;

	// 画面の準備
	if (pMenu != NULL)
	{
		pMenu->Init();
	}
	return pMenu;
}