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
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	spEnemy->SetSize({ 200, 200 });
}

void Enemy::Move()
{
}

void Enemy::Golf()
{
}

void Enemy::Roll()
{
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
}
