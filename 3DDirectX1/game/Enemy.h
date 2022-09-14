#pragma once
#include"Sprite.h"
#include"Collision.h"
#include"Ease.h"
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
	void OnCollision();
	void Draw();
	//Getter
	float GetRand() { return dropRand; }
	float GetTime() { return timer; }
	float GetEndTime() { return endTime; }
	float GetGravity() { return gravity; }
	XMFLOAT2 GetDropPos() { return dropPos[0]; }
	Circle GetCircle() { return circle; }
	Circle GetDropCircle(int i) { return dropCircle[i]; }
	Circle GetGrowCircle(int i) { return growCircle[i]; }
	Circle GetGolfCircle() { return golfCircle; }
	int GetAttackNo() { return AttackNo; }

	XMFLOAT2 GetGolfPos() { return GolfPos; }
	float GetEaseTimer() { return easeTimer; }

	float GetGrowTime() { return growAnimation; }

	int GetGrowRandX() { return growRandX; }
	int GetGrowRandY() { return growRandY; }

	int GetHP() { return HP; }
	int SetHP(int hp) { return this->HP = hp; }

	XMFLOAT2 GetGrowPos() { return growPos; }
	Circle GetEnemyCircle() { return enemyCircle; }

	const XMFLOAT2 GetPosition() { return position; }

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
	Sprite* EHP = nullptr;
	Sprite* EHPFrame = nullptr;
	XMFLOAT2 position = { 1200,490 };
	int HP = 150;
	Circle enemyCircle;
	//drop変数
	float lane_Width = 128;
	Sprite* spCard[6];
	XMFLOAT2 dropPos[6];
	float lane[7] = { 0,lane_Width,lane_Width * 2,lane_Width * 3,lane_Width * 4, lane_Width * 5,lane_Width * 6 };
	float dropRand;
	bool randFlag = false;
	bool dropFlag = false;
	float timer = 0;
	float endTime = 0;
	float gravity = 0;
	bool behindFlag = false;
	float behindTime = 0;
	Circle dropCircle[6];
	//ロール変数
	Sprite* pig = nullptr;

	//roll変数

	XMFLOAT2 pigPos = { 2000,490 };
	float pigRot = 0;
	Circle circle;
	//攻撃の種類を決めるためのもの
	int AttackNo;
	//Grow変数
	Sprite* spGrow_Y;
	Sprite* spGrow_X;
	float x = 230;
	float y = 150;
	float growPosX[3] = { x,x * 2,x * 3 };
	float growPosY[3] = { 0,y * 2,y };
	int growRandX = 0;
	int growRandY = 0;
	float growRandTime = 0;
	bool growRandFlag = false;
	XMFLOAT2 growPos;
	XMFLOAT2 growPos2 = { 0,720 };
	bool growFlag = false;
	float growTime = 0;
	float growAnimation = 0;
	float growNo = 0;
	Circle growCircle[3];
	//Golf変数
	Eas* eas;
	Sprite* backGolf = nullptr;
	Sprite* golf = nullptr;
	Sprite* enGolf = nullptr;
	XMFLOAT2 GolfPos = { 1000,600 };
	bool GolfFlag = false;
	float easeTimer = 0;
	Circle golfCircle;

	float backAnime = 0;
	bool isBackAnime = false;
	float backNo = 0;

	float enGolfNo = 0;
	float enGolfAnime = 0;

	bool isAlive = false;
};