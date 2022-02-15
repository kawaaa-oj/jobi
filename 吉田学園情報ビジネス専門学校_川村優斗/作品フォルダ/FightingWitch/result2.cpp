//=============================================================================
//
// リザルト画面の処理 [menu.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "result2.h"
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
CRanking *CResult2::m_pRanking = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CResult2::CResult2()
{
	m_fade = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult2::~CResult2()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult2::Init(void)
{
	CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_OTHER, CTexture::TEXTURETYPE_BGRESULT2);

	CNumber::Load();

	// サウンド取得
	CSound *pSound = CManager::GetSound();
	// 音楽の再生
	pSound->Play(pSound->SOUND_LABEL_BGM_RESULT);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_RESULT, 0.35f);

	// ランキングの生成
	m_pRanking = CRanking::Create(D3DXVECTOR3(SCREEN_CENTER_X - 120.0f, 200.0f, 0.0f), D3DXVECTOR2(25.0f, 40.0f), false);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult2::Uninit(void)
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
void CResult2::Update(void)
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
			pFade->SetFade(CManager::MODE_MENU);
			m_fade = true;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult2::Draw(void)
{
}

//=============================================================================
// メニュー画面の生成
//=============================================================================
CResult2 * CResult2::Create(void)
{
	// 画面のインスタンス生成
	CResult2 *pResult = new CResult2;

	// 画面の準備
	if (pResult != NULL)
	{
		pResult->Init();
	}
	return pResult;
}

CRanking * CResult2::GetRanking(void)
{
	return m_pRanking;
}