//=============================================================================
//
// ライフのクラス [life.h]
// Author : 川村優斗
//
//=============================================================================
// プリプロセッサ
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"
#include"ui.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE (8)

class CUI;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLife : public CScene2D
{
public:
	CLife(int nPriority = 4);
	~CLife();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLife(int nLife);
	void AddLife(int nValue);
	int GetLife(void);

	// ライフの生成
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int life);

private:
	CUI			*m_apPolygon[MAX_LIFE];	// ポリゴンのインスタンス
	D3DXVECTOR2 m_size;					// サイズ
	D3DXVECTOR3 m_pos;					// 位置

	int			m_nLife;				// ライフ数

	bool		m_fade;					// フェード判定

};
#endif // !_LIFE_H_