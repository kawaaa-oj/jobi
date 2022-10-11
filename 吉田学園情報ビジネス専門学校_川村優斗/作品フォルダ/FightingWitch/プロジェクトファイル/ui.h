//=============================================================================
//
// UI�N���X�̏��� [UI.h]
// Author : �쑺�D�l
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"manager.h"
#include"player.h"
#include"texture.h"
#include"time.h"
#include"life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE (5)		// �X�R�A�̃P�^��
#define MAX_TIME (3)		// ���Ԃ̃P�^��
#define LIFE_WIDTH (150.0f)	// ���C�t�o�[�̕�
#define LIFE_HEIGHT (40.0f)	// ���C�t�o�[�̍���
#define LIFE_MAX (260)		// ���C�t�̏��
#define LIFE_DAMAGE (10.0f)	// ���C�t�o�[�̌����
#define STOP_PUSH (300.0f)	// PUSHSTART���~�܂�ʒu
#define MOVE_PUSH (2.0f)	// PUSHSTART�̑��x
#define MOVE_PICT (5.0f)	// ��̐l�̈ړ����x

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;
class CPlayer;

//*****************************************************************************
// UI�̃N���X
//*****************************************************************************
class CUI : public CScene2D
{
public:
	typedef enum
	{
		UITYPE_PUSH = 0,	// PUSH START 
		UITYPE_NAME,		// �^�C�g�����S
		UITYPE_WITCH,		// �v���C���[(�^�C�g��)
		UITYPE_WITCH2,		// �v���C���[(���j���[)
		UITYPE_GAMESTART,	// 	���j���[UI
		UITYPE_HELP,		// 	���j���[UI
		UITYPE_RANKING,		// 	���j���[UI
		UITYPE_TITLE,		// 	���j���[UI
		UITYPE_STARTTEXT,	// 	���j���[UI
		UITYPE_HELPTEXT,	// 	���j���[UI
		UITYPE_RANKINGTEXT,	// 	���j���[UI
		UITYPE_TITLETEXT,	// 	���j���[UI
		UITYPE_RIGHT,		// �E���̂��
		UITYPE_NORMAL,		// ��ԕ\��
		UITYPE_DAMAGE,		// ��ԕ\��
		UITYPE_SUPER,		// ��ԕ\��
		UITYPE_MUTEKI,		// ��ԕ\��
		UITYPE_SINISOU,		// ��ԕ\��
		UITYPE_TIMEUP,		// �^�C���A�b�v
		UITYPE_LIFE,		// ���C�t
		UITYPE_NUMBER,		// �i���o�[
		UITYPE_MAX
	} UI_TYPE;

	CUI(int nPriority = 4);	// �R���X�g���N�^
	~CUI();					// �f�X�g���N�^

	HRESULT Init(void);// ����������
	void Uninit(void); // �I������
	void Update(void); // �X�V����
	void Draw(void);   // �`�揈��

	// ��������
	static CUI *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type);

private:
	D3DXCOLOR					m_col;					// �F
	D3DXVECTOR3					m_size;					// �傫��
	D3DXVECTOR3					m_pos;					// �ʒu

	float						m_fPosV;				// �e�N�X�`�����WV
	float						m_fPosU;				// �e�N�X�`�����WU
	int							m_nLife;				// ���C�t

	bool						m_bBrinkFlag;			// PUSHSPACE�̓_�Ŕ���
	bool						m_bBrinkFlag2;			// �^�C�g���̎��̔�������				
	bool						m_fade;					// �t�F�[�h����
	bool						m_bDisplay;				// �^�C�g���o������
	bool						m_bDisplay2;			// �^�C�g���o������2

	DWORD						m_dwCurrentTime;		// �o�ߎ���
	DWORD						m_dwExecLastTime;		// ���݂̎���

	CManager::MODE				m_mode;					// ���[�h
	CTexture::TEXTURE_TYPE		m_type;					// UI�̃^�C�v
	CPlayer::PLAYERSTATE		m_state;				// �v���C���[�̏��

	CPlayer						*m_pPlayer;				// �v���C���[�̃C���X�^���X
	CTime						*m_pTime;				// ���Ԃ̃C���X�^���X

};

#endif // !_TYTLEUI_H_