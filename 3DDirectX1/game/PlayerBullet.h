#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
/// <summary>
/// プレイヤー関連のクラス
/// </summary>
class PlayerBullet
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
	PlayerBullet();
	~PlayerBullet();
	void Initialize();//一回だけの初期化
	void Init(XMFLOAT2 position, XMFLOAT2 speed);//シーンチェンジ時にもする初期化
	void Update();
	void Draw();
	void OnCollision();

	//Getter
	XMFLOAT2 GetPlayerBulletPos() { return playerBulletPos; }

private:
	//プレイヤーの動き系
	Sprite* playerBulletSprite = nullptr;
	Sprite* sizeSprite = nullptr;
	//位置サイズ角度
	XMFLOAT2 playerBulletPos = { 0,0 };
	XMFLOAT2 bulletSpeed = { 0,0 };
	//当たり判定
	bool isAlive = false;
};
