//=============================================================================
//
// �|���S���\���̃N���X [polygon.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include"scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_POLYGONN (2)

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPolygon : public CScene2D
{
public:
	CPolygon(int nPriority = 3);
	~CPolygon();

	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void);	// �ʒu�̎擾
	D3DXVECTOR2 GetSize(void);	// �傫���̎擾

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// �o�b�t�@
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR2					m_size;			// �傫��

	bool						m_bTextureFlag;	// �e�N�X�`�������f����Ă��邩
};

#endif // !_POLYGON_H_