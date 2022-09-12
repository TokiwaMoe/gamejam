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
	Sprite::LoadTexture(10, L"Resources/card/JOKER.png");
	Sprite::LoadTexture(11, L"Resources/card/heart.png");
	Sprite::LoadTexture(12, L"Resources/card/dia.png");
	Sprite::LoadTexture(13, L"Resources/card/card_hedgehog.png");
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 5)
		{
			spCard[i] = Sprite::CreateSprite(11, dropPos[i]);
		}
		else if (i == 1 || i == 3)
		{
			spCard[i] = Sprite::CreateSprite(12, dropPos[i]);
		}
		else if (i == 2)
		{
			spCard[i] = Sprite::CreateSprite(10, dropPos[i]);
		}
		else if (i == 4)
		{
			spCard[i] = Sprite::CreateSprite(13, dropPos[i]);
		}
		spCard[i]->SetSize({ 91, 133 });
	}

	Sprite::LoadTexture(14, L"Resources/flower/flower_1.png");
	spGrow_Y = Sprite::CreateSprite(14, growPos);
	spGrow_Y->SetTextureRect({ 0,0 }, { 144,144 });
	spGrow_Y->SetSize({ 400, 400 });
	spGrow_Y->SetRotation(70);

	Sprite::LoadTexture(15, L"Resources/flower/flower_2.png");
	spGrow_X = Sprite::CreateSprite(15, growPos);
	spGrow_X->SetTextureRect({ 0,0 }, { 144,144 });
	spGrow_X->SetSize({ 400, 400 });

	Sprite::LoadTexture(16, L"Resources/hedgehog/hedgehog.png");
	backGolf = Sprite::CreateSprite(16, GolfPos);
	backGolf->SetTextureRect({ 0,0 }, {100, 64});
	backGolf->SetSize({ 200, 128 });
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
	for (int i = 0; i < 6; i++)
	{
		dropCircle[i].center = dropPos[i];
		dropCircle[i].radius = 60;
	}
	for (int i = 0; i < 3; i++)
	{
		growCircle[i].center = growPos;
		growCircle[i].center = growPos2;
		growCircle[i].radius = 150;
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
		if (easeTimer >= eas->maxflame)
		{
			isBackAnime = true;
			GolfPos.x += 3.0f;

			//アニメーション
			backAnime += 1.5f;

			if (backAnime >= 8)
			{
				backNo++;
				backAnime = 0;

				if (backNo == 2)
				{
					backNo = 0;
				}
			}
			
			if (GolfPos.x >= 1300)
			{
				GolfFlag = false;
				GolfPos = { 1000,200 };
				AttackNo = rand() % 4;
			}
		}
		else
		{
			isBackAnime = false;
			easeTimer += 0.1f;
			GolfPos = eas->easeOut_Bounce({ 1000,200 }, { 0,450 }, easeTimer);
		}
	}
	golf->SetSize({ 100,100 });
	golf->SetPosition(GolfPos);
	backGolf->SetTextureRect({ 100 * backNo,0 }, { 100,64 });
	backGolf->SetSize({ 200, 128 });
	backGolf->SetPosition(GolfPos);
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
	for (int i = 0; i < 3; i++)
	{
		if (AttackNo == 3 && growFlag == false) {
			growRandFlag = true;
		}

		if (growRandFlag)
		{
			growRandY = rand() % 3;
			growRandX = rand() % 3;
			growPos = { 0, growPosY[growRandY] };
			growPos2 = { growPosX[growRandX], 720 };
			growFlag = true;
		}

		if (growFlag)
		{
			growRandFlag = false;
			if (300.0f <= growPos.x && growPos2.y <= 420.0f)
			{
				behindTime += 0.05f;
				growPos.x = 300.0f;
				growPos2.y = 420.0f;
			}

			if (behindTime >= 30.0f)
			{
				growPos.x -= 3.0f;
				growPos2.y += 3.0f;

				if (growPos.x <= 0.0f && growPos2.y >= 720.0f)
				{
					growFlag = false;
					behindTime = 0;
					growTime = 0;
					//AttackNo = 2;
					AttackNo = rand() % 4;
				}
			}
			else {
				growPos.x += 2.0f;
				growPos2.y -= 2.0f;
				
			}
		}

		spGrow_Y->SetPosition(growPos);
		spGrow_X->SetPosition(growPos2);
	}

	growAnimation += 0.5f;

	if (growAnimation >= 8)
	{
		growNo++;
		growAnimation = 0;

		if (growNo == 3)
		{
			growNo = 0;
		}
	}

	spGrow_X->SetTextureRect({ 144 * growNo,0 }, { 144,144 });
	spGrow_Y->SetTextureRect({ 144 * growNo,0 }, { 144,144 });
}

void Enemy::Drop()
{
	for (int i = 0; i < 6; i++)
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
	for (int i = 0; i < 6; i++)
	{
		if (randFlag)
		{
			endTime += 0.05;

			for (int i = 0; i < 7; i++)
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
				dropRand = rand() % 7;
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
		for (int i = 0; i < 6; i++)
		{
			spCard[i]->Draw();
		}
	}
	if (AttackNo == 0) {
		pig->Draw();
	}
	if (AttackNo == 2) {
		if (isBackAnime)
		{
			backGolf->Draw();
		}
		else
		{
			golf->Draw();
		}
		
	}
	for (int i = 0; i < 3; i++)
	{
		if (AttackNo == 3)
		{
			spGrow_Y->Draw();
			spGrow_X->Draw();
		}
	}
	
}

