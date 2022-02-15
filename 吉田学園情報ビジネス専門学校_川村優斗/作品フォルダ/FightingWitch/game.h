//=============================================================================
//
// ゲーム部分のクラス処理 [game.h]
// Author : 川村優斗
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBg;
class CBullet;
class CLife;
class CEffect;
class CEnemy;
class CEnemyBullet;
class CExplosion;
class CItem;
class CPlayer;
class CRightMenu;
class CScore;
class CTime;

//*****************************************************************************
// ゲームのクラスの定義
//*****************************************************************************
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	static CBg				*GetBg(void);
	static CBullet			*GetBullet(void);
	static CPlayer			*GetPlayer(void);
	static CScore			*GetScore(void);
	static CLife			*GetLife(void);
	static CEffect			*GetEffect(void);
	static CTime			*GetTime(void);
	static CRightMenu		*GetRightmenu(void);
	static CItem			*GetItem(void);
	static CEnemy			*GetEnemy(void);
	static CEnemyBullet		*GetEnemyBullet(void);

private:
	// 各種インスタンス
	static CBg				*m_pBg;
	static CBullet			*m_pBullet;
	static CPlayer			*m_pPlayer;
	static CScore			*m_pScore;
	static CLife			*m_pLife;
	static CEffect			*m_pEffect;
	static CTime			*m_pTime;
	static CRightMenu		*m_pRightmenu;
	static CItem			*m_pItem;
	static CEnemy			*m_pEnemy;
	static CEnemyBullet		*m_pEnemyBullet;
	int						m_nCnt;
	float					m_fPos2;

};


#endif // !_GAME_H_
