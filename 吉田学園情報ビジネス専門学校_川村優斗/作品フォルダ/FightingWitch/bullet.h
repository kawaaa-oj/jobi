//=============================================================================
//
// 弾のクラス [bullet.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_BULLETTYPE (2) //弾のタイプ数

//*****************************************************************************
// 弾のクラスの定義
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	CBullet(int nPriority = 3);
	~CBullet();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 弾の生成
	static CBullet	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int type, int life, CTexture::TEXTURE_TYPE ntype);

private:
	D3DXVECTOR3					m_move;	//移動量
	int							m_nLife;//寿命
	int							m_nType;//弾のタイプ
};

#endif // !_BULLET_H_
