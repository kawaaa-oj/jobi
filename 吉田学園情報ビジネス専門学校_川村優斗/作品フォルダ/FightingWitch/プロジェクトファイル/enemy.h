//=============================================================================
//
// �G�̃N���X [enemy.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include"texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define MAX_ENEMY (3)

//*****************************************************************************
// �G�̃N���X��`
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	// �G�̃^�C�v
	typedef enum
	{
		ENEMY_NONE = 0,	
		ENEMY_NORMAL,	// ���ڂ���
		ENEMY_JIGZAG,	// ������
		ENEMY_HOMING,	// �Ԃ���
		ENEMY_SUPER,	// ����
		ENEMY_PLANE,	// �퓬�@
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

	// �G�̐���
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size, ENEMYTYPE type, CTexture::TEXTURE_TYPE ntype);


protected:


private:
	D3DXVECTOR3	m_move;			// �ړ���
	D3DXVECTOR3	m_pos;			// ���W
	D3DXVECTOR3	m_PlayerPos;	// �v���C���[�̍��W

	ENEMYTYPE	m_type;			// �G�̃^�C�v

	int			m_nLife;		// ����
	int			m_BulletCount;	// �e���˂܂ł̃J�E���^
	int			m_nCounterAnim;	// �J�E���^�[
	int			m_nPatternAnim;	// �p�^�[���i���o�[

	bool		m_bFlag;		// �W�O�U�N�^�C�v�̓G�̏㉺����
	bool		m_bDeadFlag;	// ���񂾔���

};
#endif //!_ENEMY_H_