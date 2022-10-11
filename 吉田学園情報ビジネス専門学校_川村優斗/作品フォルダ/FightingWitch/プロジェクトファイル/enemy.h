//=============================================================================
//
// 敵のクラス [enemy.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include"texture.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define MAX_ENEMY (3)

//*****************************************************************************
// 敵のクラス定義
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	// 敵のタイプ
	typedef enum
	{
		ENEMY_NONE = 0,	
		ENEMY_NORMAL,	// かぼちゃ
		ENEMY_JIGZAG,	// 黒い鳥
		ENEMY_HOMING,	// 赤い鳥
		ENEMY_SUPER,	// 魔女
		ENEMY_PLANE,	// 戦闘機
		ENEMY_MAX
	} ENEMYTYPE;

	CEnemy(int nPriority = 3);
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	ENEMYTYPE GetEnemyType(void);
	void LifeDamage(void);
	void EnemyMove(void);

	// 敵の生成
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, ENEMYTYPE type, CTexture::TEXTURE_TYPE ntype);


protected:


private:
	D3DXVECTOR3	m_move;			// 移動量
	D3DXVECTOR3	m_pos;			// 座標
	D3DXVECTOR3	m_PlayerPos;	// プレイヤーの座標

	ENEMYTYPE	m_type;			// 敵のタイプ

	int			m_nLife;		// 寿命
	int			m_BulletCount;	// 弾発射までのカウンタ
	int			m_nCounterAnim;	// カウンター
	int			m_nPatternAnim;	// パターンナンバー

	bool		m_bFlag;		// ジグザクタイプの敵の上下判定
	bool		m_bDeadFlag;	// 死んだ判定

};
#endif //!_ENEMY_H_