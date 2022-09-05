#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "Material.h"
#include <vector>
#include <unordered_map>

class Mesh
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public: // �T�u�N���X

	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};

public: // �ÓI�����o�֐�

	static void StaticInitialize(ID3D12Device* dev);


public: // �����o�֐�

	const std::string& GetName() { return name; }

	void SetName(const std::string& name);

	void AddVertex(const VertexPosNormalUv& vertex);

	void AddIndex(unsigned short index);

	inline size_t GetVertexCount() { return vertices.size(); }

	void AddSmoothData(unsigned short indexPosition, unsigned short indexVertex);

	void CalculateSmoothedVertexNormals();

	Material* GetMaterial() { return material; }

	void SetMaterial(Material* material);

	void CreateBuffers();

	const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }

	const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }

	void Draw(ID3D12GraphicsCommandList* cmdList);

	inline const std::vector<VertexPosNormalUv>& GetVertices() { return vertices; }

	inline const std::vector<unsigned short>& GetIndices() { return indices; }


private: // �����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* dev;
	// ���O
	std::string name;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// ���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;
	// �}�e���A��
	Material* material = nullptr;
};

