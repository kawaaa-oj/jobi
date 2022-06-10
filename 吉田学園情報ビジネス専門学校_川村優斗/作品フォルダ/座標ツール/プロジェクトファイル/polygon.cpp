//=============================================================================
//
// ポリゴンの表示処理 [polygon.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "polygon.h"
#include"manager.h"
#include"keyboard.h"
#include"texture.h"
#include"padx.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CPolygon::CPolygon(int nPriority) : CScene2D(nPriority)
{
	m_bTextureFlag = true;
	m_nAns = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// ポリゴンの生成
//=============================================================================
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ポリゴンのインスタンス生成
	CPolygon *pPolygon = new CPolygon;

	if (pPolygon != NULL)
	{
		pPolygon->m_pos = pos;
		pPolygon->m_size = size;
		pPolygon->Init();
		pPolygon->SetPosition(pos);
		pPolygon->SetSize(size);
		pPolygon->BindTexture(CManager::GetTexture()->SetTextureType(CTexture::TEXTURETYPE_NORMAL));
	}

	return pPolygon;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPolygon::Init(void)
{
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPolygon::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPolygon::Update(void)
{
	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得
	CPadX *pPadX = CManager::GetPadX();

	// シフト押しながらで微調整
	if (pKeyboard->GetPress(DIK_LSHIFT) == true || pKeyboard->GetPress(DIK_RSHIFT) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)
	{
		// 右移動
		if (pKeyboard->GetTrigger(DIK_RIGHT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_pos.x += 1.0f;
		}
		// 左移動
		if (pKeyboard->GetTrigger(DIK_LEFT) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_pos.x -= 1.0f;
		}
		// 下移動
		if (pKeyboard->GetTrigger(DIK_DOWN) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_pos.y += 1.0f;
		}
		// 上移動
		if (pKeyboard->GetTrigger(DIK_UP) == true || pPadX->GetLeftStickTrigger(pPadX->STICK_TYPE_UP) == true)
		{
			m_pos.y -= 1.0f;
		}

		// 高さ拡大
		if (pKeyboard->GetTrigger(DIK_W) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_UP) == true)
		{
			m_size.y += 1.0f;
		}
		// 高さ縮小
		if (pKeyboard->GetTrigger(DIK_S) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_size.y -= 1.0f;
		}
		// 幅拡大
		if (pKeyboard->GetTrigger(DIK_D) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_size.x += 1.0f;
		}
		// 幅縮小
		if (pKeyboard->GetTrigger(DIK_A) == true || pPadX->GetRightStickTrigger(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_size.x -= 1.0f;
		}
	}
	else
	{
		// 右移動
		if (pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_pos.x += 4.0f;
		}
		// 左移動
		if (pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_pos.x -= 4.0f;
		}
		// 下移動
		if (pKeyboard->GetPress(DIK_DOWN) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_pos.y += 4.0f;
		}
		// 上移動
		if (pKeyboard->GetPress(DIK_UP) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_UP) == true)
		{
			m_pos.y -= 4.0f;
		}

		// 高さ拡大
		if (pKeyboard->GetPress(DIK_W) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_UP) == true)
		{
			m_size.y += 2.0f;
		}
		// 高さ縮小
		if (pKeyboard->GetPress(DIK_S) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_DOWN) == true)
		{
			m_size.y -= 2.0f;
		}
		// 幅拡大
		if (pKeyboard->GetPress(DIK_D) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_RIGHT) == true)
		{
			m_size.x += 2.0f;
		}
		// 幅縮小
		if (pKeyboard->GetPress(DIK_A) == true || pPadX->GetRightStick(pPadX->STICK_TYPE_LEFT) == true)
		{
			m_size.x -= 2.0f;
		}
	}

	// 位置高さリセット
	if (pKeyboard->GetRelease(DIK_X) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_Y) == true)
	{
		m_size.x = 40.0f;
		m_size.y = 40.0f;
		m_pos.x = SCREEN_CENTER_X;
		m_pos.y = SCREEN_CENTER_Y;
	}

	// ファイルに書き出し
	if (pKeyboard->GetTrigger(DIK_P) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
	{
		FILE *pFile = fopen("data//text//pos.txt", "w");

		if (pFile != NULL)
		{
			fprintf(pFile, "D3DXVECTOR3(%.1ff, %.1ff, %.1ff), D3DXVECTOR2(%.1ff, %.1ff)", m_pos.x, m_pos.y, m_pos.z, m_size.x, m_size.y);
		}
	}
		// テクスチャ反映/解除
	if (pKeyboard->GetTrigger(DIK_RETURN) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_B) == true)
	{
		if (m_bTextureFlag == true)
		{
			// テクスチャを消す
			DeleteTexture();
			m_bTextureFlag = false;
		}
		else if (m_bTextureFlag == false)
		{
			// テクスチャを割り当て
			BindTexture(CManager::GetTexture()->SetTextureType(CTexture::TEXTURETYPE_NORMAL));
			m_bTextureFlag = true;
		}
	}
		// 位置設定
		SetPosition(m_pos);

		// 大きさ設定
		SetSize(m_size);

		CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CPolygon::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CPolygon::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 大きさの取得
//=============================================================================
D3DXVECTOR2 CPolygon::GetSize(void)
{
	return m_size;
}