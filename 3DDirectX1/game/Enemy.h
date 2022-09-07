#pragma once
#include"Sprite.h"
#include"Collision.h"
/// <summary>
/// プレイヤー関連のクラス
/// </summary>
class Enemy
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	Enemy();
	~Enemy();
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void Update();

	void Draw();
	//Getter
	float GetRand() { return dropRand; }
	float GetTime() { return time; }
	float GetEndTime() { return endTime; }
	float GetGravity() { return gravity; }
	XMFLOAT2 GetDropPos() { return dropPos[0]; }
	Circle GetCircle() { return circle; }
	int GetAttackNo() { return AttackNo; }
private:
	void Move();//移動
	void Golf();
	void Roll();
	void Grow();
	void Drop();
	void DropRand();
	void Attack();
private://変数
	Sprite* spEnemy = nullptr;
	Sprite* pig = nullptr;
	XMFLOAT2 position = { 0,0 };

	//drop変数
	float lane_Width = 128;
	Sprite* spCard[9];
	XMFLOAT2 dropPos[9];
	float lane[10] = { 0,lane_Width,lane_Width * 2,lane_Width * 3,lane_Width * 4, lane_Width * 5,lane_Width * 6,lane_Width * 7,lane_Width * 8,lane_Width * 9 };
	float dropRand;
	bool randFlag = false;
	bool dropFlag = false;
	float time = 0;
	float endTime = 0;
	float gravity = 0;
	//ロール関数
	XMFLOAT2 pigPos = { 2000,500 };
	float pigRot = 0;
	Circle circle;
	int AttackNo;
	//Grow変数
	Sprite* spGrow[3];
	XMFLOAT2 growPos[3];

};