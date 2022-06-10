//=============================================================================
//
// �w�i�̃N���X [bg.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _BG_H_
#define _BG_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//***********************z******************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �w�i�̃N���X�̒�`
//*****************************************************************************
class CBg : public CScene2D
{
public:
	CBg(int nPriority = 2);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �w�i�̐���
	static CBg	*Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE ntype);

private:
	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXCOLOR					m_col;					// �F
	CTexture::TEXTURE_TYPE		m_type;					// ���
	int							m_nPriority;			// �D�揇��
	int							m_time;					// �c�莞��
	int							m_nHelpNum;				// �w���v�̃y�[�W��

	bool m_bTextureFlag;

};

#endif // !_BG_H_