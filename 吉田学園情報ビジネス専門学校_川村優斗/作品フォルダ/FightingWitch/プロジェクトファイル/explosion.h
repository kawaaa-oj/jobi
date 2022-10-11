//=============================================================================
//
// 爆発のクラス [explosion.h]
// Author : 川村優斗
//
//=============================================================================
// プリプロセッサ
#ifndef _EXPLOTION_H_
#define _EXPLOTION_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// 弾のクラスの定義
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = 3);
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 爆発の生成
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	int	m_nCounterAnim;	// カウンター
	int	m_nPatternAnim;	// パターンナンバー

};


#endif // !_EXPLOTION_H_
