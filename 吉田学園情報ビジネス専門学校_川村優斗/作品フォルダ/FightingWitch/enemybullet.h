//=============================================================================
//
// �G�e�̃N���X [enemybullet.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// �G�e�̃N���X�̒�`
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

	// �G�e�̐���
	static CEnemyBullet	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int life, CTexture::TEXTURE_TYPE type);

private:
	D3DXVECTOR3					m_move;		//�ړ���
	int							m_nLife;	//����

};

#endif // !1
