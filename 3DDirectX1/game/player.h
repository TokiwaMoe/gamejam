#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
#include"PlayerBullet.h"
#include<memory>
#include<list>
/// <summary>
/// �v���C���[�֘A�̃N���X
/// </summary>
class Player
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
	Player();
	~Player();
	void Initialize();//��񂾂��̏�����
	void Init();//�V�[���`�F���W���ɂ����鏉����
	void Update();
	void OnCollision(const CollisionInfo& info);
	void Attack();
	void Draw();
	void DrawSprite();

	//Getter
	XMFLOAT2 GetPlayerPos() { return playerPos; }
	Circle GetCircle() { return circle; }
	int SetHP(int hp) { return this->HP = hp; }
private://�v���C���[�̓����n
	void Move();//�ړ�
	void Jump();//�W�����v


	Sprite* playerSprite = nullptr;
	Sprite* sizeSprite = nullptr;
	float eye;
	int HP = 3;
	//�ʒu�T�C�Y�p�x
	XMFLOAT2 playerPos = { 0,0 };
	bool playerFlag = false;
	bool jumpFlag = false;
	bool gFlag = false;
	float g = 9.8f / 60;
	float jSpeed;
	Circle circle;

	float bulletTime = 10;
	float maxBulletTime = 10;
	bool isRight = true;
public:
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};