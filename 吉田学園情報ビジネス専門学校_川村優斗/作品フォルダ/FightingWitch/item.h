//=============================================================================
//
// �A�C�e���̃N���X [item.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// �A�C�e���̃N���X�̒�`
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

	// �A�C�e���̐���
	static CItem	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	D3DXVECTOR3					m_move;		// �ړ���
	CTexture::TEXTURE_TYPE		m_ItemType;	// �A�C�e���̎��

};

#endif // !_ITEM_H_
