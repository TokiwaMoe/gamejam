#include "Enemy.h"
#include<time.h>

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
	Sprite::LoadTexture(11, L"Resources/flower_hachiue1_red.png");
	for (int i = 0; i < 3; i++)
	{
		spGrow[i]= Sprite::CreateSprite(11, growPos[i]);
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

	Grow();

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
		AttackNo = rand() % 2;
	}
	pig->SetSize({ 100, 100 });
	pig->SetAnchorPoint({ 0.5,0.5 });
	pig->SetPosition(pigPos);
	pig->SetRotation(pigRot);

}

void Enemy::Grow()
{
	

	if (growTime >= 50)
	{
		growFlag = true;
		growRandX = rand() % 4;

		if (growRandX == 1 || growRandX == 2)
		{
			growRandY = rand() % 2;
		}
		else if (growRandX == 0 || growRandX == 3)
		{
			growRandY = rand() % 3;
		}
		
	}

	if (growFlag)
	{
		growPos[0] = { growPosX[growRandX], growPosY[growRandY] };
		growTime = 0;
		growFlag = false;
	}
	else {
		growTime += 0.05f;
	}

	spGrow[0]->SetPosition(growPos[0]);
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
	
	for (int i = 0; i < 3; i++)
	{
		spGrow[i]->Draw();
	}
}
