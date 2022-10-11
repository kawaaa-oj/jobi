//=============================================================================
//
// 自機のクラス [player.h]
// Author : 川村優斗
//
//=============================================================================
//プリプロセッサ
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include"scene2d.h"
#include"texture.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,	// 通常 
		STATE_DAMAGE,	// ダメージ
		STATE_MUTEKI,	// 無敵
		STATE_RENSYA,	// 連射
		STATE_SINISOU,	// 死にそう
		STATE_MAX
	} PLAYERSTATE;
	// プレイヤーの状態

	CPlayer(int nPriority = 3);
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void PlayerMove(void);

	void ChangeState(PLAYERSTATE state);
	CPlayer::PLAYERSTATE GetState(void);

	D3DXVECTOR3 GetPos(void);

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	D3DXCOLOR	m_col;			// 色
	D3DXVECTOR3	m_pos;			// 位置

	PLAYERSTATE	m_state;		// 状態

	int			m_breakCnt;		// 無敵時間
	int			m_ItembreakCnt;	// 無敵時間
	int			m_nCntSuper;	// 連射時間
	int			m_BulletBreak;	// 連射間隔

	bool		m_bVibeFlag;	// 振動判定
	bool		m_bTypeBreak;	// ダメージ判定
	bool		m_bNormal;		// 通常判定
	bool		m_Itembreak;	// 無敵判定
	bool		m_break;		// 無敵判定
};

#endif // !_PLAYER_H_
