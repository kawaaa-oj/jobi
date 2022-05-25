#ifndef _FADE_H_
#define _FADE_H_

#include"scene2D.h"
#include"manager.h"

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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CFade *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CManager::MODE mode);

	FADE GetFade(void);
	void SetFade(CManager::MODE mode);

private:
	D3DXCOLOR		m_col;	// 色
	CManager::MODE	m_mode;	// モード情報
	FADE			m_fade;	// フェード

};

#endif // !_FADE_H_
