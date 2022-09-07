#pragma once
#include"Sprite.h"

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

private:
	void Move();//移動
	void Golf();
	void Roll();
	void Grow();
	void Drop();
	void Attack();
private://変数
	Sprite* spEnemy = nullptr;
	XMFLOAT2 position = { 0,0 };

	//drop変数
	Sprite* spCard = nullptr;
	XMFLOAT2 dropPos[9];
	char lane[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int rand;

};