//=============================================================================
//
// サウンドクラス [sound.h]
// Author : 川村優斗
//
//=============================================================================
// プリプロセッサ
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "xaudio2.h"//XAudio2関連のヘッダー
#include"manager.h"

//*****************************************************************************
// サウンドクラスの定義
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイルの構造体
	typedef enum
	{
		SOUND_LABEL_BGM_GAME = 0,	// ゲームBGM
		SOUND_LABEL_BGM_HELP,		// ヘルプBGM
		SOUND_LABEL_BGM_MENU,		// メニューBGM
		SOUND_LABEL_BGM_RESULT,		// リザルトBGM
		SOUND_LABEL_BGM_MUTEKI,		// 無敵BGM
		SOUND_LABEL_BGM_TITLE,		// タイトルBGM
		SOUND_LABEL_EXPLOSION,		// 爆発音
		SOUND_LABEL_SHOT,			// ショット音
		SOUND_LABEL_DAMAGE,			// ダメージ音
		SOUND_LABEL_PAGE,			// ページめくり
		SOUND_LABEL_OK,				// 決定音
		SOUND_LABEL_SELECT,			// 選択音
		SOUND_LABEL_TIMEUP,			// タイムアップ音
		SOUND_LABEL_SCOREUP,		// スコアアップ音
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	// 音量設定
	void SetVolume(SOUND_LABEL label, float fVolume)
	{
		m_apSourceVoice[label]->SetVolume(fVolume);
	}

private:
	// パラメータ構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// マスターボイス
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// オーディオデータ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// オーディオデータサイズ

	// 各音素材のパラメータ
	PARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data//sound//gamebgm.wav", -1 },		// ゲームBGM
		{ "data//sound//helpbgm.wav", -1 },		// ヘルプBGM
		{ "data//sound//menubgm.wav", -1 },		// メニューBGM
		{ "data//sound//resultbgm.wav", -1 },	// リザルトBGM
		{ "data//sound//mutekibgm.wav", -1 },	// 無敵BGM
		{ "data//sound//titlebgm.wav", -1 },	// タイトルBGM
		{ "data//sound//explosion.wav", 0 },	// 爆発音
		{ "data//sound//shot.wav", 0 },			// ショット音
		{ "data//sound//damage.wav", 0 },		// ダメージ音
		{ "data//sound//pagenext.wav", 0 },		// ページめくり
		{ "data//sound//ok.wav", 0 },			// 決定音
		{ "data//sound//select.wav", 0 },		// 選択音
		{ "data//sound//timeup.wav", 0 },		// タイムアップ音
		{ "data//sound//scoreup.wav", 0 }		// スコアアップ音
	};

};

#endif // !_SOUND_H_
