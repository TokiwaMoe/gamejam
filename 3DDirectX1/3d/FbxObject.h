#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "FbxModel.h"
#include "FbxLoader.h"
#include "Camera.h"
class FbxObject3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//�{�[���̍ő吔
	static const int MAX_BONES = 32;

	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
	};
	struct ConstBufferDataSkin
	{
		XMMATRIX bones[MAX_BONES];

	};



	static void CreateGraphicsPipeline(const wchar_t* ps, const wchar_t* vs);
	static void SetDev(ID3D12Device* dev) {
		FbxObject3d::dev = dev;
	}
	static void SetCamera(Camera* camera) {
		FbxObject3d::camera = camera;
	}

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	void Initialize();

	void Update();

	void Draw();

	void PlayAnimation();

	const XMFLOAT3& GetPosition() { return position; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }

	const XMFLOAT3& GetRotation() { return rotation; }

	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// ���f���Ƃ̘A�g
	void SetModel(FbxModel* fbxModel) { this->fbxModel = fbxModel; };




protected:
	ComPtr<ID3D12Resource> constBuffTransform;

	ComPtr<ID3D12Resource> constBuffSkin;
private:

	// �f�o�C�X
	static ID3D12Device* dev;

	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;

	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;



	//ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@


	// �F
	//XMFLOAT4 color = { 1,0,0,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	FbxObject3d* parent = nullptr;

	FbxModel* fbxModel = nullptr;

	// �J����
	static Camera* camera;

	//1�t���[���̎���
	FbxTime frameTime;
	//�A�j���[�V�����J�n����	
	FbxTime startTime;
	//�A�j���[�V�����I������
	FbxTime endTime;
	//���ݎ���
	FbxTime currentTime;
	//�A�j���[�V�����Đ���
	bool isPlay = false;
};

