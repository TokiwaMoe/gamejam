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
	Sprite::LoadTexture(11, L"Resources/flower_hachiue1_red.png");
	for (int i = 0; i < 3; i++)
	{
		spGrow[i] = Sprite::CreateSprite(11, growPos[i]);
	}


}

void Enemy::Init()
{
	circle.center = pigPos;
	circle.radius = 10;
	srand(time(NULL));
	//AttackNo = 2;
	AttackNo = rand() % 4;
	eas = new Eas();
	eas->Initialize();
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
	case 2:
		Golf();
		break;
	case 3:
		Grow();
		break;
	}

	

	circle.center = pigPos;
	circle.radius = 60;
	for (int i = 0; i < 9; i++)
	{
		dropCircle[i].center = dropPos[i];
		dropCircle[i].radius = 60;
	}
	for (int i = 0; i < 3; i++)
	{
		growCircle[i].center = growPos[i];
		growCircle[i].radius = 60;
	}
	golfCircle.center = GolfPos;
	golfCircle.radius = 60;
}

void Enemy::Move()
{
}

void Enemy::Golf()
{
	if (AttackNo == 2 && GolfFlag == false)
	{
		GolfFlag = true;
		easeTimer = 0;
	}

	if (GolfFlag)
	{
		easeTimer += 0.1f;
		GolfPos = eas->easeOut_Bounce({1000,200}, {0,450}, easeTimer);

		if (easeTimer >= eas->maxflame)
		{
			GolfFlag = false;
			AttackNo = 2;
			GolfPos = { 1000,200 };
			AttackNo = rand() % 4;
		}
	}
	golf->SetSize({ 100,100 });
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
		//AttackNo = 2;
		AttackNo = rand() % 4;
	}
	pig->SetSize({ 100, 100 });
	pig->SetAnchorPoint({ 0.5,0.5 });
	pig->SetPosition(pigPos);
	pig->SetRotation(pigRot);

}

void Enemy::Grow()
{
	if (AttackNo == 3 && growFlag == false) {
		growRandFlag = true;
	}

	if (growRandFlag)
	{
		growRandY = rand() % 3;
		growPos[0] = { growPosX[growRandX], growPosY[growRandY] };
		growFlag = true;
	}

	if (growFlag)
	{
		growRandFlag = false;
		if (20.0f <= growPos[0].x)
		{
			behindTime += 0.05f;
			growPos[0].x = 20.0f;
		}

		if (behindTime >= 10.0f)
		{
			growPos[0].x -= 0.05f;

			if (growPos[0].x <= 0.0f)
			{
				growFlag = false;
				behindTime = 0;
				growTime = 0;
				//AttackNo = 2;
				AttackNo = rand() % 4;
			}
		}
		else {
			growPos[0].x += 0.05f;
		}
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
				//AttackNo = 2;
				AttackNo = rand() % 4;
				dropFlag = false;
				randFlag = false;
				gravity = 0;
			}
		}

		if (endTime >= 50)
		{
			timer = 0;
			dropFlag = false;
			//AttackNo = 2;
			AttackNo = rand() % 4;

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
	if (AttackNo == 2) {
		golf->Draw();
	}
	for (int i = 0; i < 3; i++)
	{
		spGrow[0]->Draw();
	}

}

