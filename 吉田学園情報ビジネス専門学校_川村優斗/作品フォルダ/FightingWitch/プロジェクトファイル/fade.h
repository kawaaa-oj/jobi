//=============================================================================
//
// フェードの処理 [fade.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene2D.h"
#include"manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_SPEED (0.05f)	// フェードの進行速度

//*****************************************************************************
// フェードのクラス
//*****************************************************************************
class CFade : public CScene2D
{
public:

	typedef enum
	{
		FADE_NONE = 0,
		FADE_IN,	// フェードイン
		FADE_OUT,	// フェードアウト
		FADE_MAX
	}FADE;
	// フェードの情報

	CFade(int nPriority = 7);
	~CFade();

	HRESULT Init(void);// 初期化処理
	void Uninit(void); // 終了処理
	void Update(void); // 更新処理
	void Draw(void);   // 描画処理

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CManager::MODE mode);

	FADE GetFade(void);
	void SetFade(CManager::MODE mode);

private:
	D3DXCOLOR		m_col;	// 色
	CManager::MODE	m_mode;	// モード情報
	FADE			m_fade;	// フェード

};

#endif // !_FADE_H_
