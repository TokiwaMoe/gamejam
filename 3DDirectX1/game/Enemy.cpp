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
	Sprite::LoadTexture(4, L"Resources/stay.png");
	spEnemy = Sprite::CreateSprite(4, position);
	spEnemy->SetAnchorPoint({ 0.5,0.5 });
	spEnemy->SetSize({ 400,400 });
	Sprite::LoadTexture(5, L"Resources/pig.png");
	pig = Sprite::CreateSprite(5, pigPos);
	Sprite::LoadTexture(6, L"Resources/hedgehog/golf.png");
	golf = Sprite::CreateSprite(6, GolfPos);
	golf->SetAnchorPoint({ 0.5, 0.5 });
	Sprite::LoadTexture(7, L"Resources/golf.png");
	enGolf = Sprite::CreateSprite(7, position);
	enGolf->SetTextureRect({ 0,0 }, { 96,96 });
	enGolf->SetAnchorPoint({ 0.5,0.5 });
	enGolf->SetSize({ 400, 400 });
	Sprite::LoadTexture(10, L"Resources/card/JOKER.png");
	Sprite::LoadTexture(11, L"Resources/card/heart.png");
	Sprite::LoadTexture(12, L"Resources/card/dia.png");
	Sprite::LoadTexture(13, L"Resources/card/card_hedgehog.png");
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 5)
		{
			spCard[i] = Sprite::CreateSprite(11, {0, 730});
		}
		else if (i == 1 || i == 3)
		{
			spCard[i] = Sprite::CreateSprite(12, { 0, 730 });
		}
		else if (i == 2)
		{
			spCard[i] = Sprite::CreateSprite(10, { 0, 730 });
		}
		else if (i == 4)
		{
			spCard[i] = Sprite::CreateSprite(13, { 0, 730 });
		}
		spCard[i]->SetSize({ 91, 133 });
	}

	Sprite::LoadTexture(14, L"Resources/flower/flower_1.png");
	spGrow_Y = Sprite::CreateSprite(14, { -10, 730 });
	spGrow_Y->SetTextureRect({ 0,0 }, { 144,144 });
	spGrow_Y->SetSize({ 400, 400 });
	spGrow_Y->SetRotation(70);

	Sprite::LoadTexture(15, L"Resources/flower/flower_2.png");
	spGrow_X = Sprite::CreateSprite(15, { -10, 730 });
	spGrow_X->SetTextureRect({ 0,0 }, { 144,144 });
	spGrow_X->SetSize({ 400, 400 });

	Sprite::LoadTexture(16, L"Resources/hedgehog/hedgehog.png");
	backGolf = Sprite::CreateSprite(16, GolfPos);
	backGolf->SetTextureRect({ 0,0 }, {100, 64});
	backGolf->SetSize({ 200, 128 });
	Sprite::LoadTexture(17, L"Resources/EnemyHPFrame.png");
	EHPFrame = Sprite::CreateSprite(17, { 100, -10 });
	EHPFrame->SetSize({ 1010,100 });
	Sprite::LoadTexture(18, L"Resources/white1x1.png");
	EHP = Sprite::CreateSprite(18, { 160, 20 });
	//EHP->SetSize(HPSize);
	EHP->SetColor({ 0, 1, 0, 1 });

	Sprite::LoadTexture(19, L"Resources/buta.png");
	enRoll = Sprite::CreateSprite(19, position);
	enRoll->SetTextureRect({ 0,0 }, { 96,96 });
	enRoll->SetAnchorPoint({ 0.5,0.5 });
	enRoll->SetSize({ 400, 400 });

	Sprite::LoadTexture(60, L"Resources/ono.png");
	enGrow = Sprite::CreateSprite(60, position);
	enGrow->SetTextureRect({ 0,0 }, { 96,96 });
	enGrow->SetAnchorPoint({ 0.5,0.5 });
	enGrow->SetSize({ 400, 400 });
}

void Enemy::Init()
{
	circle.center = pigPos;
	circle.radius = 50;
	isRollHit = true;
	for (int i = 0; i < 6; i++)
	{
		dropCircle[i].center = { dropPos[i].x + 45, dropPos[i].y + 66 };
		dropCircle[i].radius = 60;
		isDropHit[i] = true;

	}
	for (int i = 0; i < 2; i++)
	{
		growCircle[0].center = { growPos.x + 200, growPos.y + 200 };
		growCircle[1].center = { growPos2.x + 200, growPos2.y + 200 };
		growCircle[i].radius = 100;
		isGrowHit[i] = true;
	}
	golfCircle.center = { GolfPos.x + 100, GolfPos.y };
	golfCircle.radius = 50;
	//isGolfHit = true;

	enemyCircle.center = position;
	enemyCircle.radius = 200;
	srand(time(NULL));
	AttackNo = 1;
	//AttackNo = rand() % 4;
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
	//isRollHit = true;
	for (int i = 0; i < 6; i++)
	{
		dropCircle[i].center = { dropPos[i].x + 45, dropPos[i].y + 66 };
		dropCircle[i].radius = 45;
		//isDropHit[i] = true;

	}
	for (int i = 0; i < 2; i++)
	{
		growCircle[0].center = { growPos.x - 100, growPos.y + 200 };
		growCircle[1].center = { growPos2.x + 200, growPos2.y + 200 };
		growCircle[0].radius = 100;
		growCircle[1].radius = 100;
		//isGrowHit[i] = true;
	}
	golfCircle.center = { GolfPos.x + 100, GolfPos.y };
	golfCircle.radius = 30;
	//isGolfHit = true;
	enemyCircle.center = position;
	enemyCircle.radius = 200;

	spEnemy->SetAnchorPoint({ 0.5,0.5 });
	spEnemy->SetSize({ 400,400 });
	EHP->SetSize(HPSize);
}

void Enemy::Move()
{
}

void Enemy::Golf()
{
	//isGolfHit = true;
	stayFlag = false;
	enGolfAnime += 1.0f;

	if (enGolfAnime >= 8)
	{
		enGolfNo++;
		enGolfAnime = 0;

		if (enGolfNo == 5)
		{
			GolfFlag = true;
			easeTimer = 0;
		}

		if (enGolfNo >= 6)
		{
			stayFlag = true;
			enGolfNo = 7;
			enGolfAnime = 9;
		}
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
				isBackAnime = false;
				GolfPos = { 1000,350 };
				//AttackNo = 2;
				AttackNo = rand() % 4;
				enGolfNo = 0;
				enGolfAnime = 0;
			}
		}
		else
		{
			isBackAnime = false;
			easeTimer += 0.1f;
			GolfPos = eas->easeOut_Bounce({ 1100,450 }, { 0,560 }, easeTimer);
		}
	}
	golf->SetSize({ 100,100 });
	golf->SetPosition(GolfPos);
	backGolf->SetTextureRect({ 100 * backNo,0 }, { 100,64 });
	backGolf->SetSize({ 128, 128 });
	backGolf->SetPosition(GolfPos);

	enGolf->SetTextureRect({ 96 * enGolfNo,0 }, { 96,96 });
	enGolf->SetPosition(position);
}

void Enemy::Roll()
{
	stayFlag = false;
	enRollAnime += 0.5f;

	if (enRollAnime >= 8)
	{
		enRollNo++;
		enRollAnime = 0;

		if (enRollNo == 3)
		{
			isRoll = true;
		}

		if (enRollNo >= 7)
		{
			enRollNo = 8;
			enRollAnime = 9;
			stayFlag = true;
			
		}
	}

	if (isRoll)
	{
		if (pigPos.x > 0) {
			pigPos.x -= 10;
			pigRot -= 30;
		}
		else {
			pigPos.x = 2000;
			//AttackNo = 0;
			pigRot = 0;
			isRoll = false;
			enRollAnime = 0;
			enRollNo = 0;
			AttackNo = rand() % 4;
		}
	}
	
	//isRollHit = true;
	
	pig->SetSize({ 100, 100 });
	pig->SetAnchorPoint({ 0.5,0.5 });
	pig->SetPosition(pigPos);
	pig->SetRotation(pigRot);
	enRoll->SetTextureRect({ 96 * enRollNo,0 }, { 96,96 });
	enRoll->SetAnchorPoint({ 0.5,0.5 });
	enRoll->SetSize({ 400, 400 });

}

void Enemy::Grow()
{
	stayFlag = false;
	enGrowAnime += 1.0f;

	if (enGrowAnime >= 8)
	{
		enGrowNo++;
		enGrowAnime = 0;

		if (enGrowNo >= 4)
		{
			enGrowNo = 4;
			enGrowAnime = 9;
			//stayFlag = true;
			growFlag = true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		//isGrowHit[i] = true;
		if (AttackNo == 3 && growFlag == false) {
			growRandFlag = true;
		}

		if (growRandFlag)
		{
			growRandY = rand() % 3;
			growRandX = rand() % 3;
			growPos = { -13, growPosY[growRandY] };
			growPos2 = { growPosX[growRandX], 730 };
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
					stayFlag = true;
					growFlag = false;
					behindTime = 0;
					growTime = 0;
					//AttackNo = 3;
					enGrowNo = 0;
					enGrowAnime = 0;
					AttackNo = rand() % 4;
					growPos = { 0, 730 };
					growPos2 = { 0, 730 };
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
	enGrow->SetTextureRect({ 96 * enGrowNo,0 }, { 96,96 });
	enGrow->SetAnchorPoint({ 0.5,0.5 });
	enGrow->SetSize({ 400, 400 });
}

void Enemy::Drop()
{
	for (int i = 0; i < 6; i++)
	{
		//isDropHit[i] = true;
		if (dropFlag)
		{
			gravity += 9.8f / 60.0f;
			dropPos[i].y += gravity;
			if (dropPos[i].y >= 730)
			{
				//AttackNo = 2;
				isDropHit[i] = true;
				AttackNo = rand() % 4;
				dropPos[i] = { 60,730 };
				dropFlag = false;
				randFlag = false;
				gravity = 0;
			}
		}

		if (endTime >= 50)
		{
			timer = 0;
			dropFlag = false;
			AttackNo = 1;
			//AttackNo = rand() % 4;

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
			dropPos[i].y = 60;
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

void Enemy::OnCollision()
{
	HP -= 1;
	HPSize.x -= 6;
	EHP->SetSize(HPSize);
	if (HP <= 0)
	{
		isAlive = true;
	}
}

void Enemy::Draw()
{
	if (stayFlag)
	{
		spEnemy->Draw();
	}
	
	if (AttackNo == 1 && randFlag) {
		for (int i = 0; i < 6; i++)
		{
			spCard[i]->Draw();
		}
	}
	if (AttackNo == 0) {
		
		if (stayFlag == false)
		{
			enRoll->Draw();
		}
		pig->Draw();
	}
	if (AttackNo == 2) {
		if (stayFlag == false)
		{
			enGolf->Draw();
		}
		
		if (isBackAnime)
		{
			backGolf->Draw();
		}
		else
		{
			if (GolfFlag)
			{
				golf->Draw();
			}
			
		}
		
	}
	if (AttackNo == 3)
	{
		if (stayFlag == false)
		{
			enGrow->Draw();
		}
		spGrow_Y->Draw();
		spGrow_X->Draw();
	}
	
	EHP->Draw();
	EHPFrame->Draw();
}