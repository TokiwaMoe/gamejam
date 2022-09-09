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
	float GetRand() { return dropRand; }
	float GetTime() { return timer; }
	float GetEndTime() { return endTime; }
	float GetGravity() { return gravity; }
	XMFLOAT2 GetDropPos() { return dropPos[0]; }
	Circle GetCircle() { return circle; }
	int GetAttackNo() { return AttackNo; }
	float GetGrowTime() { return growTime; }
private:
	void Move();//�ړ�
	void Golf();
	void Roll();
	void Grow();
	void Drop();
	void DropRand();
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
	float dropRand;
	bool randFlag = false;
	bool dropFlag = false;
	float timer = 0;
	float endTime = 0;
	float gravity = 0;
	//roll�ϐ�
	XMFLOAT2 pigPos = { 2000,500 };
	float pigRot = 0;
	Circle circle;
	int AttackNo;
	//Grow�ϐ�
	Sprite* spGrow[3];
	float x = 320;
	float y = 240;
	float growPosX[4] = { x,x * 2,x * 3,x * 4 };
	float growPosY[3] = { 0,y * 2,y };
	int growRandX = 0;
	int growRandY = 0;
	float growTime = 0;
	bool growFlag = false;
	XMFLOAT2 growPos[3];

};