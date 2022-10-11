//=============================================================================
//
// ���@�̃N���X [player.h]
// Author : �쑺�D�l
//
//=============================================================================
//�v���v���Z�b�T
#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene2d.h"
#include"texture.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,	// �ʏ� 
		STATE_DAMAGE,	// �_���[�W
		STATE_MUTEKI,	// ���G
		STATE_RENSYA,	// �A��
		STATE_SINISOU,	// ���ɂ���
		STATE_MAX
	} PLAYERSTATE;
	// �v���C���[�̏��

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
	D3DXCOLOR	m_col;			// �F
	D3DXVECTOR3	m_pos;			// �ʒu

	PLAYERSTATE	m_state;		// ���

	int			m_breakCnt;		// ���G����
	int			m_ItembreakCnt;	// ���G����
	int			m_nCntSuper;	// �A�ˎ���
	int			m_BulletBreak;	// �A�ˊԊu

	bool		m_bVibeFlag;	// �U������
	bool		m_bTypeBreak;	// �_���[�W����
	bool		m_bNormal;		// �ʏ픻��
	bool		m_Itembreak;	// ���G����
	bool		m_break;		// ���G����
};

#endif // !_PLAYER_H_
