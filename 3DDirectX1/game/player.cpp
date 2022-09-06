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
	/*Sprite::LoadTexture(1, L"Resources/back.png");
	spPlayer = Sprite::CreateSprite(1, { 0,0 });*/
}

void Player::Init()
{
	
}


void Player::Move()
{
	if (Input::GetInstance()->PushKey(DIK_W))
	{
		position.y += 1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_S))
	{
		position.y -= 1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_D))
	{
		position.x += 1.0f;
	}
	if (Input::GetInstance()->PushKey(DIK_A))
	{
		position.x -= 1.0f;
	}
}

void Player::Ball()
{

}

void Player::Jump()
{
	if (Input::GetInstance()->PushKey(DIK_SPACE) && jumpFlag == false)
	{
		jumpFlag = true;
	}

	if (jumpFlag)
	{
		position.y += gravity / 60.0f;
		if (position.y >= 4)
		{
			gravityFlag = true;
		}
	}

	if (gravityFlag)
	{
		jumpFlag = false;
		position.y -= gravity / 60.0f;

		if (position.y < 0)
		{
			gravityFlag = false;
		}
	}
}

void Player::Update()
{
	
}


void Player::Draw()
{
	//spPlayer->Draw();
	
}