//=============================================================================
//
// ���C�t�̃N���X [life.h]
// Author : �쑺�D�l
//
//=============================================================================
// �v���v���Z�b�T
#ifndef _LIFE_H_
#define _LIFE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene.h"
#include"ui.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE (8)

class CUI;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLife : public CScene2D
{
public:
	CLife(int nPriority = 4);
	~CLife();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetLife(int nLife);
	void AddLife(int nValue);
	int GetLife(void);

	// ���C�t�̐���
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int life);

private:
	CUI			*m_apPolygon[MAX_LIFE];	// �|���S���̃C���X�^���X
	D3DXVECTOR2 m_size;					// �T�C�Y
	D3DXVECTOR3 m_pos;					// �ʒu

	int			m_nLife;				// ���C�t��

	bool		m_fade;					// �t�F�[�h����

};
#endif // !_LIFE_H_