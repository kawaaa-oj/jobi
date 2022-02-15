//=============================================================================
//
// テクスチャのクラス [texture.h]
// Author : 川村優斗
//
//=============================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILENAME_TEX "data//text//texture.txt"

//*****************************************************************************
// テクスチャのクラス
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTURETYPE_PUSH = 0,	// PUSH START
		TEXTURETYPE_NAME,		// タイトルロゴ
		TEXTURETYPE_PLAYER,		// プレイヤー
		TEXTURETYPE_GAMESTART,	// メニューUI
		TEXTURETYPE_HELP,		// メニューUI
		TEXTURETYPE_RANKING,	// メニューUI
		TEXTURETYPE_TITLE,		// メニューUI
		TEXTURETYPE_MENUTEXT,	// メニュー説明文
		TEXTURETYPE_RIGHT,		// 右側のやつ
		TEXTURETYPE_NORMAL,		// 状態表示
		TEXTURETYPE_DAMAGE,		// 状態表示
		TEXTURETYPE_SUPER,		// 状態表示
		TEXTURETYPE_MUTEKI,		// 状態表示
		TEXTURETYPE_SINISOU,	// 状態表示
		TEXTURETYPE_TIMEUP,		// タイムアップ
		TEXTURETYPE_ITEMSCORE,	// スコアアイテム
		TEXTURETYPE_ITEMMUTEKI,	// 無敵アイテム
		TEXTURETYPE_ITEMLIFE,	// ライフアイテム
		TEXTURETYPE_ITEMGUN,	// 連射アイテム
		TEXTURETYPE_EFFECT,		// エフェクト
		TEXTURETYPE_BULLET,		// 弾
		TEXTURETYPE_BULLET2,	// 連射弾
		TEXTURETYPE_ENEMYBULLET,// 敵弾
		TEXTURETYPE_EXPLOSION,	// 爆発
		TEXTURETYPE_ENEMYWITCH,	// 敵魔女
		TEXTURETYPE_ENEMYPLANE,	// 敵戦闘機
		TEXTURETYPE_ENEMYJACK,	// 敵かぼちゃ
		TEXTURETYPE_ENEMYBIRD,	// 敵黒鳥
		TEXTURETYPE_ENEMYBIRD2,	// 敵赤鳥
		TEXTURETYPE_NUMBER,		// 数字
		TEXTURETYPE_BGGAME1,	// ゲーム背景1
		TEXTURETYPE_BGGAME2,	// ゲーム背景2
		TEXTURETYPE_BGGAMEOVER,	// ゲームオーバー背景
		TEXTURETYPE_BGHELP1,	// ヘルプ背景1
		TEXTURETYPE_BGHELP2,	// ヘルプ背景2
		TEXTURETYPE_BGHELP3,	// ヘルプ背景3
		TEXTURETYPE_BGHELPPAD,	// ヘルプ背景パッド版
		TEXTURETYPE_BGMENU,		// メニュー背景
		TEXTURETYPE_BGRESULT1,	// リザルト背景
		TEXTURETYPE_BGRESULT2,	// リザルト背景2
		TEXTURETYPE_BGTITLE,	// タイトル背景
		TEXTURETYPE_LIFE,		// ライフ
		TEXTURETYPE_MAX
	} TEXTURE_TYPE;
	// テクスチャのタイプ

	CTexture();						// コンストラクタ
	~CTexture();					// デストラクタ

	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	static CTexture *Create(void);		// 生成処理
	LPDIRECT3DTEXTURE9 SetTextureType(int nType);				// テクスチャの種類を設定

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURETYPE_MAX];// テクスチャのポインタ
	static int m_nType;										// タイプ
	int m_nNumTexture;										// テクスチャの番号
};

#endif // !_TEXTURE_H_