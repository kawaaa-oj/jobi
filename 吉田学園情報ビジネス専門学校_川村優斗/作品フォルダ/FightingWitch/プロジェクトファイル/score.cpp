//=============================================================================
//
// スコアの処理 [score.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include "score.h"
#include "number.h"
#include<stdio.h>

//=============================================================================
// コンストラクタ
//=============================================================================
CScore::CScore(int nPriority) : CScene(nPriority)
{
	m_nScore = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum] = CNumber::Create(D3DXVECTOR3(m_pos.x + m_size.x + 50 * nCntNum, m_pos.y, 0.0f), D3DXVECTOR2(m_size.x, m_size.y));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	// セーブ処理
	FILE *pFile;
	pFile = fopen("data//text//newscore.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "%d\n", m_nScore);
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		if (m_apNumber[nCntNum] != NULL)
		{
			m_apNumber[nCntNum]->Uninit();
			delete m_apNumber[nCntNum];
			m_apNumber[nCntNum] = NULL;
		}
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	m_apNumber[0]->SetNumber(m_nScore % (int)pow(10, 5) / (int)pow(10, 4));
	m_apNumber[1]->SetNumber(m_nScore % (int)pow(10, 4) / (int)pow(10, 3));
	m_apNumber[2]->SetNumber(m_nScore % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[3]->SetNumber(m_nScore % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[4]->SetNumber(m_nScore % (int)pow(10, 1));
}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum]->Draw();
	}
}

//=============================================================================
// スコアの設定
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
	for (int nCntNum = 0; nCntNum < MAX_SCORE; nCntNum++)
	{
		m_apNumber[nCntNum]->SetNumber(m_nScore);
	}
}

//=============================================================================
// スコアの加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// スコアの生成
//=============================================================================
CScore * CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// スコアのインスタンス生成
	CScore *pScore = new CScore;

	// スコアの準備
	if (pScore != NULL)
	{
		pScore->m_pos = pos;
		pScore->m_size = size;
		pScore->Init();
	}

	return pScore;
}