//=============================================================================
//
// 2D�V�[���̃N���X [scene2d.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)// ���_�t�H�[�}�b�g(���_���W(2d) | ���_�J���[)
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)							// ��ʂ̐^��
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)							// ��ʂ̐^��
#define NUM_VERTEX 4
#define NUM_POLYGON 2
#define TEXTURE_WIDTH 100
#define TEXTURE_HEIGHT 100

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{

	D3DXVECTOR3	pos;	// ���_���W
	float		rhw;	// 1.0f�ŌŒ�
	D3DCOLOR	col;	// �F
	D3DXVECTOR2 tex;	// �e�N�X�`�����W

} VERTEX_2D;

//*****************************************************************************
// 2D�V�[���N���X�̒�`
//*****************************************************************************
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);
	~CScene2D();

	HRESULT CScene2D::Init(void);
	void Uninit(void);
	void Draw(void);
	void Update(void);

	//�|���S���̐���
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR2 GetSize(void);

	void SetPosition(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetSize(D3DXVECTOR2 size);
	void SetColor(D3DXCOLOR col);

	void SetVtxTex(int PtnAnim, float fAnimU, D3DXVECTOR2 Tex);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR3				m_pos;		// �|���S���̈ʒu
	D3DXVECTOR3				m_move;		// �|���S���̈ʒu
	D3DXCOLOR				m_col;		// �F
	D3DXVECTOR2				m_size;		// �T�C�Y

	float					m_FTexU;	// �e�N�X�`�����W(U)
	float					m_FTexV;	// �e�N�X�`�����W(V)

};

#endif // !_SCENE2D_H_