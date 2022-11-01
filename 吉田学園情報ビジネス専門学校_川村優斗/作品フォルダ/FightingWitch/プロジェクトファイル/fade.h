//=============================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene2D.h"
#include"manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_SPEED (0.05f)	// �t�F�[�h�̐i�s���x

//*****************************************************************************
// �t�F�[�h�̃N���X
//*****************************************************************************
class CFade : public CScene2D
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	}FADE;
	// �t�F�[�h�̏��

	CFade(int nPriority = 7);
	~CFade();

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CManager::MODE mode);

	FADE GetFade(void);
	void SetFade(CManager::MODE mode);

private:
	D3DXCOLOR		m_col;	// �F
	CManager::MODE	m_mode;	// ���[�h���
	FADE			m_fade;	// �t�F�[�h

};

#endif // !_FADE_H_
