//=============================================================================
//
// ���Ԍo�߂̏��� [time.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "time.h"
#include "number.h"
#include"sound.h"
#include"ui.h"
#include"player.h"
#include"game.h"
#include"fade.h"
#include"texture.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority) : CScene(nPriority)
{
	m_bflag = false;
	m_fade = false;

	m_nTime = 0;
	m_nInterval = 0;
	m_dwCurrentTime = 0;

	m_dwExecLastTime = timeGetTime();
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CTime::~CTime()
{
}

//=============================================================================
//����������
//=============================================================================
HRESULT CTime::Init(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime] = CNumber::Create(D3DXVECTOR3(m_pos.x + m_size.x + 50 * nCntTime, m_pos.y, 0.0f), D3DXVECTOR2(m_size.x, m_size.y));
	}
	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Uninit();
			delete m_apNumber[nCntTime];
			m_apNumber[nCntTime] = NULL;
		}
	}
	Release();
}

//=============================================================================
//�X�V����
//=============================================================================
void CTime::Update(void)
{
	m_dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾

	if ((m_dwCurrentTime - m_dwExecLastTime) >= 1000 && m_nTime != 0)
	{
		AddTime(-1);
		m_dwCurrentTime = 0;
		m_dwExecLastTime = timeGetTime();
	}

	m_apNumber[0]->SetNumber(m_nTime % (int)pow(10, 3) / (int)pow(10, 2));
	m_apNumber[1]->SetNumber(m_nTime % (int)pow(10, 2) / (int)pow(10, 1));
	m_apNumber[2]->SetNumber(m_nTime % (int)pow(10, 1));

	if (m_nTime <= 30)
	{
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		m_apNumber[0]->SetColor(m_col);
		m_apNumber[1]->SetColor(m_col);
		m_apNumber[2]->SetColor(m_col);
	}
	if (m_nTime <= 0)
	{
		CFade *pFade = CManager::GetFade();
		CSound *pSound = CManager::GetSound();

		pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);
		pSound->Stop(pSound->SOUND_LABEL_BGM_MUTEKI);

		if (m_bflag == false)
		{
			pSound->Play(pSound->SOUND_LABEL_TIMEUP);
			CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), CTexture::TEXTURETYPE_TIMEUP);
			m_bflag = true;
		}
		m_nInterval++;
		if (m_nInterval == 100)
		{
			if (m_fade == false)
			{
				pFade->SetFade(CManager::MODE_RESULT);
				m_fade = true;
			}
		}
		m_nTime = 0;
	}
}

//=============================================================================
//�`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		m_apNumber[nCntTime]->Draw();
	}
}

//=============================================================================
//���Ԃ̉��Z
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;
}
//=============================================================================
//���Ԃ̎擾
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//=============================================================================
//���Ԃ̐���
//=============================================================================
CTime * CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int time)
{
	CTime *pTime = new CTime;

	if (pTime != NULL)
	{
		pTime->m_nTime = time;
		pTime->m_pos = pos;
		pTime->m_size = size;
		pTime->Init();
	}
	return pTime;
}