//=============================================================================
//
// レンダラーのクラス [renderer.h]
// Author : 川村優斗a
//
//=============================================================================
//プリプロセッサ
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// レンダラーのクラスの定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// デバイスの取得
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

	void AddSynthesis(bool bUse);

private:
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)

#ifdef _DEBUG
	LPD3DXFONT				m_nFont = NULL;			// フォントへのポインタ
	int						m_nCntFPS;				// FPSカウンタ
	void					DrawFPS(void);			// FPSの表示
#endif
};

#endif // !_RENDERER_H_
