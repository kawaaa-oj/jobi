//=============================================================================
//
// 背景のクラス [bg.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//***********************z******************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 背景のクラスの定義
//*****************************************************************************
class CBg : public CScene2D
{
public:
	typedef enum
	{
		BGTYPE_GAME1 = 0,
		BGTYPE_GAME2,
		BGTYPE_GAME3,
		BGTYPE_HELP1,
		BGTYPE_HELP2,
		BGTYPE_HELP3,
		BGTYPE_HELPPAD,
		BGTYPE_OTHER,
		BGTYPE_MAX
	} BGTYPE;

	CBg(int nPriority = 2);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BgMove(void);

	// 背景の生成
	static CBg	*Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, BGTYPE type, CTexture::TEXTURE_TYPE ntype);

private:
	CManager::MODE				m_mode;					// モード
	BGTYPE						m_nType;				// 背景のタイプ

	D3DXVECTOR3					m_pos;					// 位置
	D3DXCOLOR					m_col;					// 色
	static LPDIRECT3DTEXTURE9	m_apTexture[BGTYPE_MAX];// 共有テクスチャのポインタ

	float						m_fPosV[BGTYPE_MAX];	// テクスチャ座標
	int							m_nPriority;			// 優先順位
	int							m_time;					// 残り時間
	int							m_nHelpNum;				// ヘルプのページ数
};

#endif // !_BG_H_
