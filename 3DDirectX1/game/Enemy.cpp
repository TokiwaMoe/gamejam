#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	Sprite::LoadTexture(4, L"Resources/fantasy_maou_devil.png");
	spEnemy = Sprite::CreateSprite(4, { 700,500 });
	Sprite::LoadTexture(5, L"Resources/animal_pig_buta.png");
	pig = Sprite::CreateSprite(5, pigPos);
	Sprite::LoadTexture(10, L"Resources/card_joker.png");
	for (int i = 0; i < 9; i++)
	{
		spCard[i] = Sprite::CreateSprite(10, dropPos[i]);
	}
	
	
}

void Enemy::Init()
{
	circle.center = pigPos;
	circle.radius = 10;
}

void Enemy::Update()
{
	spEnemy->SetSize({ 200, 200 });
	for (int i = 0; i < 9; i++)
	{
		spCard[i]->SetSize({91, 133});
	}
	
	Roll();
	Drop();

	circle.center = pigPos;
	circle.radius = 60;
}

void Enemy::Move()
{
}

void Enemy::Golf()
{
}

void Enemy::Roll()
{
	if (pigPos.x > 0) {
		pigPos.x -= 10;
		pigRot -= 30;
	}
	else {
		pigPos.x = 2000;
	}
	pig->SetSize({ 100, 100 });
	pig->SetAnchorPoint({ 0.5,0.5 });
	pig->SetPosition(pigPos);
	pig->SetRotation(pigRot);
}

void Enemy::Grow()
{
}

void Enemy::Drop()
{
	if (dropFlag)
	{
		dropRand = rand() % 10;
		for (int i = 0; i < 9; i++)
		{
			dropPos[i].x = lane[i];

			if (dropRand <= i)
			{
				dropPos[i].x = lane[i + 1];
			}
			spCard[i]->SetPosition(dropPos[i]);
		}
		time = 0;
	}
	else {
		time += 0.5;
		if (time >= 50.0f)
		{
			dropFlag = true;
		}
	}

	
	
}

void Enemy::Attack()
{
}

void Enemy::Draw()
{
	spEnemy->Draw();
	for (int i = 0; i < 9; i++)
	{
		spCard[i]->Draw();
	}
	pig->Draw();
}
