//=============================================================================
//
// エフェクトのクラス [effect.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define MAX_EFFECT (10000) //エフェクトの最大数

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority = 2);
	~CEffect();

	static CEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRad, int nLife, float fAlpha, CTexture::TEXTURE_TYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3						m_pos;		// 位置
	D3DXCOLOR						m_col;		// 色
	float							m_fRad;		// 半径
	int								m_nLife;	// 寿命
	float							m_fAlpha;	// アルファ値

};
#endif // !_EFFECT_H_