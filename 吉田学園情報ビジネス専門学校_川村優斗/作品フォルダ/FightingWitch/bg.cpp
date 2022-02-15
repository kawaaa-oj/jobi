//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "bg.h"
#include"time.h"
#include"game.h"
#include"help.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_apTexture[BGTYPE_MAX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg(int nPriority) : CScene2D(nPriority)
{
	m_time = 10;
	m_nHelpNum = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nPriority = nPriority;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	// モードの取得
	m_mode = CManager::GetMode();

	// ゲームモード以外で暴走しないように
	if (m_mode == CManager::MODE_GAME)
	{
		// 現在の時間を取得
		CTime *pTime = CGame::GetTime();
		m_time = pTime->GetTime();
	}
	if (m_mode == CManager::MODE_HELP)
	{
		CHelp *pHelp = CManager::GetHelp();
		m_nHelpNum = pHelp->GetUInum();
	}

	CScene2D::Update();

	switch (m_nType)
	{
	case BGTYPE_GAME1:
		if (m_time != 0)
		{
			m_fPosV[0] += 0.001f;
			if (m_fPosV[0] >= 0.0f)
			{
				m_fPosV[0] -= 1.0f;
			}
			CScene2D::SetVtxTex(1, m_fPosV[0], 1.0f, 1.0f);
		}
		break;
	case BGTYPE_GAME2:
		if (m_time != 0)
		{
			m_fPosV[1] += 0.002f;
			if (m_fPosV[1] >= 0.0f)
			{
				m_fPosV[1] -= 1.0f;
			}
			CScene2D::SetVtxTex(1, m_fPosV[1], 1.0f, 1.0f);
		}
		break;
	case BGTYPE_GAME3:
		if (m_time != 0)
		{
			m_fPosV[2] += 0.003f;
			if (m_fPosV[2] >= 0.0f)
			{
				m_fPosV[2] -= 1.0f;
			}
			CScene2D::SetVtxTex(1, m_fPosV[2], 1.0f, 1.0f);
		}
		break;
	case BGTYPE_HELP1:
		if (m_mode == CManager::MODE_HELP)
		{
			switch (m_nHelpNum)
			{
			case 0:
				m_col.a = 1.0f;
				SetColor(m_col);
				break;
			case 1:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 2:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 3:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			default:
				break;
			}
		}
		break;
	case BGTYPE_HELP2:
		if (m_mode == CManager::MODE_HELP)
		{
			switch (m_nHelpNum)
			{
			case 0:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 1:
				m_col.a = 1.0f;
				SetColor(m_col);
				break;
			case 2:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 3:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			default:
				break;
			}
		}
		break;
	case BGTYPE_HELP3:
		if (m_mode == CManager::MODE_HELP)
		{
			switch (m_nHelpNum)
			{
			case 0:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 1:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 2:
				m_col.a = 1.0f;
				SetColor(m_col);
				break;
			case 3:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			default:
				break;
			}
			break;
		}
	case BGTYPE_HELPPAD:
		if (m_mode == CManager::MODE_HELP)
		{
			switch (m_nHelpNum)
			{
			case 0:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 1:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 2:
				m_col.a = 0.0f;
				SetColor(m_col);
				break;
			case 3:
				m_col.a = 1.0f;
				SetColor(m_col);
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{
	CScene2D::Draw();
}


//=============================================================================
// 生成処理
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, BGTYPE type, CTexture::TEXTURE_TYPE ntype)
{
	// 背景のインスタンス生成
	CBg *pBg = new CBg;

	// 背景の準備
	if (pBg != NULL)
	{
		pBg->m_nType = type;
		pBg->m_pos = pos;
		pBg->SetPosition(pos);
		pBg->SetSize(size);
		pBg->Init();
		pBg->BindTexture(CManager::GetTexture()->SetTextureType(ntype));
		pBg->SetVtxTex(0, 1.0f, 1.0f, 1.0f);
	}
	return pBg;
}