//=============================================================================
//
// 敵弾のクラス [enemybullet.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// 敵弾のクラスの定義
//*****************************************************************************
class CEnemyBullet : public CScene2D
{
public:
	CEnemyBullet();
	~CEnemyBullet();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 敵弾の生成
	static CEnemyBullet	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int life, CTexture::TEXTURE_TYPE type);

private:
	D3DXVECTOR3					m_move;		//移動量
	int							m_nLife;	//寿命

};

#endif // !1
