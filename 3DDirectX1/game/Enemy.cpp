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
	pig = Sprite::CreateSprite(5,  pigPos);
}

void Enemy::Init()
{
	circle.center = pigPos;
	circle.radius = 3;
}

void Enemy::Update()
{
	spEnemy->SetSize({ 200, 200 });
	Roll();
	circle.center = pigPos;
	circle.radius = 3;
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
}

void Enemy::Attack()
{
}

void Enemy::Draw()
{
	spEnemy->Draw();
	pig->Draw();
}
