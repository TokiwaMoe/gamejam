#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize()
{
	Sprite::LoadTexture(30, L"Resources/animal_flamingo.png");
	playerBulletSprite = Sprite::CreateSprite(30, { 0,100 });
	playerBulletSprite->SetSize({ 162.5f,200.0f });
}

void PlayerBullet::Init(XMFLOAT2 position, XMFLOAT2 speed)
{
	playerBulletPos = position;
	bulletSpeed = speed;
	playerBulletSprite->SetPosition(playerBulletPos);
}

void PlayerBullet::Update()
{
	playerBulletPos.x += bulletSpeed.x;
	playerBulletSprite->SetPosition(playerBulletPos);
}

void PlayerBullet::Draw()
{
	playerBulletSprite->Draw();
}
