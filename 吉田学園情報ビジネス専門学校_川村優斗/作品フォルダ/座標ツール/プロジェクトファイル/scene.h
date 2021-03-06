//=============================================================================
//
// シーンのクラス [scene.h]
// Author : 川村優斗
//
//=============================================================================

//プリプロセッサ
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SCENE (512)
#define MAX_PRI (10)

//*****************************************************************************
// シーンクラスの定義
//*****************************************************************************
class CScene
{
public:
	CScene(int nPriority = 3);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Update(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static CScene *GetScene(int nPriority, int nIdx);

protected:
	void Release(void);

private:
	static CScene	*m_apScene[MAX_PRI][MAX_SCENE];	// オブジェクトの配列
	static int		m_nNumAll;						// オブジェクトの数
	int				m_nID;							// 格納先の番号
	int				m_nPriority;					// 優先順位の番号

};

#endif // !_SCENE_H_