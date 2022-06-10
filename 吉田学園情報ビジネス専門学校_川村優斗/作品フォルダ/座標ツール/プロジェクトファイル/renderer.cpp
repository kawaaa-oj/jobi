//=============================================================================
//
// �����_���[�̏��� [renderer.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"renderer.h"
#include"scene.h"
#include"polygon.h"
#include"padx.h"
#include"keyboard.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_nFont = NULL;
	m_bColorFlag = false;
	m_bDeleteFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = true;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs��
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs��
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs��
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O���s��Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p

	//�����x�̐ݒ���ł���悤�ɂ��Ă���
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�


	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 22, 10, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_nFont);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_nFont != NULL)
	{
		m_nFont->Release();
		m_nFont = NULL;
	}

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	CScene::UpdateAll();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();

		// FPS�\��
		DrawFPS();

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

// �A���t�@�u�����f�B���O�̉��Z����
void CRenderer::AddSynthesis(bool bUse)
{
	if (bUse == true)
	{
		// ���u�����f�B���O�����Z�����ɐݒ�
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}
	else
	{
		// ���u�����f�B���O��ʏ�ɖ߂�
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[300];

	// FPS���擾
	m_nCntFPS = GetFPS();

	// ���W�Ƒ傫�����i�[
	int x = 0.0f;
	int y = 0.0f;
	int z = 0.0f;
	int w = 0.0f;
	int h = 0.0f;

	// �|���S���̎擾
	CPolygon *pPolygon = CManager::GetPolygon();

	// �L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// �Q�[���p�b�h�擾
	CPadX *pPadX = CManager::GetPadX();

	if (pPolygon != NULL)
	{
		D3DXVECTOR3 pos = pPolygon->GetPos();
		D3DXVECTOR2 size = pPolygon->GetSize();

		// ���W�Ƒ傫�����i�[
		x = pos.x;
		y = pos.y;
		z = pos.z;
		w = size.x;
		h = size.y;

		// �p�b�h�ڑ�����
		bool bConnect = pPadX->ConnectPad();

		// �f�o�b�O�\��(�p�b�h�ڑ����Ƃ���ȊO�ŕ\���𕪂���)
		if (bConnect == false)
		{
			wsprintf(str, "FPS:%d\n�|���S���̈ʒu X:%d,Y:%d,Z:%d\n�|���S���̑傫�� ��:%d,����:%d\n[��������]:�ړ� [A,D]:�� [W,S]:����\n[Shift]�L�[�������Ȃ���:������\n[P]:txt�t�@�C���ɕۑ�\n[Enter]:�e�N�X�`��ON/OFF [Space]:�w�iON/OFF\n[X]:�傫���ʒu���Z�b�g\n[��Ctrl]:����������\n[�ECtrl]:�����̐F��ς���", m_nCntFPS, x, y, z, w, h);
		}
		else
		{
			wsprintf(str, "FPS:%d\n�|���S���̈ʒu X:%d,Y:%d,Z:%d\n�|���S���̑傫�� ��:%d,����:%d\n[���X�e�B�b�N]:�ړ� [�E�X�e�B�b�N]:���A����\n[RB]�������Ȃ���:������\n[A]:txt�t�@�C���ɕۑ�\n[B]:�e�N�X�`��ON/OFF [X]:�w�iON/OFF\n[Y]:�傫���ʒu���Z�b�g\n[Back]:����������\n[Start]:�����̐F��ς���", m_nCntFPS, x, y, z, w, h);
		}
	}

	// �F��ς���
	if (pKeyboard->GetTrigger(DIK_RCONTROL) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_START) == true)
	{
		switch (m_bColorFlag)
		{
		case false:
			m_bColorFlag = true;
			break;
		case true:
			m_bColorFlag = false;
			break;
		}
	}

	// �����̃I���I�t
	if (pKeyboard->GetTrigger(DIK_LCONTROL) == true || pPadX->GetButtonTrigger(XINPUT_GAMEPAD_BACK) == true)
	{
		switch (m_bDeleteFlag)
		{
		case false:
			m_bDeleteFlag = true;
			break;
		case true:
			m_bDeleteFlag = false;
			break;
		}
	}

	// ����ɗ���Ǝז��Ȃ̂Ńe�L�X�g���ړ�
	if ((x <= 380 + w) && (y <= 200 + h))
	{
		switch (m_bColorFlag)
		{
		case false:
			switch (m_bDeleteFlag)
			{
			case false:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xbf, 0xbf, 0));
				break;
			case true:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		case true:
			switch (m_bDeleteFlag)
			{
			case false:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0, 0, 0xff));
				break;
			case true:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		}
	}
	else
	{
		switch (m_bColorFlag)
		{
		case false:
			switch (m_bDeleteFlag)
			{
			case false:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xbf, 0xbf, 0));
				break;
			case true:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		case true:
			switch (m_bDeleteFlag)
			{
			case false:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0, 0, 0xff));
				break;
			case true:
				// �e�L�X�g�`��
				m_nFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0, 0, 0, 0));
				break;
			}
			break;
		}
	}
}