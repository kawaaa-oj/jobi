//=============================================================================
//
// レンダラーの処理 [renderer.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"renderer.h"
#include"scene.h"
#include"polygon.h"
#include"padx.h"
#include"keyboard.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_nFont = NULL;
	m_bColorFlag = false;
	m_bDeleteFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = true;										// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行う
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行う
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行う
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行わない
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用

	//透明度の設定をできるようにしている
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定


	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(m_pD3DDevice, 22, 10, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_nFont);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// デバッグ情報表示用フォントの破棄
	if (m_nFont != NULL)
	{
		m_nFont->Release();
		m_nFont = NULL;
	}

	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	CScene::UpdateAll();
}

//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();

		// FPS表示
		DrawFPS();

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}
	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

// アルファブレンディングの加算合成
void CRenderer::AddSynthesis(bool bUse)
{
	if (bUse == true)
	{
		// αブレンディングを加算合成に設定
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}
	else
	{
		// αブレンディングを通常に戻す
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//=============================================================================
// FPS表示
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[300];

	// FPSを取得
	m_nCntFPS = GetFPS();

	// 座標と大きさを格納
	int x = 0.0f;
	int y = 0.0f;
	int z = 0.0f;
	int w = 0.0f;
	int h = 0.0f;

	// ポリゴンの取得
	CPolygon *pPolygon = CManager::GetPolygon();

	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッド取得
	CPadX *pPadX = CManager::GetPadX();

	if (pPolygon != NULL)
	{
		D3DXVECTOR3 pos = pPolygon->GetPos();
		D3DXVECTOR2 size = pPolygon->GetSize();

		// 座標と大きさを格納
		x = pos.x;
		y = pos.y;
		z = pos.z;
		w = size.x;
		h = size.y;

		// パッド接続判定
		bool bConnect = pPadX->ConnectPad();

		// デバッグ表示(パッド接続時とそれ以外で表示を分ける)
		if (bConnect == false)
		{
			wsprintf(str, "FPS:%d\nポリゴンの位置 X:%d,Y:%d,Z:%d\nポリゴンの大きさ 幅:%d,高さ:%d\n[↑↓←→]:移動 [A,D]:幅 [W,S]:高さ\n[Shift]キーを押しながら:微調整\n[P]:txtファイルに保存\n[Enter]:テクスチャON/OFF [Space]:背景ON/OFF\n[X]:大きさ位置リセット\n[左Ctrl]:文字を消す\n[右Ctrl]:文字の色を変える", m_nCntFPS, x, y, z, w, h);
		}
		else
		{
			wsprintf(str, "FPS:%d\nポリゴンの位置 X:%d,Y:%d,Z:%d\nポリゴンの大きさ 幅:%d,高さ:%d\n[左スティック]:移動 [右スティック]:幅、高さ\n[RB]を押しながら:微調整\n[A]:txtファイルに保存\n[B]:テクスチャON/OFF [X]:背景ON/OFF\n[Y]:大きさ位置リセット\n[Back]:文字を消す\n[Start]:文字の色を変える", m_nCntFPS, x, y, z, w, h);
		}
	}

	// 色を変える
	if (pKeyboard->GetTrigger(DIK_RCONTROL) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true)
	{
		switch (m_bColorFlag)
		{
		case false:
			m_bColorFlag = true;
			break;
		case true:
			m_bColorFlag = false;
			break;
		}
	}

	// 文字のオンオフ
	if (pKeyboard->GetTrigger(DIK_LCONTROL) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_BACK) == true)
	{
		switch (m_bDeleteFlag)
		{
		case false:
			m_bDeleteFlag = true;
			break;
		case true:
			m_bDeleteFlag = false;
			break;
		}
	}

	// 左上に来ると邪魔なのでテキストを移動
	if ((x <= 380 + w) && (y <= 200 + h))
	{
		switch (m_bColorFlag)
		{
		case false:
			switch (m_bDeleteFlag)
			{
			case false:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xbf, 0xbf, 0));
				break;
			case true:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		case true:
			switch (m_bDeleteFlag)
			{
			case false:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0, 0, 0xff));
				break;
			case true:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		}
	}
	else
	{
		switch (m_bColorFlag)
		{
		case false:
			switch (m_bDeleteFlag)
			{
			case false:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xbf, 0xbf, 0));
				break;
			case true:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		case true:
			switch (m_bDeleteFlag)
			{
			case false:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0xff));
				break;
			case true:
				// テキスト描画
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		}
	}
}