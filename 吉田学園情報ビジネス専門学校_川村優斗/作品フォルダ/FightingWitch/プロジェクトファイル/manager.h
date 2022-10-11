//=============================================================================
//
// マネージャーのクラス [manager.h]
// Author : 川村優斗
//
//=============================================================================
// プリプロセッサ
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//*****************************************************************************
//マクロ定義
//*****************************************************************************
#define POLYGON_SIZE_X (100.0f)
#define POLYGON_SIZE_Y (100.0f)

//*****************************************************************************
// 前方宣言
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
// クラスの定義
//*****************************************************************************
class CManager
{
public:

	typedef enum
	{
		MODE_TITLE = 0,	// タイトル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_RESULT2,	// リザルト(メニューから入った版)
		MODE_MENU,		// メニュー
		MODE_HELP,		// ヘルプ
		MODE_GAMEOVER,	// ゲームオーバー
		MODE_MAX
	}MODE;
	// 各種モード

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
	// 各種ポインタ
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