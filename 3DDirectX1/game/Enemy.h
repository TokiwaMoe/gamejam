#pragma once
#include"Sprite.h"

/// <summary>
/// �v���C���[�֘A�̃N���X
/// </summary>
class Enemy
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	Enemy();
	~Enemy();
	void Initialize();//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void Update();

	void Draw();
	//Getter

private:
	void Move();//�ړ�
	void Golf();
	void Roll();
	void Grow();
	void Drop();
	void Attack();
private://�ϐ�
	Sprite* spEnemy = nullptr;
	Sprite* pig = nullptr;
	XMFLOAT2 position = { 0,0 };

	//drop�ϐ�
	Sprite* spCard = nullptr;
	XMFLOAT2 dropPos[9];
	char lane[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int rand;
	//���[���֐�
	XMFLOAT2 pigPos = { 2000,500 };
	float pigRot = 0;
};