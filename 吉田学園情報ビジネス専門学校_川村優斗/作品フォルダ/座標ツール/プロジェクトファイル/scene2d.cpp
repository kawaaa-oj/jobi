//=============================================================================
//
// 2D�V�[���̏��� [scene2d.cpp]
// Author : �쑺�D�l
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include"scene2d.h"
#include"manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(int nPriority) : CScene(nPriority)
{
	memset(&m_size, 0, sizeof(m_size));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// ���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W�̐ݒ�	
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit()
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw()
{
	// �f�o�C�X���擾����
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update()
{
	// ���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// ���_���W�̐ݒ�	
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 2D�V�[���̐���
//=============================================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR2 size)
{
	CScene2D *pScene2D = new CScene2D;
	if (pScene2D != NULL)
	{
		pScene2D->Init();
		pScene2D->SetPosition(pos);
		pScene2D->SetSize(size);
	}
	return pScene2D;
}

//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ���W�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::Getposition(void)
{
	return m_pos;
}

//=============================================================================
// �e�N�X�`���̊��蓖��
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

void CScene2D::DeleteTexture()
{
	m_pTexture = NULL;
}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void  CScene2D::SetSize(D3DXVECTOR2 size)
{
	m_size = D3DXVECTOR2(size);
}

//=============================================================================
// �T�C�Y�̎擾
//=============================================================================
D3DXVECTOR2 CScene2D::GetSize(void)
{
	return m_size;
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	//���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::SetVtxTex(int PtnAnim, float fAnimU, float TexU, float TexV)
{

	m_FTexU = TexU;
	m_FTexV = TexV;

	// ���_���ւ̃|�C���^
	VERTEX_2D * pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void **)&pVtx, 0);

	// �e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(PtnAnim * fAnimU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(PtnAnim * fAnimU + TexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(PtnAnim * fAnimU, m_FTexV);
	pVtx[3].tex = D3DXVECTOR2(PtnAnim * fAnimU + TexU, m_FTexV);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
