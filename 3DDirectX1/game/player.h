#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"Sprite.h"
#include"SafeDelete.h"
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
	void Draw();
	void DrawSprite();

	//Getter
	XMFLOAT3 GetPlayerPos() { return playerPos; }
	XMFLOAT3 GetSpherePos() { return spherePos; }
	XMVECTOR GetSphereAngle() { return sphereAngle; }
	XMVECTOR GetPlayerAngle() { return playerAngle; }
	float GetCameraAngle() { return cameraAngle; }
	Sphere GetSphere() { return sphere; }
	OBB GetOBB() { return obb; }
	Object3d* GetObject() { return SphereObj; }
	float GetTsize() { return Tsize; }
	float SetTsize(float tsize) { return this->Tsize = tsize; }
	bool SetTransFlag(bool transFlag) { return this->transFlag = transFlag; }
	float GetJspeed() { return jspeed; }
	bool GetOnGround() { return onGround; }
private://�v���C���[�̓����n
	void Move();//�ړ�
	void Ball();//�{�[���֌W
	void Jump();//�W�����v
	void Dash();//�_�b�V��
private://�ϐ�
	Object3d* playerObj=nullptr;
	Model* model=nullptr;
	Object3d* SphereObj=nullptr;
	Model* model2=nullptr;

	Sprite* dashSprite=nullptr;
	Sprite* sizeSprite=nullptr;
	//�ʒu�T�C�Y�p�x
	XMFLOAT3 playerPos = { 0,0,0 };
	XMFLOAT3 spherePos = { 0,0,0 };
	XMVECTOR playerAngle = { 0,0,0,0 };
	XMVECTOR sphereAngle = { 0,0,0,0 };
	XMFLOAT3 sphereSize = { 1,1,1 };
	float cameraAngle = 0;
	Sphere sphere;
	
	float radAD = 0.0f;
	float radWS = 0.0f;
	OBB obb;
	float Tsize = 1;//���̃T�C�Y(����ɕ\������Ă�����)
	float r = 3;
	bool transFlag = false;
	bool JumpFlag = false;
	bool gFlag = false;
	float g = 0.0098;
	float jspeed;
	bool dashFlag = false;
	float dashSpeed = 2.0f;
	int dashCoolTime = 0;
	const int dashCoolTimeMax = 20;
	int dashTime = 0;
	const int dashTimeMax = 20;
	float fade = 1;
	bool onGround = true;
	// �����x�N�g��
	DirectX::XMVECTOR fallV;
};