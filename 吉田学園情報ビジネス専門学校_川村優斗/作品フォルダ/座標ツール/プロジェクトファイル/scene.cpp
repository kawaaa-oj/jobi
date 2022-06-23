//=============================================================================
//
// �V�[���̏��� [scene.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CScene *CScene::m_apScene[MAX_PRI][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nID = nCntScene;
			m_nNumAll++;
			break;
		}
	}
	m_nPriority = nPriority;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// �S�Ă�j������
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nPriority = 0; nPriority < MAX_PRI; nPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nPriority][nCntScene] != NULL)
			{
				if (nPriority != 7)
				{
					m_apScene[nPriority][nCntScene]->Uninit();
				}
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nPriority = 0; nPriority < MAX_PRI; nPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nPriority][nCntScene] != NULL)
			{
				m_apScene[nPriority][nCntScene]->Update();
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nPriority = 0; nPriority < MAX_PRI; nPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nPriority][nCntScene] != NULL)
			{
				m_apScene[nPriority][nCntScene]->Draw();
			}
		}
	}
}

//=============================================================================
// �V�[���̎擾
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}

//=============================================================================
// ������j��
//=============================================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}