//=============================================================================
//
// �G�t�F�N�g�̃N���X [effect.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define MAX_EFFECT (10000) //�G�t�F�N�g�̍ő吔

//*****************************************************************************
//�N���X��`
//*****************************************************************************
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority = 2);
	~CEffect();

	static CEffect *Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRad, int nLife, float fAlpha, CTexture::TEXTURE_TYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3						m_pos;		// �ʒu
	D3DXCOLOR						m_col;		// �F
	float							m_fRad;		// ���a
	int								m_nLife;	// ����
	float							m_fAlpha;	// �A���t�@�l

};
#endif // !_EFFECT_H_