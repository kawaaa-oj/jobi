//=============================================================================
//
// �����\���̃N���X [number.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
	void SetColor(D3DXCOLOR col);

private:
	static LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff; // �o�b�t�@
	D3DXCOLOR						m_col;		// �F

};

#endif // !_NUMBER_H_