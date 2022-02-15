//=============================================================================
//
// アイテムのクラス [item.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// アイテムのクラスの定義
//*****************************************************************************
class CItem : public CScene2D
{
public:
	CItem(int nPriority = 4);
	~CItem();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// アイテムの生成
	static CItem	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	D3DXVECTOR3					m_move;		// 移動量
	CTexture::TEXTURE_TYPE		m_ItemType;	// アイテムの種類

};

#endif // !_ITEM_H_
