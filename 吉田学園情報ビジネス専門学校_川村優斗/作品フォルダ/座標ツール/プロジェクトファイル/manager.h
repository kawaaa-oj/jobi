//=============================================================================
//
// �}�l�[�W���[�̃N���X [manager.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//�C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
//�}�N����`
//*****************************************************************************
#define POLYGON_SIZE_X (100.0f)
#define POLYGON_SIZE_Y (100.0f)

//*****************************************************************************
//�O���錾
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CPadX;
class CPolygon;
class CTexture;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CRenderer		*GetRenderer(void);
	static CKeyboard		*GetKeyboard(void);
	static CPadX			*GetPadX(void);
	static CPolygon			*GetPolygon(void);
	static CTexture			*GetTexture(void);

private:
	// �e��|�C���^
	static CRenderer		*m_pRenderer;
	static CKeyboard		*m_pKeyboard;
	static CPadX			*m_pPadX;
	static CPolygon			*m_pPolygon;
	static CTexture			*m_pTexture;

};

#endif // !_MANAGER_H_