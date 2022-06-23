//=============================================================================
//
// マネージャーのクラス [manager.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*****************************************************************************
//インクルードファイル
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
//前方宣言
//*****************************************************************************
class CRenderer;
class CKeyboard;
class CPadX;
class CPolygon;
class CTexture;

//*****************************************************************************
// クラスの定義
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
	// 各種ポインタ
	static CRenderer		*m_pRenderer;
	static CKeyboard		*m_pKeyboard;
	static CPadX			*m_pPadX;
	static CPolygon			*m_pPolygon;
	static CTexture			*m_pTexture;

};

#endif // !_MANAGER_H_