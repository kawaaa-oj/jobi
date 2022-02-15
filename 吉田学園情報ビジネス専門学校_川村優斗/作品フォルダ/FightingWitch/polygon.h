//=============================================================================
//
// UI関連表示のクラス [polygon.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_POLYGONN (2)

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CPolygon
{
public:

	typedef enum
	{
		POLYGON_NONE = 0,
		POLYGON_LYFE,
		POLYGON_MAX
	}POLYGONTYPE;
	// ポリゴンの種類

	CPolygon();
	~CPolygon();

	static HRESULT Load(void);
	static void Unload(void);
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;	// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// バッファ

};



#endif // !_POLYGON_H_