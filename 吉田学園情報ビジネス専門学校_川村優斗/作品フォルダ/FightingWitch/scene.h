//=============================================================================
//
// �V�[���̃N���X [scene.h]
// Author : �쑺�D�l
//
//=============================================================================

//�v���v���Z�b�T
#ifndef _SCENE_H_
#define _SCENE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCENE (512)
#define MAX_PRI (10)

//*****************************************************************************
// �V�[���N���X�̒�`
//*****************************************************************************
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,	// �v���C���[
		OBJTYPE_ENEMY,		// �G
		OBJTYPE_BULLET,		// �e
		OBJTYPE_ENEMYBULLET,// �G�e
		OBJTYPE_ITEM_SCORE,	// �X�R�A�A�C�e��
		OBJTYPE_ITEM_MUTEKI,// ���G�A�C�e�� 
		OBJTYPE_ITEM_LIFE,	// ���C�t��
		OBJTYPE_ITEM_SUPER,	// �A�˃A�C�e��
		OBJTYPE_MAX
	}OBJTYPE;
	// �I�u�W�F�N�g�̎��

	CScene(int nPriority = 3);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Update(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriority, int nIdx);

protected:
	void Release(void);

private:
	static CScene	*m_apScene[MAX_PRI][MAX_SCENE];	//�I�u�W�F�N�g�̔z��
	static int		m_nNumAll;						//�I�u�W�F�N�g�̐�
	OBJTYPE			m_objType;						//�I�u�W�F�N�g�̎��
	int				m_nID;							//�i�[��̔ԍ�
	int				m_nPriority;					//�D�揇�ʂ̔ԍ�

};

#endif // !_SCENE_H_
