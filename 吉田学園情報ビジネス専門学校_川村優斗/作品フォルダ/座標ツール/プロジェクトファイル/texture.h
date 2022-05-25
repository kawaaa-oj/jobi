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
#define FILENAME_TEX "text//texture.txt"

//*****************************************************************************
// テクスチャのクラス
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTURETYPE_NORMAL = 0,	// PUSH START
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