#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
/// <summary>
/// �v���C���[�֘A�̃N���X
/// </summary>
class PlayerBullet
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
	PlayerBullet();
	~PlayerBullet();
	void Initialize();//��񂾂��̏�����
	void Init(XMFLOAT2 position, XMFLOAT2 speed);//�V�[���`�F���W���ɂ����鏉����
	void Update();
	void Draw();
	void OnCollision();

	//Getter
	XMFLOAT2 GetPlayerBulletPos() { return playerBulletPos; }
	bool GetIsAlive() { return isAlive; }

private:
	//�v���C���[�̓����n
	Sprite* playerBulletSprite = nullptr;
	Sprite* sizeSprite = nullptr;
	//�ʒu�T�C�Y�p�x
	XMFLOAT2 playerBulletPos = { 0,0 };
	XMFLOAT2 bulletSpeed = { 0,0 };
	//�����蔻��
	bool isAlive = false;
};
