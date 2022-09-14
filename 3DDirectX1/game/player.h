#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
#include"PlayerBullet.h"
#include<memory>
#include<list>
#include"Audio.h"
/// <summary>
/// プレイヤー関連のクラス
/// </summary>
class Player
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
	Player();
	~Player();
	void Initialize();//一回だけの初期化
	void Init();//シーンチェンジ時にもする初期化
	void Update();
	//void OnCollision(const CollisionInfo& info);
	void OnCollisionCall();
	void Attack();
	void Draw();
	void DrawSprite();

	//Getter
	XMFLOAT2 GetPlayerPos() { return playerPos; }
	Circle GetCircle() { return circle; }
	Circle GetBulletCircle() { return bulletCircle; };
	int GetHP() { return HP; }
	XMFLOAT2 GetOldPos() { return oldPosition; }
	XMFLOAT2 GetVelocity() { return velocity; }
	bool GetAudioFlag() { return AudioFlag; }
	bool GetIsHit() { return isHit; }
	bool SetHit(bool hit) { return this->isHit = hit; }
	//弾リストを取得
	const std::list < std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; }
private://プレイヤーの動き系
	void Move();//移動
	void Jump();//ジャンプ

	bool AudioFlag = false;
	Sprite* playerSprite_Walk = nullptr;
	Sprite* playerSprite_Stay = nullptr;
	Sprite* sizeSprite = nullptr;
	float eye;
	//位置サイズ角度
	XMFLOAT2 playerPos = { 0,0 };
	bool playerFlag = false;
	bool jumpFlag = false;
	bool gFlag = false;
	float g = 9.8f / 60;
	float jSpeed;
	Circle circle;
	Circle bulletCircle;
	float bulletTime = 10;
	float maxBulletTime = 10;
	bool isRight = true;

	float walkAnima = 0;
	float walkNo = 0;
	float stayAnima = 0;
	float stayNo = 0;
	bool isWalk = false;
	XMFLOAT2 oldPosition = { 0,0 };
	XMFLOAT2 velocity = { 0,0 };
	Sprite* pHP[5];
	XMFLOAT2 oldPos = { 0,0 };

	int HP = 5;
	bool isHit = false;
public:
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};