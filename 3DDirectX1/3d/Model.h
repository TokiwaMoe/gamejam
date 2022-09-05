#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Mesh.h"
/// <summary>
/// OBJ�p�̃��f���N���X
/// </summary>
class Model
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

public:
	~Model();

	static void StaticInitialize(ID3D12Device* dev);

	static Model* Create(const std::string& modelname, bool smoothing = false);

	void Initialize(const std::string& modelname, bool smoothing);
	
	// �`��
	void Draw(ID3D12GraphicsCommandList* cmdList);

	inline const std::vector<Mesh*>& GetMeshes() { return meshes; }


private:


	void LoadTextures();
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	void LoadModel(const std::string& modelname, bool smoothing);
	
	void AddMaterial(Material* material);
	
	void CreateDescriptorHeap();

	static const std::string baseDirectory;
	// �f�o�C�X
	static ID3D12Device* dev;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// ���O
	std::string name;
	// ���b�V���R���e�i
	std::vector<Mesh*> meshes;
	// �}�e���A���R���e�i
	std::unordered_map<std::string, Material*> materials;
	// �f�t�H���g�}�e���A��
	Material* defaultMaterial = nullptr;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
};