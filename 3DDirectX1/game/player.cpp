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
	delete& bullets_;
}
void Player::Initialize()
{
	Sprite::LoadTexture(2, L"Resources/player/walk.png");
	Sprite::LoadTexture(3, L"Resources/player/stay.png");
	Sprite::LoadTexture(50, L"Resources/PlayerHP.png");
	//Sprite::LoadTexture(3, L"Resources/UI/sizeUI.png");
	playerSprite_Walk = Sprite::CreateSprite(2, { 0,0 });
	playerSprite_Walk->SetSize({ 128,128 });
	playerSprite_Walk->SetTextureRect({ 0,0 }, { 48,48 });

	playerSprite_Stay = Sprite::CreateSprite(3, { 0,0 });
	playerSprite_Stay->SetSize({ 128,128 });
	playerSprite_Stay->SetTextureRect({ 0,0 }, { 48,48 });
	//sizeSprite = Sprite::CreateSprite(3, { 100,100 });
	for (int i = 0; i < 5; i++) {
		pHP[i] = Sprite::CreateSprite(50, { playerPos.x,playerPos.y - 20 });
	}
 
}

void Player::Init()
{
	circle.center = playerPos;
	circle.radius = 50;
	sphere.center = { playerPos.x,playerPos.y,0,0 };
	sphere.radius = 50;
	playerPos = { 65,627 };
	HP = 5;
}


void Player::Move()
{
	
	if (Input::GetInstance()->PushKey(DIK_D) && playerPos.x <= 1280 - 64)
	{
		playerPos.x += 4;
		playerFlag = false;
		isRight = true;
		isWalk = true;
	}
	else if (Input::GetInstance()->PushKey(DIK_A) && playerPos.x >= 64)
	{
		playerPos.x -= 4;
		playerFlag = true;
		isRight = false;
		isWalk = true;
	}
	else {
		isWalk = false;
	}
	if (Input::GetInstance()->PushKey(DIK_UPARROW))
	{
		playerPos.y += 4;
	}
	if (Input::GetInstance()->PushKey(DIK_DOWN))
	{
		playerPos.y -= 4;
	}
	
	circle.center = playerPos;
	circle.radius = 50;
	sphere.center = { playerPos.x,playerPos.y,0,0 };
	sphere.radius = 50;
}


void Player::Jump()
{
	
	if (jumpFlag == false) {
		if (Input::GetInstance()->TriggerKey(DIK_W))
		{
			jumpFlag = true;
			gFlag = false;
			jSpeed = 5;
			oldPos = playerPos;

		}
	}
	else if (jumpFlag == true) {
		if (gFlag == false) {
			if (playerPos.y >= oldPos.y - 250)
			{
				playerPos.y -= jSpeed;
				//jSpeed += 3;
			}
			if (playerPos.y <= oldPos.y - 250) { gFlag = true; }
		}
		else if (gFlag == true) {
			playerPos.y += jSpeed;
			//if (playerPos.y <= oldPos.y - 200)
			//{
			//	
			//	//jSpeed += 3;
			//}
			if (playerPos.y <= oldPos.y) { jumpFlag = false; playerPos.y = oldPos.y; }
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
	for (int i = 0; i < 5; i++) {
		pHP[i]->SetPosition({ playerPos.x-70+i*30,playerPos.y-70 });
	}
}




void Player::Attack()
{
	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	bulletTime += 0.3f;
	bulletCircle.radius = 10;
	bulletCircle.center = newBullet->GetPlayerBulletPos();
	AudioFlag = false;
	if (bulletTime >= maxBulletTime)
	{
		oldPosition = playerPos;
		
		const float kBulletSpeed = 3.0f;

		if (isRight == false)
		{
			velocity = { -kBulletSpeed, 0 };
		}
		else {
			velocity = { kBulletSpeed, 0 };
		}
		
		newBullet->Initialize();
		newBullet->Init(oldPosition, velocity);
		bulletCircle.center = newBullet->GetPlayerBulletPos();

		//’e‚ð“o˜^‚·‚é
		bullets_.push_back(std::move(newBullet));

		bulletTime = 0;
		AudioFlag = true;
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
	for (int i = 0; i < HP; i++) {
		pHP[i]->Draw();
	}

}

void Player::OnCollisionCall()
{
	HP -= 1;
}

