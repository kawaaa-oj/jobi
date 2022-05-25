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
#define FILENAME_TEX "data//text//texture.txt"

//*****************************************************************************
// �e�N�X�`���̃N���X
//*****************************************************************************
class CTexture
{
public:

	typedef enum
	{
		TEXTURETYPE_PUSH = 0,	// PUSH START
		TEXTURETYPE_NAME,		// �^�C�g�����S
		TEXTURETYPE_PLAYER,		// �v���C���[
		TEXTURETYPE_GAMESTART,	// ���j���[UI
		TEXTURETYPE_HELP,		// ���j���[UI
		TEXTURETYPE_RANKING,	// ���j���[UI
		TEXTURETYPE_TITLE,		// ���j���[UI
		TEXTURETYPE_MENUTEXT,	// ���j���[������
		TEXTURETYPE_RIGHT,		// �E���̂��
		TEXTURETYPE_NORMAL,		// ��ԕ\��
		TEXTURETYPE_DAMAGE,		// ��ԕ\��
		TEXTURETYPE_SUPER,		// ��ԕ\��
		TEXTURETYPE_MUTEKI,		// ��ԕ\��
		TEXTURETYPE_SINISOU,	// ��ԕ\��
		TEXTURETYPE_TIMEUP,		// �^�C���A�b�v
		TEXTURETYPE_ITEMSCORE,	// �X�R�A�A�C�e��
		TEXTURETYPE_ITEMMUTEKI,	// ���G�A�C�e��
		TEXTURETYPE_ITEMLIFE,	// ���C�t�A�C�e��
		TEXTURETYPE_ITEMGUN,	// �A�˃A�C�e��
		TEXTURETYPE_EFFECT,		// �G�t�F�N�g
		TEXTURETYPE_BULLET,		// �e
		TEXTURETYPE_BULLET2,	// �A�˒e
		TEXTURETYPE_ENEMYBULLET,// �G�e
		TEXTURETYPE_EXPLOSION,	// ����
		TEXTURETYPE_ENEMYWITCH,	// �G����
		TEXTURETYPE_ENEMYPLANE,	// �G�퓬�@
		TEXTURETYPE_ENEMYJACK,	// �G���ڂ���
		TEXTURETYPE_ENEMYBIRD,	// �G����
		TEXTURETYPE_ENEMYBIRD2,	// �G�Ԓ�
		TEXTURETYPE_NUMBER,		// ����
		TEXTURETYPE_BGGAME1,	// �Q�[���w�i1
		TEXTURETYPE_BGGAME2,	// �Q�[���w�i2
		TEXTURETYPE_BGGAMEOVER,	// �Q�[���I�[�o�[�w�i
		TEXTURETYPE_BGHELP1,	// �w���v�w�i1
		TEXTURETYPE_BGHELP2,	// �w���v�w�i2
		TEXTURETYPE_BGHELP3,	// �w���v�w�i3
		TEXTURETYPE_BGHELPPAD,	// �w���v�w�i�p�b�h��
		TEXTURETYPE_BGMENU,		// ���j���[�w�i
		TEXTURETYPE_BGRESULT1,	// ���U���g�w�i
		TEXTURETYPE_BGRESULT2,	// ���U���g�w�i2
		TEXTURETYPE_BGTITLE,	// �^�C�g���w�i
		TEXTURETYPE_LIFE,		// ���C�t
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