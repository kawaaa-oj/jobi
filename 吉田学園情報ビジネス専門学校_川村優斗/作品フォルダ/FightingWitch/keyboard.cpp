//=============================================================================
//
// キーボードの入力処理 [keyboard.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"keyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	// キー情報のクリア
	memset(&m_aKeyStatePress[0], 0, sizeof(m_aKeyStatePress));
	memset(&m_aKeyStateTrigger[0], 0, sizeof(m_aKeyStateTrigger));	// トリガー
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	// 入力情報保存用
	BYTE aKeyState[NUM_KEY_MAX];

	// 入力デバイスからデータ取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStatePress[nCntKey] = aKeyState[nCntKey];//キーボードの入力情報保存
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// プレス情報
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeyStatePress[nKey] & 0x80) ? true : false;
	//条件　? 真の場合 : 偽の場合;
}

//=============================================================================
// トリガー情報
//=============================================================================
bool CInputKeyboard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
	//条件　? 真の場合 : 偽の場合;
}

//=============================================================================
// リリース情報
//=============================================================================
bool CInputKeyboard::GetKeyboardRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
	//条件　? 真の場合 : 偽の場合;
}