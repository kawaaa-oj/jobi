//=============================================================================
//
// メニューの処理 [menu.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _MENU_H_
#define _MENU_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_UI (8)							// UIの最大数
#define UITEXT_X (SCREEN_CENTER_X)			// 文字のX座標
#define UITEXT_WIDTH (300.0f)				// 文字の幅
#define UITEXT_HEIGHT (50.0f)				// 文字の高さ
#define UIINFO_Y (630.0f)					// 説明文のX座標
#define UIINFO_WIDTH (320.0f)				// 説明文の幅
#define UIINFO_HEIGHT (85.0f)				// 説明文の高さ

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScene2D;
class CUI;

//*****************************************************************************
// リザルトのクラス
//*****************************************************************************
class CMenu : public CScene
{
public:
	// 選択肢の列挙
	typedef enum
	{
		SELECT_PLAY = 0,		// 選択（プレイ）
		SELECT_TUTORIAL,		// 選択（チュートリアル）
		SELECT_RANKING,			// 選択（ランキング）
		SELECT_QUIT,			// 選択（戻る）
		SELECT_MAX
	} SELECTTYPE;
	// 選択番号

	CMenu();		// コンストラクタ
	~CMenu();		// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static CMenu *Create(void);

private:
	bool		m_fade;			// フェードイン判定
	static CUI	*m_pUI[6];		// UIのインスタンス
	int			m_nCntSelect;	// どこを選んでるかのやつ

};

#endif // !_RESULT_H_
