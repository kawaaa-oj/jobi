//=============================================================================
//
// UIの処理 [ui.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "ui.h"
#include"keyboard.h"
#include"manager.h"
#include"fade.h"
#include"player.h"
#include"time.h"
#include"game.h"
#include"sound.h"
#include"padx.h"
#include"life.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

CUI::CUI(int nPriority) : CScene2D(nPriority)
{
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = CTexture::TEXTURETYPE_NAME;
	m_state = CPlayer::STATE_NORMAL;

	m_fPosU = 0.0f;
	m_fPosV = 0.0f;
	m_nLife = 0;

	m_bBrinkFlag = false;
	m_bBrinkFlag2 = false;
	m_fade = false;
	m_bDisplay = false;
	m_bDisplay2 = false;

	m_dwCurrentTime = 0;
	m_dwExecLastTime = timeGetTime();
}

CUI::~CUI()
{
}

HRESULT CUI::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

void CUI::Uninit(void)
{
	CScene2D::Uninit();
}

void CUI::Update(void)
{
	//UIの大きさを設定
	D3DXVECTOR3 pPos = Getposition();

	// UIのサイズを設定
	D3DXVECTOR3 pSize = GetSize();

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//フェードの取得
	CFade *pFade = CManager::GetFade();

	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// モードの取得
	m_mode = CManager::GetMode();

	// ゲームモード以外で暴走しないように
	if (m_mode == CManager::MODE_GAME)
	{
		// 時間切れのときはスコア増えないように
		m_pTime = CGame::GetTime();
		m_pPlayer = CGame::GetPlayer();
		m_state = m_pPlayer->GetState();
		int nTime = m_pTime->GetTime();
	}

	CScene2D::Update();

	// タイプごとに動きを指定
	switch (m_type)
	{
		// タイトルロゴ
	case CTexture::TEXTURETYPE_NAME:
		if (m_bBrinkFlag2 == false)
		{
			m_col.a = 0.0f;
		}
		m_col.a += 0.01f;
		if (START_KEY)
		{
			if (m_bDisplay2 == false)
			{
				pPos.y = STOP_PUSH;
				m_col.a = 0.9f;
				m_bDisplay2 = true;
			}
		}
		m_bBrinkFlag2 = true;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_bDisplay = true;
		}

		//色設定
		SetColor(m_col);

		//徐々に降りてく
		pPos.y += MOVE_PUSH;
		if (pPos.y >= STOP_PUSH)
		{
			//真ん中で止まる
			pPos.y -= MOVE_PUSH;
			if (START_KEY)
			{
				if (m_fade == false)
				{
					if (m_bDisplay == true)
					{
						//ゲーム行き
						pSound->Play(pSound->SOUND_LABEL_OK);
						pFade->SetFade(CManager::MODE_MENU);
						m_fade = true;
					}
				}
			}
		}
		break;
	// PUSH SPACE
	case CTexture::TEXTURETYPE_PUSH:
		//点滅させる
		if (m_bBrinkFlag == false)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				m_col.a = 0.0f;
				m_bBrinkFlag = true;
			}
		}
		else
		{
			m_col.a += 0.01f;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_bBrinkFlag = false;
			}
		}

		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_PLAYER:
		if (m_mode == CManager::MODE_TITLE)
		{
			CScene2D::SetVtxTex(0, 0.25f, 0.25f, 1.0f);

			//上をウロウロさせとく
			pPos.x += MOVE_PICT;

			//端まで行ったらワープ
			if (pPos.x >= 1400.0f)
			{
				pPos.x = -70.0f;
			}
		}
		break;
	
	// 状態表示の処理
	case CTexture::TEXTURETYPE_NORMAL:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_NORMAL)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_DAMAGE:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_DAMAGE)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_SUPER:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_RENSYA)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_MUTEKI:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_MUTEKI)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_SINISOU:
		if (m_mode == CManager::MODE_GAME)
		{
			if (m_state == CPlayer::STATE_SINISOU)
			{
				m_col.a = 1.0f;
			}
			else
			{
				m_col.a = 0.0f;
			}
		}
		SetColor(m_col);
		break;
	case CTexture::TEXTURETYPE_NUMBER:

		break;
	default:
		break;
	}
	//プレイヤーの位置設定
	SetPosition(pPos);

}

//=============================================================================
// 描画処理
//============================================================================
void CUI::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CUI * CUI::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// UIのインスタンス生成
	CUI *pUI = new CUI;

	// UIの準備
	if (pUI != NULL)
	{
		pUI->m_type = type;
		pUI->Init();
		pUI->SetPosition(pos);
		pUI->SetSize(size);
		pUI->BindTexture(CManager::GetTexture()->SetTextureType(type));
	}
	return pUI;
}