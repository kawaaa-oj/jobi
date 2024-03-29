//=============================================================================
//
// メイン処理 [main.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION (0x0800)	// ビルド時の警告対処用マクロ
#include <windows.h>
#include "d3dx9.h"						// 描画に必要
#include "dinput.h"						// 入力処理に必要
#include "xaudio2.h"					// XAudio関連のヘッダー
#include <stdio.h>
#include <Xinput.h>

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")		// 描画に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// dirctXコンポーネント（部品）使用に必要
#pragma comment(lib,"dinput8.lib")	// 入力処理に必要
#pragma comment(lib,"winmm.lib")	// 入力処理に必要
#pragma comment(lib, "Xinput.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH (1280)	// 画面の幅
#define SCREEN_HEIGHT (720)	// 画面の高さ
#define FPS_COUNT (500)		// FPSを算出する間隔
#define START_KEY (pKeyboard->GetTrigger(DIK_SPACE) == true || pKeyboard->GetTrigger(DIK_RETURN) == true || (pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A)) == true|| (pPadX->GetButtonTrigger(XINPUT_GAMEPAD_START)) == true)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CRenderer;
class CScene;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int GetFPS(void);

#endif