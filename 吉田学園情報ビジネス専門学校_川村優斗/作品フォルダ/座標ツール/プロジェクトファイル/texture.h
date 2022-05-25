//=============================================================================
//
// �e�N�X�`���̃N���X [texture.h]
// Author : �쑺�D�l
//
//=============================================================================

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILENAME_TEX "text//texture.txt"

//*****************************************************************************
// �e�N�X�`���̃N���X
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTURETYPE_NORMAL = 0,	// PUSH START
		TEXTURETYPE_MAX
	} TEXTURE_TYPE;
	// �e�N�X�`���̃^�C�v

	CTexture();						// �R���X�g���N�^
	~CTexture();					// �f�X�g���N�^

	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CTexture *Create(void);		// ��������
	LPDIRECT3DTEXTURE9 SetTextureType(int nType);				// �e�N�X�`���̎�ނ�ݒ�

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURETYPE_MAX];// �e�N�X�`���̃|�C���^
	static int m_nType;										// �^�C�v
	int m_nNumTexture;										// �e�N�X�`���̔ԍ�
};

#endif // !_TEXTURE_H_