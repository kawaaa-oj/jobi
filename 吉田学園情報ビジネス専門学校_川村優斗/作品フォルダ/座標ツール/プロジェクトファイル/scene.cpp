//=============================================================================
//
// シーンの処理 [scene.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CScene *CScene::m_apScene[MAX_PRI][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全てを破棄する
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
// 更新処理
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
// 描画処理
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
// シーンの取得
//=============================================================================
CScene * CScene::GetScene(int nPriority, int nIdx)
{
	return m_apScene[nPriority][nIdx];
}

//=============================================================================
// 一個だけ破棄
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