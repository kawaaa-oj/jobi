//=============================================================================
//
// 数字表示のクラス [number.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetColor(D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff; // バッファ
	D3DXCOLOR						m_col;		// 色

};

#endif // !_NUMBER_H_