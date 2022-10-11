//=============================================================================
//
// UIクラスの処理 [UI.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"player.h"
#include"texture.h"
#include"time.h"
#include"life.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCORE (5)		// スコアのケタ数
#define MAX_TIME (3)		// 時間のケタ数
#define LIFE_WIDTH (150.0f)	// ライフバーの幅
#define LIFE_HEIGHT (40.0f)	// ライフバーの高さ
#define LIFE_MAX (260)		// ライフの上限
#define LIFE_DAMAGE (10.0f)	// ライフバーの減る量
#define STOP_PUSH (300.0f)	// PUSHSTARTが止まる位置
#define MOVE_PUSH (2.0f)	// PUSHSTARTの速度
#define MOVE_PICT (5.0f)	// 上の人の移動速度

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;
class CPlayer;

//*****************************************************************************
// UIのクラス
//*****************************************************************************
class CUI : public CScene2D
{
public:
	typedef enum
	{
		UITYPE_PUSH = 0,	// PUSH START 
		UITYPE_NAME,		// タイトルロゴ
		UITYPE_WITCH,		// プレイヤー(タイトル)
		UITYPE_WITCH2,		// プレイヤー(メニュー)
		UITYPE_GAMESTART,	// 	メニューUI
		UITYPE_HELP,		// 	メニューUI
		UITYPE_RANKING,		// 	メニューUI
		UITYPE_TITLE,		// 	メニューUI
		UITYPE_STARTTEXT,	// 	メニューUI
		UITYPE_HELPTEXT,	// 	メニューUI
		UITYPE_RANKINGTEXT,	// 	メニューUI
		UITYPE_TITLETEXT,	// 	メニューUI
		UITYPE_RIGHT,		// 右側のやつ
		UITYPE_NORMAL,		// 状態表示
		UITYPE_DAMAGE,		// 状態表示
		UITYPE_SUPER,		// 状態表示
		UITYPE_MUTEKI,		// 状態表示
		UITYPE_SINISOU,		// 状態表示
		UITYPE_TIMEUP,		// タイムアップ
		UITYPE_LIFE,		// ライフ
		UITYPE_NUMBER,		// ナンバー
		UITYPE_MAX
	} UI_TYPE;

	CUI(int nPriority = 4);	// コンストラクタ
	~CUI();					// デストラクタ

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	// 生成処理
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	D3DXCOLOR					m_col;					// 色
	D3DXVECTOR3					m_size;					// 大きさ
	D3DXVECTOR3					m_pos;					// 位置

	float						m_fPosV;				// テクスチャ座標V
	float						m_fPosU;				// テクスチャ座標U
	int							m_nLife;				// ライフ

	bool						m_bBrinkFlag;			// PUSHSPACEの点滅判定
	bool						m_bBrinkFlag2;			// タイトルの字の薄さ判定				
	bool						m_fade;					// フェード判定
	bool						m_bDisplay;				// タイトル出現判定
	bool						m_bDisplay2;			// タイトル出現判定2

	DWORD						m_dwCurrentTime;		// 経過時間
	DWORD						m_dwExecLastTime;		// 現在の時間

	CManager::MODE				m_mode;					// モード
	CTexture::TEXTURE_TYPE		m_type;					// UIのタイプ
	CPlayer::PLAYERSTATE		m_state;				// プレイヤーの状態

	CPlayer						*m_pPlayer;				// プレイヤーのインスタンス
	CTime						*m_pTime;				// 時間のインスタンス

};

#endif // !_TYTLEUI_H_