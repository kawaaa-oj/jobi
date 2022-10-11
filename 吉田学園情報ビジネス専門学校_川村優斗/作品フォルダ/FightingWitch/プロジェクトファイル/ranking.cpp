//=============================================================================
//
// �����L���O�f�[�^�̏��� [ranking.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "ranking.h"
#include"score.h"
#include"game.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScore *CRanking::m_pScore[MAX_RANKING] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRanking::CRanking(int nPriority) : CScene(nPriority)
{
	m_bFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRanking::~CRanking()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRanking::Init(void)
{
	for (int nCntNum = 0; nCntNum < MAX_RANKING - 1; nCntNum++)
	{
		m_pScore[nCntNum] = CScore::Create(D3DXVECTOR3(m_pos.x, m_pos.y + (100 * nCntNum), 0.0f), m_size);
	}

	// ���[�h����
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
		printf("�t�@�C�����J���܂���ł���\n");
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
			printf("�t�@�C�����J���܂���ł���\n");
		}
		fclose(pFile);
	}

	// �Q�[���I����̏ꍇ�ƃ��j���[����J�����ꍇ�ŏ����𕪂���
	if (m_bFlag == true)
	{
		m_pNowScore = CScore::Create(D3DXVECTOR3(90.0f, SCREEN_HEIGHT / 2, 0.0f), m_size);
		m_pNowScore->SetScore(nNewdata);
		m_nScore[MAX_RANKING - 1] = nNewdata;
	}

	// ���בւ�
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

	// �X�R�A����ׂ�
	for (int nCntRank = 0; nCntRank < MAX_RANKING - 1; nCntRank++)
	{
		m_pScore[nCntRank]->SetScore(m_nScore[nCntRank]);
	}

	// �Z�[�u����
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
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRanking::Uninit(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRanking::Update(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CRanking::Draw(void)
{
}

//=============================================================================
// ��ʂ̃e�N�X�`�����[�h
//=============================================================================
CRanking * CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, bool bFlag)
{
	// �����L���O�̃C���X�^���X����
	CRanking *pRanking = new CRanking;

	// �����L���O�̏���
	if (pRanking != NULL)
	{
		pRanking->m_bFlag = bFlag;
		pRanking->m_pos = pos;
		pRanking->m_size = size;
		pRanking->Init();
	}

	return pRanking;
}