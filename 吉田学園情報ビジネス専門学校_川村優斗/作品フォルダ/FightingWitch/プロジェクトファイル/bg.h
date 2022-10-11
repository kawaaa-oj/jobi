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
	typedef enum
	{
		BGTYPE_GAME1 = 0,
		BGTYPE_GAME2,
		BGTYPE_GAME3,
		BGTYPE_HELP1,
		BGTYPE_HELP2,
		BGTYPE_HELP3,
		BGTYPE_HELPPAD,
		BGTYPE_OTHER,
		BGTYPE_MAX
	} BGTYPE;

	CBg(int nPriority = 2);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BgMove(void);

	// �w�i�̐���
	static CBg	*Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, BGTYPE type, CTexture::TEXTURE_TYPE ntype);

private:
	CManager::MODE				m_mode;					// ���[�h
	BGTYPE						m_nType;				// �w�i�̃^�C�v

	D3DXVECTOR3					m_pos;					// �ʒu
	D3DXCOLOR					m_col;					// �F
	static LPDIRECT3DTEXTURE9	m_apTexture[BGTYPE_MAX];// ���L�e�N�X�`���̃|�C���^

	float						m_fPosV[BGTYPE_MAX];	// �e�N�X�`�����W
	int							m_nPriority;			// �D�揇��
	int							m_time;					// �c�莞��
	int							m_nHelpNum;				// �w���v�̃y�[�W��
};

#endif // !_BG_H_
