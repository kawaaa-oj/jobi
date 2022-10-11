//=============================================================================
//
// 2Dシーンのクラス [scene2d.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)// 頂点フォーマット(頂点座標(2d) | 頂点カラー)
#define SCREEN_CENTER_X (SCREEN_WIDTH / 2)							// 画面の真ん中
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)							// 画面の真ん中
#define NUM_VERTEX 4
#define NUM_POLYGON 2
#define TEXTURE_WIDTH 100
#define TEXTURE_HEIGHT 100

//*****************************************************************************
// 構造体の定義
//*****************************************************************************
typedef struct
{

	D3DXVECTOR3	pos;	// 頂点座標
	float		rhw;	// 1.0fで固定
	D3DCOLOR	col;	// 色
	D3DXVECTOR2 tex;	// テクスチャ座標

} VERTEX_2D;

//*****************************************************************************
// 2Dシーンクラスの定義
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

	//ポリゴンの生成
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR2 GetSize(void);

	void SetPosition(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetSize(D3DXVECTOR2 size);
	void SetColor(D3DXCOLOR col);

	void SetVtxTex(int PtnAnim, float fAnimU, D3DXVECTOR2 Tex);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;		// ポリゴンの位置
	D3DXVECTOR3				m_move;		// ポリゴンの位置
	D3DXCOLOR				m_col;		// 色
	D3DXVECTOR2				m_size;		// サイズ

	float					m_FTexU;	// テクスチャ座標(U)
	float					m_FTexV;	// テクスチャ座標(V)

};

#endif // !_SCENE2D_H_