//=============================================================================
//
// �}�l�[�W���[�̃N���X [manager.h]
// Author : �쑺�D�l
//
//=============================================================================
// �v���v���Z�b�T
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
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
// �O���錾
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CPadX;
class CSound;
class CTitle;
class CGame;
class CGameOver;
class CResult;
class CResult2;
class CFade;
class CMenu;
class CHelp;
class CTexture;

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,	// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_RESULT2,	// ���U���g(���j���[�����������)
		MODE_MENU,		// ���j���[
		MODE_HELP,		// �w���v
		MODE_GAMEOVER,	// �Q�[���I�[�o�[
		MODE_MAX
	}MODE;
	// �e�탂�[�h

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void);

	static CRenderer		*GetRenderer(void);
	static CKeyboard		*GetKeyboard(void);
	static CPadX			*GetPadX(void);
	static CSound			*GetSound(void);
	static CFade			*GetFade(void);
	static CTexture			*GetTexture(void);
	static CHelp			*GetHelp(void);
	static CTitle			*GetTitle(void);
	static CMenu			*GetMenu(void);
	static CGame			*GetGame(void);
	static CGameOver		*GetGameOver(void);
	static CResult			*GetResult(void);
	static CResult2			*GetResult2(void);

private:
	// �e��|�C���^
	static CRenderer		*m_pRenderer;
	static CKeyboard		*m_pKeyboard;
	static CPadX			*m_pPadX;
	static CSound			*m_pSound;
	static CTitle			*m_pTitle;
	static CGame			*m_pGame;
	static CGameOver		*m_pGameOver;
	static CResult			*m_pResult;
	static CResult2			*m_pResult2;
	static CHelp			*m_pHelp;
	static CMenu			*m_pMenu;
	static MODE				m_mode;
	static CFade			*m_pFade;
	static CTexture			*m_pTexture;

};

#endif // !_MANAGER_H_