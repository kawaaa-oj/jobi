//=============================================================================
//
// ポリゴン表示のクラス [polygon.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include"scene2d.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POLYGONN (2)

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPolygon : public CScene2D
{
public:
	CPolygon(int nPriority = 3);
	~CPolygon();

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void);	// 位置の取得
	D3DXVECTOR2 GetSize(void);	// 大きさの取得

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// バッファ
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR2					m_size;			// 大きさ

	bool						m_bTextureFlag;	// テクスチャが反映されているか
};

#endif // !_POLYGON_H_