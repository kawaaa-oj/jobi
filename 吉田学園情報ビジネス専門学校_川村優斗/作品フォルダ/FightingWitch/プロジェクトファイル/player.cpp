//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 川村優斗
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
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
// 静的メンバ変数
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene2D(nPriority)
{
	// オブジェクトタイプの設定
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
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// プレイヤーの生成
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CTexture::TEXTURE_TYPE type)
{
	// プレイヤーのインスタンス生成
	CPlayer *pPlayer = new CPlayer;

	// プレイヤーの準備
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
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	CScene2D::Init();

	// ステータスの生成
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_NORMAL);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_SUPER);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_DAMAGE);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_MUTEKI);
	CUI::Create(D3DXVECTOR3(SCREEN_CENTER_X + 450.0f, SCREEN_CENTER_Y + 80.0f, 0.0f), D3DXVECTOR2(200.0f, SCREEN_HEIGHT / 6), CTexture::TEXTURETYPE_SINISOU);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// サウンドの取得
	CSound *pSound = CManager::GetSound();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// プレイヤーの移動
	m_pos = GetPosition();
	D3DXVECTOR2 pSize = GetSize();

	// 色の設定
	SetColor(m_col);

	// 時間の取得
	CTime *pTime = CGame::GetTime();
	int nTime = pTime->GetTime();

	// ライフの取得
	CLife *pLife = CGame::GetLife();
	int nLife = pLife->GetLife();

	if (nTime != 0)
	{
		// プレイヤーの移動
		PlayerMove();

		// 連射状態の処理
		if (m_state == STATE_RENSYA)
		{
			m_col = D3DXCOLOR(255, 255, 255, 255);
			
			// 色を青っぽく
			CScene2D::SetVtxTex(1, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

			// BGM止める
			pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

			if (m_bNormal == false)
			{
				pSound->Play(pSound->SOUND_LABEL_BGM_MUTEKI);
				m_bTypeBreak = true;
				pSound->SetVolume(pSound->SOUND_LABEL_BGM_MUTEKI, 0.3f);
				m_bNormal = true;
			}

			// 連射時間加算
			m_nCntSuper++;

			// 連射！
			if (pKeyboard->GetPress(DIK_SPACE) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_A) == true || pPadX->GetButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER) == true)	//弾発射
			{
				m_BulletBreak++;

				// 弾の連射間隔
				if (m_BulletBreak == 5)
				{
					CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, 0.0f), D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 40.0f), 1, 60, CTexture::TEXTURETYPE_BULLET2);
					m_BulletBreak = 0;
				}
			}
			if ((m_nCntSuper >= 300) && (m_nCntSuper % 5 == 0))
			{// 色と無敵時間を戻す
				CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			}
			else if ((m_nCntSuper >= 300) && (m_nCntSuper % 5 != 0))
			{// 無敵時間警告
				CScene2D::SetVtxTex(1, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
			}

			// 通常状態に戻る
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
			// 普通のときは普通の弾を
			if (pKeyboard->GetTrigger(DIK_SPACE) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_A) == true)
			{
				CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, 0.0f), D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 10.0f), 0, 60, CTexture::TEXTURETYPE_BULLET);
			}
		}
	}

	// 無敵状態の処理
	if (m_state == STATE_MUTEKI)
	{
		// 色を戻す
		m_col = D3DXCOLOR(255, 255, 255, 255);
		pSound->Stop(pSound->SOUND_LABEL_BGM_GAME);

		if (m_bNormal == false)
		{
			pSound->Play(pSound->SOUND_LABEL_BGM_MUTEKI);
			m_bTypeBreak = true;
			pSound->SetVolume(pSound->SOUND_LABEL_BGM_MUTEKI, 0.3f);
			m_bNormal = true;
		}
		// 無敵カウンタを増やし
		if (nTime != 0)
		{
			m_ItembreakCnt++;
		}
		// 色を半透明に
		CScene2D::SetVtxTex(2, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		// 無敵時間終了
		if ((m_ItembreakCnt >= 350) && (m_ItembreakCnt % 5 == 0))
		{// 色と無敵時間を戻す
			CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		}
		else if ((m_ItembreakCnt >= 350) && (m_ItembreakCnt % 5 != 0))
		{// 無敵時間警告
			CScene2D::SetVtxTex(2, 0.25f, D3DXVECTOR2(0.25f, 1.0f));
		}
		// アイテム無敵時間終了
		if (m_ItembreakCnt >= 500)
		{// 色と無敵時間を戻す
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
	// ダメージ無敵時間中
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
		// 無敵カウンタを増やし
		if (nTime != 0)
		{
			m_breakCnt++;
		}
		CScene2D::SetVtxTex(0, 0.25f, D3DXVECTOR2(0.25f, 1.0f));

		// 色を半透明に
		m_col.a = 0.5f;
		if (m_breakCnt % 3 == 1)
		{
			m_col.a = 1.0f;
		}
		// 無敵時間終了
		if (m_breakCnt == 100)
		{// 色と無敵時間を戻す
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

	// 画面からはみ出ないための処理
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
	// プレイヤーの位置設定
	SetPosition(m_pos);

	CScene2D::Update();

	for (int nCntPriority = 0; nCntPriority < 10; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < 512; nCntScene++)
		{
			// 敵の情報を取得
			CScene *pScene = CScene::GetScene(nCntPriority, nCntScene);
			if (pScene != NULL)
			{
				// オブジェクトの種類を取得
				CScene::OBJTYPE objType = pScene->GetObjType();

				// 敵の位置を取得
				D3DXVECTOR3 pos = ((CScene2D*)pScene)->GetPosition();

				// 敵の大きさを取得
				D3DXVECTOR2 size = ((CScene2D*)pScene)->GetSize();

				// 現在のライフを取得
				CLife *pLife = CGame::GetLife();

				// 現在のライフを取得
				CScore *pScore = CGame::GetScore();

				// 敵の状態を取得
				CEnemy *pEnemy = CGame::GetEnemy();

				// 敵とぶつかったら
				if (objType == OBJTYPE_ENEMY)
				{
					if (m_pos.y <= pos.y + size.y && m_pos.x <= pos.x + size.x && m_pos.y >= pos.y - size.y && m_pos.x >= pos.x - size.x)
					{
						// 無敵時間突入
						m_nCntSuper = 0;
						if (m_state != STATE_DAMAGE)
						{
							if (m_state != STATE_MUTEKI)
							{
								m_state = STATE_DAMAGE;

								// サウンド再生し
								pSound->Play(pSound->SOUND_LABEL_DAMAGE);
								pSound->SetVolume(pSound->SOUND_LABEL_DAMAGE, 0.25f);
								
								// ライフをいじり
								pLife->AddLife(-1);
							}
						}
					}
				}
				// 敵弾とぶつかったら
				else if (objType == OBJTYPE_ENEMYBULLET)
				{
					if (m_pos.y <= pos.y + 30.0f && m_pos.x <= pos.x + 30.0f && m_pos.y >= pos.y - 30.0f && m_pos.x >= pos.x - 30.0f)
					{
						// 無敵時間突入
						if (m_state != STATE_DAMAGE)
						{
							if (m_state != STATE_MUTEKI)
							{
								m_state = STATE_DAMAGE;

								// サウンド再生し
								pSound->Play(pSound->SOUND_LABEL_DAMAGE);
								pSound->SetVolume(pSound->SOUND_LABEL_DAMAGE, 0.25f);
								// ライフをいじり
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
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

void CPlayer::PlayerMove(void)
{
	// キーボード取得
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// ゲームパッドの取得
	CPadX *pPadX = CManager::GetPadX();

	// 下移動
	if (pKeyboard->GetPress(DIK_S) == true || pKeyboard->GetPress(DIK_DOWN) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_DOWN) || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_DOWN)) == true)		//下移動
	{	// 右下
		if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.75f) * 20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * 15.0f;
		}
		// 左下
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

	// 上移動
	else if (pKeyboard->GetPress(DIK_W) == true || pKeyboard->GetPress(DIK_UP) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_UP) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_UP)) == true)	//上移動
	{	// 右上
		if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)
		{
			m_pos.x += sinf(D3DX_PI * 0.75f) * 20.0f;
			m_pos.y += cosf(D3DX_PI * 0.25f) * -15.0f;
		}
		// 左上
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
	// 右移動
	else if (pKeyboard->GetPress(DIK_D) == true || pKeyboard->GetPress(DIK_RIGHT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_RIGHT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT)) == true)	//右移動
	{
		m_pos.x += 20.0f;
	}
	// 左移動
	else if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_LEFT) == true || pPadX->GetLeftStick(pPadX->STICK_TYPE_LEFT) == true || (pPadX->GetButtonPress(XINPUT_GAMEPAD_DPAD_LEFT)) == true)	//左移動
	{
		m_pos.x -= 20.0f;
	}
}

//=============================================================================
// 状態変化
//=============================================================================
void CPlayer::ChangeState(PLAYERSTATE state)
{
	m_state = state;
}

//=============================================================================
// 状態の取得
//=============================================================================
CPlayer::PLAYERSTATE CPlayer::GetState(void)
{
	return m_state;
}

//=============================================================================
// 座標の取得
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}
