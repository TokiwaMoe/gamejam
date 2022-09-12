#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize()
{
	Sprite::LoadTexture(30, L"Resources/bullet.png");
	playerBulletSprite = Sprite::CreateSprite(30, { 0,100 });
	playerBulletSprite->SetSize({ 16.0f,16.0f });
}

void PlayerBullet::Init(XMFLOAT2 position, XMFLOAT2 speed)
{
	playerBulletPos = { position.x + 15.0f,  position.y + 7.0f };
	bulletSpeed = speed;
	playerBulletSprite->SetPosition(playerBulletPos);
}

void PlayerBullet::Update()
{
	playerBulletPos.x += bulletSpeed.x;
	playerBulletSprite->SetPosition(playerBulletPos);
	playerBulletSprite->SetAnchorPoint({ 0.5, 0.5 });
}

void PlayerBullet::Draw()
{
	playerBulletSprite->Draw();
}
