#pragma once
#include"Sprite.h"
#include"Collision.h"
#include"Ease.h"
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
	XMFLOAT2 GetGolfPos() { return GolfPos; }
	float GetEaseTimer() { return easeTimer; }
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
	//���[���ϐ�
	Sprite* pig = nullptr;
	XMFLOAT2 pigPos = { 2000,500 };
	float pigRot = 0;
	Circle circle;
	//�U���̎�ނ����߂邽�߂̂���
	int AttackNo;
	//Grow�ϐ�
	Sprite* spGrow[3];
	XMFLOAT2 growPos[3];
	//Golf�ϐ�
	Eas* eas;
	Sprite* golf = nullptr;
	XMFLOAT2 GolfPos = { 1000,200 };
	bool Mflag = false;
	XMFLOAT2 v2 = { 0.0f,0.0f };
	float f = 10.0f;
	float v = 40.0f;
	float k = 1.0f;
	float a = 0.f;
	float g = 9.8f / 60.0f;
	float fx1 = 1.0f;
	float m = 10.0f;
	float t = 0.0f;
	float PI = 3.141592;
	float easeTimer = 0;
};