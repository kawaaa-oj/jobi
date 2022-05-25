//=============================================================================
//
// UI�֘A�\���̃N���X [polygon.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _POLYGON_H_
#define _POLYGON_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_POLYGONN (2)

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CPolygon
{
public:

	typedef enum
	{
		POLYGON_NONE = 0,
		POLYGON_LYFE,
		POLYGON_MAX
	}POLYGONTYPE;
	// �|���S���̎��

	CPolygon();
	~CPolygon();

	static HRESULT Load(void);
	static void Unload(void);
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR2 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPolygon(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture;	// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	// �o�b�t�@

};



#endif // !_POLYGON_H_