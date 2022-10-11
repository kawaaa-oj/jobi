//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"player.h"
#include"keyboard.h"
#include"manager.h"
#include"bullet.h"
#include"sound.h"
#include"effect.h"
#include"score.h"
#include"enemy.h"
#include"enemybullet.h"
#include"life.h"
#include"game.h"
#include"item.h"
#include"ui.h"
#include"time.h"
#include"padx.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	// �I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	m_break = false;
	m_Itembreak = true;
	m_bTypeBreak = false;
	m_bNormal = false;
	m_bVibeFlag = false;

	m_nCntSuper = 0;
	m_ItembreakCnt = 0;
	m_BulletBreak = 0;
	m_breakCnt = 0;

	m_col = D3DXCOLOR(255, 255, 255, 255);

	m_state = STATE_NORMAL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �v���C���[�̐���
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// �v���C���[�̃C���X�^���X����
	CPlayer *pPlayer = new CPlayer;

	// �v���C���[�̏���
	if (pPlayer != NULL)
	{
		pPlayer->m_pos = pos;
		pPlayer->Init();
		pPlayer->SetSize(size);
		pPlayer->SetPosition(pos);
		pPlayer->BindTexture(CManager::GetTexture()->SetTextureType(type));
		pPlayer->SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
	}
	return pPlayer;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();

	// �X�e�[�^�X�̐���
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_NORMAL);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_SUPER);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_DAMAGE);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_MUTEKI);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_SINISOU);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �T�E���h�̎擾
	CSound *pSound = CManager::GetSound();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();

	// �v���C���[�̈ړ�
	m_pos = GetPosition();
	D3DXVECTOR2 pSize = GetSize();

	// �F�̐ݒ�
	SetColor(m_col);

	// ���Ԃ̎擾
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	// ���C�t�̎擾
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	if (nTime != 0)
	{
		// �v���C���[�̈ړ�
		PlayerMove();

		// �A�ˏ�Ԃ̏���
		if (m_state == STATE_RENSYA)
		{
			m_col = D3DXCOLOR(255, 255, 255, 255);
			
			// �F����ۂ�
			CScene2D::SetVtxTex(1, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

			// BGM�~�߂�
			pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

			if (m_bNormal == false)
			{
				pSound->Play(pSound->SOUND_LABEL_BGM_MUTEKI);
				m_bTypeBreak = true;
				pSound->SetVolume(pSound->SOUND_LABEL_BGM_MUTEKI, 0.3f);
				m_bNormal = true;
			}

			// �A�ˎ��ԉ��Z
			m_nCntSuper++;

			// �A�ˁI
			if (pKeyboard->GetPress(DIK_SPACE) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_A) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)	//�e����
			{
				m_BulletBreak++;

				// �e�̘A�ˊԊu
				if (m_BulletBreak == 5)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, 0.0f), D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 40.0f), 1, 60, CTexture::TEXTURETYPE_BULLET2);
					m_BulletBreak = 0;
				}
			}
			if ((m_nCntSuper >= 300) && (m_nCntSuper % 5 == 0))
			{// �F�Ɩ��G���Ԃ�߂�
				CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			}
			else if ((m_nCntSuper >= 300) && (m_nCntSuper % 5 != 0))
			{// ���G���Ԍx��
				CScene2D::SetVtxTex(1, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			}

			// �ʏ��Ԃɖ߂�
			if (m_nCntSuper == 400)
			{
				pSound->Stop(pSound->SOUND_LABEL_BGM_MUTEKI);
				pSound->Play(pSound->SOUND_LABEL_BGM_GAME);
				
				if (nLife <= 1)
				{
					m_state = STATE_SINISOU;
				}
				else
				{
					m_state = STATE_NORMAL;
				}
				CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
				m_nCntSuper = 0;
				m_bNormal = false;

			}
		}
		else
		{
			// ���ʂ̂Ƃ��͕��ʂ̒e��
			if (pKeyboard->GetTrigger(DIK_SPACE) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
			{
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, 0.0f), D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 10.0f), 0, 60, CTexture::TEXTURETYPE_BULLET);
			}
		}
	}

	// ���G��Ԃ̏���
	if (m_state == STATE_MUTEKI)
	{
		// �F��߂�
		m_col = D3DXCOLOR(255, 255, 255, 255);
		pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

		if (m_bNormal == false)
		{
			pSound->Play(pSound->SOUND_LABEL_BGM_MUTEKI);
			m_bTypeBreak = true;
			pSound->SetVolume(pSound->SOUND_LABEL_BGM_MUTEKI, 0.3f);
			m_bNormal = true;
		}
		// ���G�J�E���^�𑝂₵
		if (nTime != 0)
		{
			m_ItembreakCnt++;
		}
		// �F�𔼓�����
		CScene2D::SetVtxTex(2, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		// ���G���ԏI��
		if ((m_ItembreakCnt >= 350) && (m_ItembreakCnt % 5 == 0))
		{// �F�Ɩ��G���Ԃ�߂�
			CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		}
		else if ((m_ItembreakCnt >= 350) && (m_ItembreakCnt % 5 != 0))
		{// ���G���Ԍx��
			CScene2D::SetVtxTex(2, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		}
		// �A�C�e�����G���ԏI��
		if (m_ItembreakCnt >= 500)
		{// �F�Ɩ��G���Ԃ�߂�
			CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			m_ItembreakCnt = 0;
			pSound->Stop(pSound->SOUND_LABEL_BGM_MUTEKI);
			pSound->Play(pSound->SOUND_LABEL_BGM_GAME);

			if (nLife <= 1)
			{
				m_state = STATE_SINISOU;
			}
			else
			{
				m_state = STATE_NORMAL;
			}
			m_bNormal = false;
		}
	}
	// �_���[�W���G���Ԓ�
	if (m_state == STATE_DAMAGE)
	{
		pSound->Stop(pSound->SOUND_LABEL_BGM_MUTEKI);

		if (m_bVibeFlag == false)
		{
			pPadX->SetVibe(30000, 30000, 50);
			m_bVibeFlag = true;
		}

		if (m_bTypeBreak == true)
		{
			pSound->Play(pSound->SOUND_LABEL_BGM_GAME);
			m_bTypeBreak = false;
		}
		// ���G�J�E���^�𑝂₵
		if (nTime != 0)
		{
			m_breakCnt++;
		}
		CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

		// �F�𔼓�����
		m_col.a = 0.5f;
		if (m_breakCnt % 3 == 1)
		{
			m_col.a = 1.0f;
		}
		// ���G���ԏI��
		if (m_breakCnt == 100)
		{// �F�Ɩ��G���Ԃ�߂�
			m_break = false;
			m_col = D3DXCOLOR(255, 255, 255, 255);
			CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			if (nLife <= 1)
			{
				m_state = STATE_SINISOU;
				m_bVibeFlag = false;
			}
			else
			{
				m_state = STATE_NORMAL;
				m_bVibeFlag = false;
			}
			m_breakCnt = 0;
			m_bNormal = false;
		}
	}

	// ��ʂ���͂ݏo�Ȃ����߂̏���
	if (m_pos.x - pSize.x <= 0)
	{
		m_pos.x = 0 + pSize.x;
	}
	if (m_pos.x + pSize.x >= 850.0f)
	{
		m_pos.x = 850.0f - pSize.x;
	}
	if (m_pos.y - pSize.y <= 0)
	{
		m_pos.y = 0 + pSize.y;
	}
	if (m_pos.y + pSize.y >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - pSize.y;
	}
	// �v���C���[�̈ʒu�ݒ�
	SetPosition(m_pos);

	CScene2D::Update();

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
		{
			// �G�̏����擾
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				// �I�u�W�F�N�g�̎�ނ��擾
				CScene::OBJTYPE objType = pScene->GetObjType();

				// �G�̈ʒu���擾
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->GetPosition();

				// �G�̑傫�����擾
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// ���݂̃��C�t���擾
				CLife *pLife = CGame::GetLife();

				// ���݂̃��C�t���擾
				CScore *pScore = CGame::GetScore();

				// �G�̏�Ԃ��擾
				CEnemy *pEnemy = CGame::GetEnemy();

				// �G�ƂԂ�������
				if (objType == OBJTYPE_ENEMY)
				{
					if (m_pos.y <= pos.y + size.y && m_pos.x <= pos.x + size.x && m_pos.y >= pos.y - size.y && m_pos.x >= pos.x - size.x)
					{
						// ���G���ԓ˓�
						m_nCntSuper = 0;
						if (m_state != STATE_DAMAGE)
						{
							if (m_state != STATE_MUTEKI)
							{
								m_state = STATE_DAMAGE;

								// �T�E���h�Đ���
								pSound->Play(pSound->SOUND_LABEL_DAMAGE);
								pSound->SetVolume(pSound->SOUND_LABEL_DAMAGE, 0.25f);
								
								// ���C�t��������
								pLife->AddLife(-1);
							}
						}
					}
				}
				// �G�e�ƂԂ�������
				else if (objType == OBJTYPE_ENEMYBULLET)
				{
					if (m_pos.y <= pos.y + 30.0f && m_pos.x <= pos.x + 30.0f && m_pos.y >= pos.y - 30.0f && m_pos.x >= pos.x - 30.0f)
					{
						// ���G���ԓ˓�
						if (m_state != STATE_DAMAGE)
						{
							if (m_state != STATE_MUTEKI)
							{
								m_state = STATE_DAMAGE;

								// �T�E���h�Đ���
								pSound->Play(pSound->SOUND_LABEL_DAMAGE);
								pSound->SetVolume(pSound->SOUND_LABEL_DAMAGE, 0.25f);
								// ���C�t��������
								pLife->AddLife(-1);
							}
						}
					}
				}
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

void CPlayer::PlayerMove(void)
{
	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�̎擾
	CPadX *pPadX = CManager::GetPadX();

	// ���ړ�
	if (pKeyboard->GetPress(DIK_S) == true || pKeyboard->GetPress(DIK_DOWN) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_DOWN) || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN)) == true)		//���ړ�
	{	// �E��
		if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.75f) * 20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * 15.0f;
		}
		// ����
		else if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.25f) * -20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * 15.0f;
		}
		else
		{
			m_pos.y += 15.0f;
		}
	}

	// ��ړ�
	else if (pKeyboard->GetPress(DIK_W) == true || pKeyboard->GetPress(DIK_UP) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_UP) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_UP)) == true)	//��ړ�
	{	// �E��
		if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.75f) * 20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * -15.0f;
		}
		// ����
		else if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.75f) * -20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * -15.0f;
		}
		else
		{
			m_pos.y -= 15.0f;
		}
	}
	// �E�ړ�
	else if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)	//�E�ړ�
	{
		m_pos.x += 20.0f;
	}
	// ���ړ�
	else if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT)) == true)	//���ړ�
	{
		m_pos.x -= 20.0f;
	}
}

//=============================================================================
// ��ԕω�
//=============================================================================
void CPlayer::ChangeState(PLAYERSTATE state)
{
	m_state = state;
}

//=============================================================================
// ��Ԃ̎擾
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return m_state;
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
