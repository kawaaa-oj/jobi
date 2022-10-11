//=============================================================================
//
// �����̃N���X [explosion.h]
// Author : �쑺�D�l
//
//=============================================================================
// �v���v���Z�b�T
#ifndef _EXPLOTION_H_
#define _EXPLOTION_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"texture.h"

//*****************************************************************************
// �e�̃N���X�̒�`
//*****************************************************************************
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = 3);
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����̐���
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	int	m_nCounterAnim;	// �J�E���^�[
	int	m_nPatternAnim;	// �p�^�[���i���o�[

};


#endif // !_EXPLOTION_H_
