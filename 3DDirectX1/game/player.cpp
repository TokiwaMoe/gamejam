#include "player.h"
#include"input.h"
#include <cassert>
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
using namespace DirectX;
Player::Player()
{
}
Player::~Player()
{
}
void Player::Initialize()
{
	model = Model::Create("car", false);
	playerObj = Object3d::Create(model);
	model2 = Model::Create("bullet", true);
	SphereObj = Object3d::Create(model2);
	//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����//Create�̌�ɏ����Ȃ���client.h��InternalRelease()�ŃG���[���N����
	playerObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	SphereObj->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	Sprite::LoadTexture(2, L"Resources/dash.png");
	Sprite::LoadTexture(3, L"Resources/UI/sizeUI.png");
	dashSprite = Sprite::CreateSprite(2, { 0,0 });
	sizeSprite = Sprite::CreateSprite(3, { 100,100 });


}

void Player::Init()
{
	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);
	obb.m_NormaDirect[0] = { SphereObj->GetMatRot().r[0].m128_f32[0],SphereObj->GetMatRot().r[0].m128_f32[1] ,SphereObj->GetMatRot().r[0].m128_f32[2] };
	obb.m_NormaDirect[1] = { SphereObj->GetMatRot().r[1].m128_f32[0],SphereObj->GetMatRot().r[1].m128_f32[1] ,SphereObj->GetMatRot().r[1].m128_f32[2] };
	obb.m_NormaDirect[2] = { SphereObj->GetMatRot().r[2].m128_f32[0],SphereObj->GetMatRot().r[2].m128_f32[1] ,SphereObj->GetMatRot().r[2].m128_f32[2] };
	obb.m_fLength[0] = 1;
	obb.m_fLength[1] = 1;
	obb.m_fLength[2] = 1;
	obb.m_Pos = { spherePos.x,spherePos.y, spherePos.z };
	//playerPos={ 0,-0.8,0 };
	playerPos.y = 0;

		// �R���C�_�[�̒ǉ�
	float radius = 3.0f;
	SphereObj->SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	SphereObj->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);

	playerObj->SetCollider(new SphereCollider(XMVECTOR({ 0,2,0,0 }), radius));
	playerObj->GetCollider()->SetAttribute(COLLISION_ATTR_ALLIES);
	playerObj->Quaternion();
	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->Update();

}


void Player::Move()
{
	XMVECTOR moveUD = { 0,0,0.5,0 };//�O������p�̈ړ��x�N�g��
	XMVECTOR moveLR = { 0.5,0,0,0 };//���E�����̈ړ��p�x�N�g��
	XMVECTOR moveAngle = { 0,1,0,0 };//�p�x�̃x�N�g��
	XMVECTOR moveAngleX = { 10,0,0,0 };//�p�x�̃x�N�g��
	XMVECTOR moveAngleZ = { 0,0,10,0 };//�p�x�̃x�N�g��
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.m128_f32[1]));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
	moveUD = XMVector3TransformNormal(moveUD, matRot);
	moveLR = XMVector3TransformNormal(moveLR, matRot);
	moveAngle = XMVector3TransformNormal(moveAngle, matRot);
	if (Input::GetInstance()->PushKey(DIK_RIGHTARROW))
	{
		sphereAngle.m128_f32[1] += moveAngle.m128_f32[1];
		playerAngle.m128_f32[1] += moveAngle.m128_f32[1];

	}
	else if (Input::GetInstance()->PushKey(DIK_LEFTARROW))
	{
		sphereAngle.m128_f32[1] -= moveAngle.m128_f32[1];
		playerAngle.m128_f32[1] -= moveAngle.m128_f32[1];
	}
	if (Input::GetInstance()->PushKey(DIK_W))
	{
		playerPos.x += moveUD.m128_f32[0];
		playerPos.z += moveUD.m128_f32[2];
		sphereAngle.m128_f32[0] += 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_S))
	{
		playerPos.x -= moveUD.m128_f32[0];
		playerPos.z -= moveUD.m128_f32[2];
		sphereAngle.m128_f32[0] -= 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerPos.x += moveLR.m128_f32[0];
		playerPos.z += moveLR.m128_f32[2];
		sphereAngle.m128_f32[2] += 10;
	}
	else if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerPos.x -= moveLR.m128_f32[0];
		playerPos.z -= moveLR.m128_f32[2];
		sphereAngle.m128_f32[2] -= 10;
	}

	sphere.radius = r;
	sphere.center = XMVectorSet(spherePos.x, spherePos.y, spherePos.z, 1);
	obb.m_NormaDirect[0] = { SphereObj->GetMatRot().r[0].m128_f32[0],SphereObj->GetMatRot().r[0].m128_f32[1] ,SphereObj->GetMatRot().r[0].m128_f32[2] };
	obb.m_NormaDirect[1] = { SphereObj->GetMatRot().r[1].m128_f32[0],SphereObj->GetMatRot().r[1].m128_f32[1] ,SphereObj->GetMatRot().r[1].m128_f32[2] };
	obb.m_NormaDirect[2] = { SphereObj->GetMatRot().r[2].m128_f32[0],SphereObj->GetMatRot().r[2].m128_f32[1] ,SphereObj->GetMatRot().r[2].m128_f32[2] };
	obb.m_fLength[0] = 1;
	obb.m_fLength[1] = 1;
	obb.m_fLength[2] = 1;
	obb.m_Pos = { spherePos.x,spherePos.y, spherePos.z };
	playerObj->Update();
}

void Player::Ball()
{
#pragma region �J�����Ǐ]�Ƃقړ���
	XMVECTOR v0 = { 0,0,10,0 };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(sphereAngle.m128_f32[1]));
	//rotM *= XMMatrixRotationX(XMConvertToRadians(sphereAngle.m128_f32[0]));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR bossTarget = {playerPos.x,playerPos.y,playerPos.z };
	XMVECTOR v3 = bossTarget + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	//target = { bossTarget.m128_f32[0], bossTarget.m128_f32[1], bossTarget.m128_f32[2] };
	spherePos.x = f.x;
	spherePos.y = f.y + 3;
	spherePos.z = f.z;
#pragma endregion


}

void Player::Jump()
{


		// ��������
	if (!onGround) {
		// �����������x
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// ����
		fallV.m128_f32[1] = max(fallV.m128_f32[1] + fallAcc, fallVYMin);
		// �ړ�
		playerPos.x += fallV.m128_f32[0];
		playerPos.y += fallV.m128_f32[1];
		playerPos.z += fallV.m128_f32[2];
	}
	 //�W�����v����
	else if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		onGround = false;
		const float jumpVYFist = 0.2f;
		fallV = { 0, jumpVYFist, 0, 0 };
	}
	playerObj->Update();
	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(playerObj->GetCollider());
	assert(sphereCollider);

	//// ���̏�[���狅�̉��[�܂ł̃��C�L���X�g
	Ray ray;
	ray.start = sphereCollider->center;
	ray.start.m128_f32[1] += sphereCollider->GetRadius();
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;

	// �ڒn���
	if (onGround) {
		// �X���[�Y�ɍ������ׂ̋z������
		const float adsDistance = 0.2f;
		// �ڒn���ێ�
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistance)) {
			onGround = true;
			//���̏������L�������-nan(ind)���ďo�ĉ�ʂ�OBJ���\������Ȃ�
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			playerObj->SetPosition(playerPos);
			playerObj->Update();
		}
		// �n�ʂ��Ȃ��̂ŗ���
		else {
			onGround = false;
			fallV = {};
		}
	}
	// �������
	else if (fallV.m128_f32[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
			// ���n
			onGround = true;
			playerPos.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
			playerObj->SetPosition(playerPos);
			playerObj->Update();
		}
	}


}

void Player::Dash()
{
	dashCoolTime--;
	if (dashCoolTime <= 0 && dashTime <= 0)
	{
		dashCoolTime = 0;
		dashFlag = false;
	}
	if (Input::GetInstance()->TriggerKey(DIK_UPARROW)&&dashFlag==false)
	{
		dashTime = dashTimeMax;
		fade = 1;
		dashFlag = true;
	}

	if (dashTime > 0)
	{
		dashTime--;
		if (dashTime <= 0)
		{
			dashCoolTime = dashCoolTimeMax;
		}
		XMVECTOR movedash = { 0,0,2,0 };//�O������p�̈ړ��x�N�g��
		
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(playerAngle.m128_f32[1]));//y ���𒆐S�ɉ�]����}�g���b�N�X���쐬
		movedash = XMVector3TransformNormal(movedash, matRot);

		playerPos.x += movedash.m128_f32[0];
		playerPos.z += movedash.m128_f32[2];
		if (fade > 0) {
			fade -= 0.05f;
		}
	}

}


void Player::Update()
{
	Move();
	Jump();
	Ball();
	Dash();

	sizeSprite->SetAnchorPoint({ 0.5, 0.5 });

	SphereObj->SetPosition(spherePos);
	SphereObj->SetScale(sphereSize);
	SphereObj->SetRotation(sphereAngle);
	SphereObj->Quaternion();
	SphereObj->Update();
	playerObj->SetPosition(playerPos);
	playerObj->SetRotation(playerAngle);
	playerObj->Quaternion();
	playerObj->SetScale({ 1,1,1 });
	playerObj->Update();

	dashSprite->SetColor({1, 1, 1, fade});
}

void Player::OnCollision(const CollisionInfo& info)
{
	SphereObj->OnCollision(info);
}


void Player::Draw()
{
	playerObj->Draw();
	SphereObj->Draw();
	
}

void Player::DrawSprite()
{
	sizeSprite->Draw();
	if (dashFlag == true) {
		dashSprite->Draw();
	}
}
