//=============================================================================
//
// �T�E���h�N���X [sound.h]
// Author : �쑺�D�l
//
//=============================================================================
// �v���v���Z�b�T
#ifndef _SOUND_H_
#define _SOUND_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "xaudio2.h"//XAudio2�֘A�̃w�b�_�[
#include"manager.h"

//*****************************************************************************
// �T�E���h�N���X�̒�`
//*****************************************************************************
class CSound
{
public:
	CSound();
	~CSound();

	// �T�E���h�t�@�C���̍\����
	typedef enum
	{
		SOUND_LABEL_BGM_GAME = 0,	// �Q�[��BGM
		SOUND_LABEL_BGM_HELP,		// �w���vBGM
		SOUND_LABEL_BGM_MENU,		// ���j���[BGM
		SOUND_LABEL_BGM_RESULT,		// ���U���gBGM
		SOUND_LABEL_BGM_MUTEKI,		// ���GBGM
		SOUND_LABEL_BGM_TITLE,		// �^�C�g��BGM
		SOUND_LABEL_EXPLOSION,		// ������
		SOUND_LABEL_SHOT,			// �V���b�g��
		SOUND_LABEL_DAMAGE,			// �_���[�W��
		SOUND_LABEL_PAGE,			// �y�[�W�߂���
		SOUND_LABEL_OK,				// ���艹
		SOUND_LABEL_SELECT,			// �I����
		SOUND_LABEL_TIMEUP,			// �^�C���A�b�v��
		SOUND_LABEL_SCOREUP,		// �X�R�A�A�b�v��
		SOUND_LABEL_MAX
	}SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	// ���ʐݒ�
	void SetVolume(SOUND_LABEL label, float fVolume)
	{
		m_apSourceVoice[label]->SetVolume(fVolume);
	}

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *filename;		// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	}PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2				*m_pXAudio2 = NULL;						// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};	// �I�[�f�B�I�f�[�^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};		// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	PARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data//sound//gamebgm.wav", -1 },		// �Q�[��BGM
		{ "data//sound//helpbgm.wav", -1 },		// �w���vBGM
		{ "data//sound//menubgm.wav", -1 },		// ���j���[BGM
		{ "data//sound//resultbgm.wav", -1 },	// ���U���gBGM
		{ "data//sound//mutekibgm.wav", -1 },	// ���GBGM
		{ "data//sound//titlebgm.wav", -1 },	// �^�C�g��BGM
		{ "data//sound//explosion.wav", 0 },	// ������
		{ "data//sound//shot.wav", 0 },			// �V���b�g��
		{ "data//sound//damage.wav", 0 },		// �_���[�W��
		{ "data//sound//pagenext.wav", 0 },		// �y�[�W�߂���
		{ "data//sound//ok.wav", 0 },			// ���艹
		{ "data//sound//select.wav", 0 },		// �I����
		{ "data//sound//timeup.wav", 0 },		// �^�C���A�b�v��
		{ "data//sound//scoreup.wav", 0 }		// �X�R�A�A�b�v��
	};

};

#endif // !_SOUND_H_
