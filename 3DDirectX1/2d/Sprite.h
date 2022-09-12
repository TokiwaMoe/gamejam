#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>


using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib, "d3dcompiler.lib")
class Sprite {

private:

	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:


	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};

	struct ConstBufferData
	{
		XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};
	//�ÓI�����o�֐�
	static bool StaticInitialize(ID3D12Device* dev, int window_width, int window_height);
	//�`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//�`��㏈��
	static void PostDraw();
	//�X�v���C�g����
	static Sprite* CreateSprite(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1,1,1,1 }, XMFLOAT2 anchorpoint = { 0.0f,0.0f }, bool isFlipX = false, bool isFlipY = false);
	//�e�N�X�`���ǂݍ���
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);


	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	//������
	bool Initialize();
	//��]�̐ݒ�
	void SetRotation(float rotation);
	//���W�̐ݒ�
	void SetPosition(XMFLOAT2 position);
	//�T�C�Y�̐ݒ�
	void SetSize(XMFLOAT2 size);

	void SetColor(XMFLOAT4 color);
	//�A���J�[�|�C���g�̐ݒ�
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	//���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);
	//�㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);
	//�e�N�X�`���͈̔͂̐ݒ�
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	//�`��
	void Draw();
	XMFLOAT3 SetEye(XMFLOAT3 eye) { return this->eye = eye; }
protected:



	void TransferVertices();

	//�ÓI�����o�ϐ�
	//�e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512; //�e�N�X�`���̍ő喇��
	//���_��
	static const int vertNum = 4;
	//�f�o�C�X
	static ID3D12Device* dev;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	//�R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	//���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	//�f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	//�ˉe�s��
	static XMMATRIX matProjection;
	static XMMATRIX matView;
	static XMFLOAT3 eye;
	static XMFLOAT3 target;
	static XMFLOAT3 up;
	//�����o�ϐ�
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	//�e�N�X�`���ԍ�
	UINT texNumber = 0;
	//Z���̉�]�p
	float rotation = 0.0f;
	//���[�J�����W
	XMFLOAT2 position = {};
	//�X�v���C�g���A����
	XMFLOAT2 size = { 100.0f,100.0f };
	//�A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0,0 };
	//���[���h�ϊ��s��
	XMMATRIX matWorld{};
	//�F
	XMFLOAT4 color = { 1,1,1,1 };
	//���E���]
	bool isFlipX = false;
	//�㉺���]
	bool isFlipY = false;
	//�e�N�X�`���n�_
	XMFLOAT2 texBase = { 0,0 };
	//�e�N�X�`�����A����
	XMFLOAT2 texSize = { 100.0f,100.0f };

};
