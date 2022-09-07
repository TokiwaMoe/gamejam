#pragma once
#include"Sprite.h"
#include"Collision.h"
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
	Circle GetCircle() { return circle; }
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
	float lane_Width = 128;
	Sprite* spCard[9];
	XMFLOAT2 dropPos[9];
	float lane[10] = { 0,lane_Width,lane_Width * 2,lane_Width * 3,lane_Width * 4, lane_Width * 5,lane_Width * 6,lane_Width * 7,lane_Width * 8,lane_Width * 9 };
	int rand;
	//���[���֐�
	XMFLOAT2 pigPos = { 2000,500 };
	float pigRot = 0;
	Circle circle;
};