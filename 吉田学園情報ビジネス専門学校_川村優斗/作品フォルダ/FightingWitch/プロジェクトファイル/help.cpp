//=============================================================================
//
// ヘルプ画面の処理 [help.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"sound.h"
#include "help.h"
#include"padx.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CHelp::CHelp(int nPriority) : CScene2D(nPriority)
{
	m_uiNum = 0;
	m_fade = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CHelp::~CHelp()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CHelp::Init(void)
{
	m_pBg[0] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP1, CTexture::TEXTURETYPE_BGHELP1);
	m_pBg[1] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP2, CTexture::TEXTURETYPE_BGHELP2);
	m_pBg[2] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELP3, CTexture::TEXTURETYPE_BGHELP3);
	m_pBg[3] = CBg::Create(D3DXVECTOR3(0.0f + SCREEN_CENTER_X, 0.0f + SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CBg::BGTYPE_HELPPAD, CTexture::TEXTURETYPE_BGHELPPAD);
	
	CScene2D::Init();

	// サウンドの取得
	CSound *pSound = CManager::GetSound();
	// 音楽の再生
	pSound->Play(pSound->SOUND_LABEL_BGM_HELP);
	pSound->SetVolume(pSound->SOUND_LABEL_BGM_HELP, 0.3f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CHelp::Uninit(void)
{
	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// 音楽の再生
	pSound->Stop(pSound->SOUND_LABEL_BGM_HELP);

	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CHelp::Update(void)
{
	// 移動
	D3DXVECTOR3 pPos = GetPosition();
	D3DXVECTOR2 pSize = GetSize();

	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// ページ進む
	if ((pKeyboard->GetTrigger(DIK_D) == true) || (pKeyboard->GetTrigger(DIK_RIGHT) == true) || (pKeyboard->GetTrigger(DIK_SPACE) == true))
	{
		if (m_uiNum == 0)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 1;
		}
		else if (m_uiNum == 1)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 2;
		}
		else if (m_uiNum == 2)
		{
			// メニューに戻る
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
	}

	// ページ進む(パッド限定)
	if ((pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
	{
		if (m_uiNum == 0)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 3;
		}
		else if (m_uiNum == 3)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 2;
		}
		else if (m_uiNum == 2)
		{
			// メニューに戻る
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
	}

	// ページ戻る
	if ((pKeyboard->GetTrigger(DIK_A) == true) || (pKeyboard->GetTrigger(DIK_LEFT) == true))
	{
		if (m_uiNum == 0)
		{
			// メニューに戻る
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
		else if (m_uiNum == 1)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 0;
		}
		else if (m_uiNum == 2)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 1;
		}
	}

	// ページ戻る(パッド限定)
	if ((pPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true) || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
	{
		if (m_uiNum == 0)
		{
			// メニューに戻る
			if (m_fade == false)
			{
				pSound->Play(pSound->SOUND_LABEL_PAGE);
				pFade->SetFade(CManager::MODE_MENU);
				m_fade = true;
			}
		}
		else if (m_uiNum == 3)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 0;
		}
		else if (m_uiNum == 2)
		{
			pSound->Play(pSound->SOUND_LABEL_PAGE);
			m_uiNum = 3;
		}
	}

	// プレイヤーの位置設定
	SetPosition(pPos);

	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CHelp::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ページ数の取得
//=============================================================================
int CHelp::GetUInum(void)
{
	return m_uiNum;
}

//=============================================================================
// ヘルプ画面の生成
//=============================================================================
CHelp * CHelp::Create(void)
{
	// 画面のインスタンス生成
	CHelp *pHelp = new CHelp;

	// 画面の準備
	if (pHelp != NULL)
	{
		pHelp->Init();
	}
	return pHelp;
}