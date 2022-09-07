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
	Sprite::LoadTexture(2, L"Resources/character2.png");
	//Sprite::LoadTexture(3, L"Resources/UI/sizeUI.png");
	playerSprite = Sprite::CreateSprite(2, { 0,100 });
	//sizeSprite = Sprite::CreateSprite(3, { 100,100 });


}

void Player::Init()
{
	circle.center = playerPos;
	circle.radius = 5;
	playerPos={ 50,100 };

}


void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		playerPos.x += 2;
		playerFlag = false;
	}
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		playerPos.x -= 2;
		playerFlag = true;
	}
	if (Input::GetInstance()->PushKey(DIK_W))
	{
		playerPos.y -= 2;
		playerFlag = false;
	}
	if (Input::GetInstance()->PushKey(DIK_S))
	{
		playerPos.y += 2;
		playerFlag = false;
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
				playerPos.y-=jSpeed;
				jSpeed += g;
			}
			if (playerPos.y <= 50) { gFlag = true; }
		}
		else if (gFlag == true) {
			if (playerPos.y < 100) 
			{
				playerPos.y+=jSpeed;
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
	playerSprite->SetAnchorPoint({ 0.5, 0.5 });
	playerSprite->SetPosition(playerPos);
	playerSprite->SetIsFlipX(playerFlag);
}




void Player::Draw()
{

}

void Player::DrawSprite()
{
	playerSprite->Draw();

}
