//=============================================================================
//
// �����_���[�̃N���X [renderer.h]
// Author : �쑺�D�la
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �����_���[�̃N���X�̒�`
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

	void AddSynthesis(bool bUse);

private:
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)

#ifdef _DEBUG
	LPD3DXFONT				m_nFont = NULL;			// �t�H���g�ւ̃|�C���^
	int						m_nCntFPS;				// FPS�J�E���^
	void					DrawFPS(void);			// FPS�̕\��
#endif
};

#endif // !_RENDERER_H_
