//=============================================================================
//
// ランキングデータの処理 [ranking.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "ranking.h"
#include"score.h"
#include"game.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CScore *CRanking::m_pScore[MAX_RANKING] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	m_bFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	for (int nCntNum = 0; nCntNum < MAX_RANKING - 1; nCntNum++)
	{
		m_pScore[nCntNum] = CScore::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (100 * nCntNum), 0.0f), m_size);
	}

	// ロード処理
	FILE *pFile;

	pFile = fopen("data//text//score.txt", "r");
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRank]);
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	int nNewdata;
	if (m_bFlag == true)
	{
		pFile = fopen("data//text//newscore.txt", "r");
		if (pFile != NULL)
		{
			fscanf(pFile, "%d", &nNewdata);
		}
		else
		{
			printf("ファイルが開けませんでした\n");
		}
		fclose(pFile);
	}

	// ゲーム終了後の場合とメニューから開いた場合で処理を分ける
	if (m_bFlag == true)
	{
		m_pNowScore = CScore::Create(D3DXVECTOR3(90.0f, SCREEN_HEIGHT / 2, 0.0f), m_size);
		m_pNowScore->SetScore(nNewdata);
		m_nScore[MAX_RANKING - 1] = nNewdata;
	}

	// 並べ替え
	for (int nCntRank = 0; nCntRank < MAX_RANKING - 1; nCntRank++)
	{
		for (int nCntRank2 = 0; nCntRank2 < MAX_RANKING - 1; nCntRank2++)
		{
			if (m_nScore[nCntRank2] < m_nScore[nCntRank2 + 1])
			{
				int nScore = m_nScore[nCntRank2];
				m_nScore[nCntRank2] = m_nScore[nCntRank2 + 1];
				m_nScore[nCntRank2 + 1] = nScore;
			}
		}
	}

	// スコアを並べる
	for (int nCntRank = 0; nCntRank < MAX_RANKING - 1; nCntRank++)
	{
		m_pScore[nCntRank]->SetScore(m_nScore[nCntRank]);
	}

	// セーブ処理
	pFile = fopen("data//text//score.txt", "w");
	if (pFile != NULL)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANKING; nCntRank++)
		{
			fprintf(pFile, "%d\n", m_nScore[nCntRank]);
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// 画面のテクスチャロード
//=============================================================================
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, bool bFlag)
{
	// ランキングのインスタンス生成
	CRanking *pRanking = new CRanking;

	// ランキングの準備
	if (pRanking != NULL)
	{
		pRanking->m_bFlag = bFlag;
		pRanking->m_pos = pos;
		pRanking->m_size = size;
		pRanking->Init();
	}

	return pRanking;
}