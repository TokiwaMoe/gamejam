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
	Sprite::LoadTexture(2, L"Resources/player/walk.png");
	Sprite::LoadTexture(3, L"Resources/player/stay.png");
	//Sprite::LoadTexture(3, L"Resources/UI/sizeUI.png");
	playerSprite_Walk = Sprite::CreateSprite(2, { 0,0 });
	playerSprite_Walk->SetSize({ 128,128 });
	playerSprite_Walk->SetTextureRect({ 0,0 }, { 48,48 });

	playerSprite_Stay = Sprite::CreateSprite(3, { 0,0 });
	playerSprite_Stay->SetSize({ 128,128 });
	playerSprite_Stay->SetTextureRect({ 0,0 }, { 48,48 });
	//sizeSprite = Sprite::CreateSprite(3, { 100,100 });


}

void Player::Init()
{
	circle.center = playerPos;
	circle.radius = 5;
	playerPos = { 50,100 };

}


void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerPos.x += 2;
		playerFlag = false;
		isRight = true;
		isWalk = true;
	}
	else if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerPos.x -= 2;
		playerFlag = true;
		isRight = false;
		isWalk = true;
	}
	else {
		isWalk = false;
	}

	if (Input::GetInstance()->PushKey(DIK_UPARROW))
	{
		playerPos.y += 2;
	}
	circle.center = playerPos;
	circle.radius = 50;
}


void Player::Jump()
{
	if (jumpFlag == false) {
		if (Input::GetInstance()->PushKey(DIK_SPACE))
		{
			jumpFlag = true;
			gFlag = false;
			jSpeed = 0;
		}
	}
	else if (jumpFlag == true) {
		if (gFlag == false) {
			if (playerPos.y > 50)
			{
				playerPos.y -= jSpeed;
				jSpeed += g;
			}
			if (playerPos.y <= 50) { gFlag = true; }
		}
		else if (gFlag == true) {
			if (playerPos.y < 100)
			{
				playerPos.y += jSpeed;
				jSpeed += g;
			}
			if (playerPos.y >= 100) { jumpFlag = false; playerPos.y = 100; }
		}
	}

}



void Player::Update()
{
	Move();
	Jump();
	Attack();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update();
	}

	walkAnima += 0.5f;

	if (walkAnima >= 8)
	{
		walkNo++;
		walkAnima = 0;

		if (walkNo == 3)
		{
			walkNo = 0;
		}
	}

	stayAnima += 0.5f;

	if (stayAnima >= 8)
	{
		stayNo++;
		stayAnima = 0;

		if (stayNo == 2)
		{
			stayNo = 0;
		}
	}

	playerSprite_Walk->SetTextureRect({ 0 + 48 * walkNo,0 }, { 48,48 });
	playerSprite_Walk->SetAnchorPoint({ 0.5, 0.5 });
	playerSprite_Stay->SetTextureRect({ 0 + 48 * stayNo,0 }, { 48,48 });
	playerSprite_Stay->SetAnchorPoint({ 0.5, 0.5 });
	playerSprite_Walk->SetPosition(playerPos);
	playerSprite_Walk->SetIsFlipX(playerFlag);
	playerSprite_Stay->SetPosition(playerPos);
	playerSprite_Stay->SetIsFlipX(playerFlag);
}




void Player::Attack()
{
	bulletTime += 0.3f;

	if (bulletTime >= maxBulletTime)
	{
		XMFLOAT2 oldPosition = playerPos;
		bulletCircle.center = oldPosition;
		bulletCircle.radius = 10;
		const float kBulletSpeed = 3.0f;
		XMFLOAT2 velocity;

		if (isRight == false)
		{
			velocity = { -kBulletSpeed, 0 };
		}
		else {
			velocity = { kBulletSpeed, 0 };
		}
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize();
		newBullet->Init(oldPosition, velocity);

		//’e‚ð“o˜^‚·‚é
		bullets_.push_back(std::move(newBullet));

		bulletTime = 0;
	}

}

void Player::Draw()
{

}

void Player::DrawSprite()
{
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw();
	}

	if (isWalk)
	{
		playerSprite_Walk->Draw();
	}
	else {
		playerSprite_Stay->Draw();
	}

}

