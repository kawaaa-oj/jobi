//=============================================================================
//
// �e�̃N���X [bullet.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_BULLETTYPE (2) //�e�̃^�C�v��

//*****************************************************************************
// �e�̃N���X�̒�`
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

	// �e�̐���
	static CBullet	*Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, int type, int life, CTexture::TEXTURE_TYPE ntype);

private:
	D3DXVECTOR3					m_move;	//�ړ���
	int							m_nLife;//����
	int							m_nType;//�e�̃^�C�v
};

#endif // !_BULLET_H_
