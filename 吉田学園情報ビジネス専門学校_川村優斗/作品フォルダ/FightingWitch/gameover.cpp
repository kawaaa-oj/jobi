//=============================================================================
//
// リザルト画面の処理 [menu.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "gameover.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"bg.h"
#include"sound.h"
#include"ranking.h"
#include"number.h"
#include"padx.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRanking *CGameOver::m_pRanking = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CGameOver::CGameOver()
{
	m_fade = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CGameOver::~CGameOver()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameOver::Init(void)
{
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGGAMEOVER);

	CNumber::Load();

	// サウンド取得
	CSound *pSound = CManager::GetSound();
	// 音楽の再生
	pSound->Play(pSound->SOUND_LABEL_BGM_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_RESULT, 0.15f);

	// ランキングの生成
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, 200.0f, 0.0f), D3DXVECTOR2(25.0f, 40.0f), true);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGameOver::Uninit(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();
	pSound->Stop(pSound->SOUND_LABEL_BGM_RESULT);

	CNumber::Unload();

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameOver::Update(void)
{
	// キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) == true || (pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A)) == true)
	{
		if (m_fade == false)
		{
			pSound->Play(pSound->SOUND_LABEL_OK);
			pFade->SetFade(CManager::MODE_TITLE);
			m_fade = true;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameOver::Draw(void)
{
}

//=============================================================================
// メニュー画面の生成
//=============================================================================
CGameOver * CGameOver::Create(void)
{
	// 画面のインスタンス生成
	CGameOver *pGameOver = new CGameOver;

	// 画面の準備
	if (pGameOver != NULL)
	{
		pGameOver->Init();
	}
	return pGameOver;
}

CRanking * CGameOver::GetRanking(void)
{
	return m_pRanking;
}