#include "Enemy.h"
#include<time.h>
#include"Input.h"

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
	Sprite::LoadTexture(6, L"Resources/animal_harinezumi.png");
	golf = Sprite::CreateSprite(6, GolfPos);
	Sprite::LoadTexture(10, L"Resources/card_joker.png");
	for (int i = 0; i < 9; i++)
	{
		spCard[i] = Sprite::CreateSprite(10, dropPos[i]);
	}


}

void Enemy::Init()
{
	circle.center = pigPos;
	AttackNo = rand() % 2;
	circle.radius = 10;
	srand(time(NULL));
}

void Enemy::Update()
{
	spEnemy->SetSize({ 200, 200 });
	for (int i = 0; i < 9; i++)
	{
		spCard[i]->SetSize({ 91, 133 });
	}
	switch (AttackNo)
	{
	case 0:
		Roll();
		break;
	case 1:
		DropRand();
		Drop();
		break;
	}

	Golf();

	circle.center = pigPos;
	circle.radius = 60;
}

void Enemy::Move()
{
}

void Enemy::Golf()
{
	if (Input::GetInstance()->TriggerKey(DIK_B)) {

		Mflag = true;
		v2 = { 0.0f,0.0f };
		g = 9.8f / 60.0f;
		v2.x = v * cos(60 * PI / 180.0);
		v2.y = v * sin(60 * PI / 180.0);
		easeTimer = 0;
		GolfPos = { 800,400 };
	}


	if (Mflag) {

		if (GolfPos.y <= 500) {
			GolfPos.x -= v2.x;
			GolfPos.y -= v2.y;

			v2.y = -g + v2.y;
			g = k * v / m;
		}
		if (GolfPos.y > 500) {
			//Mflag = false;
			
			if (easeTimer < 0.2) {
				easeTimer += 0.1 / 60;
			}
			GolfPos = eas->ease(GolfPos, { 0,GolfPos.y }, easeTimer, 0.2, 5);

		}
	}
	golf->SetSize({200,200});
	golf->SetPosition(GolfPos);
}

void Enemy::Roll()
{
	if (pigPos.x > 0) {
		pigPos.x -= 10;
		pigRot -= 30;
	}
	else {
		pigPos.x = 2000;
		AttackNo = rand() % 2;
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
	for (int i = 0; i < 9; i++)
	{
		if (dropFlag)
		{
			gravity += 9.8f / 60.0f;
			dropPos[i].y += gravity;
			if (dropPos[i].y >= 730)
			{
				AttackNo = rand() % 2;
				dropFlag = false;
				randFlag = false;
				gravity = 0;
			}
		}

		if (endTime >= 50)
		{
			timer = 0;
			dropFlag = false;
			AttackNo = rand() % 2;

		}

		spCard[i]->SetPosition(dropPos[i]);
	}
}

void Enemy::DropRand()
{
	for (int i = 0; i < 9; i++)
	{
		if (randFlag)
		{
			endTime += 0.05;

			for (int i = 0; i < 9; i++)
			{
				dropPos[i].x = lane[i];

				if (dropRand <= i)
				{
					dropPos[i].x = lane[i + 1];
				}
			}

			if (endTime >= 50)
			{

				endTime = 0;
				dropFlag = true;
			}

		}
		else {
			dropPos[i].y = 0;
			timer += 0.05;
			if (timer >= 50.0f)
			{
				randFlag = true;
				dropRand = rand() % 10;
				timer = 0;
			}
		}

		spCard[i]->SetPosition(dropPos[i]);
	}
}

void Enemy::Attack()
{
}

void Enemy::Draw()
{
	spEnemy->Draw();
	if (AttackNo == 1 && randFlag) {
		for (int i = 0; i < 9; i++)
		{
			spCard[i]->Draw();
		}
	}
	if (AttackNo == 0) {
		pig->Draw();
	}
	golf->Draw();
}
