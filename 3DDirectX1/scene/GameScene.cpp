﻿#include "GameScene.h"
#include <cassert>
#include<sstream>
#include<iomanip>
#include "FbxLoader.h"
#include "FbxObject.h"
#include"input.h"
#include"DebugText.h"
#include"CollisionManager.h"
#include"TouchableObject.h"
#include"MeshCollider.h"
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(object3d);
	safe_delete(object3d2);
	safe_delete(object3d3);
	safe_delete(object3d4);
	safe_delete(model);
	safe_delete(model2);
	safe_delete(model3);
	safe_delete(model4);
	safe_delete(sprite);
	safe_delete(particleMan);
	safe_delete(lightGroup);
}

void GameScene::Initialize(DXCommon* dxCommon, Audio* audio)
{
	//u
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);
	FbxObject3d::SetDev(dxCommon->Getdev());
	//ライト生成
	lightGroup = LightGroup::Create();

	Object3d::SetLight(lightGroup);

	// 3Dオブエクトにライトをセット
	// 
	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);
	lightGroup->SetDirLightDir(0, XMVECTOR{ 0,0,1,0 });
	lightGroup->SetDirLightDir(1, XMVECTOR{ 0,-1,0,0 });
	lightGroup->SetDirLightDir(2, XMVECTOR{ 1,0,0,0 });
	//lightGroup->SetPointLightActive(0, true);
	//lightGroup->SetSpotLightActive(0, true);
	lightGroup->SetCircleShadowActive(0, false);

	FbxObject3d::SetCamera(camera);
	FbxObject3d::CreateGraphicsPipeline(L"Resources/shaders/FBXPS.hlsl", L"Resources/shaders/FBXVS.hlsl");
	colMan=CollisionManager::GetInstance();
	// パーティクルマネージャ生成
	particleMan = ParticleManager::Create(dxCommon->Getdev(), camera);

	model3 = Model::Create("skydome", true);
	model4 = Model::Create("ground", false);
	object3d3 = Object3d::Create(model3);
	object3d4 = Object3d::Create(model4);
	model = Model::Create("bullet", false);
	model2 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	object3d = Object3d::Create(model);
	object3d2 = new FbxObject3d();
	object3d2->Initialize();
	object3d2->SetModel(model2);


	//Createの後に書かないとclient.hのInternalRelease()でエラーが起こる
	object3d->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	object3d3->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");
	object3d4->CreateGraphicsPipeline(L"Resources/shaders/OBJPS.hlsl", L"Resources/shaders/OBJVS.hlsl");

	object3d2->SetRotation({ 0,45,0 });

	//object3d->Update();

	//object3d2->Update();

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	DebugText::GetInstance()->Initialize(debugTextTexNumber);

	Sprite::LoadTexture(1, L"Resources/Back_ground.png");
	Sprite::LoadTexture(40, L"Resources/title.png");
	title = Sprite::CreateSprite(40, { 0,0 });
	Sprite::LoadTexture(41, L"Resources/gameover.png");
	gameover = Sprite::CreateSprite(41, { 0,0 });
	Sprite::LoadTexture(42, L"Resources/clear.png");
	clear = Sprite::CreateSprite(42, { 0,0 });

	sprite = Sprite::CreateSprite(1, { 0,0 });


	sound1 = Audio::SoundLoadWave("Resources/Sound/ゲージ回復2.wav");
	sound2 = Audio::SoundLoadWave("Resources/Sound/picopiconostalgie.wav");


	//audio->SetBGMVolume(0.5f);
	// カメラ注視点をセット
	camera->SetTarget({ 0, 0.0f, 0 });
	camera->SetEye({ 0, 0, -10 });
	player = new Player;//newすればエラー吐かない
	player->Initialize();
	player->Init();

	enemy = new Enemy;//newすればエラー吐かない
	enemy->Initialize();
	enemy->Init();
	mapchip = new MapChip;//newすればエラー吐かない
	mapchip->Initialize();
	audio->SoundPlayWave(sound2);
}

void GameScene::Init()
{
	for (int i = 0; i < 6; i++)
	{
		HitDrop[i] = false;
	}

	for (int i = 0; i < 2; i++)
	{
		HitGrow[i] = false;
	}
	HitGolf = false;
	HitRoll = false;
}

void GameScene::Update()
{

	if (Input::GetInstance()->TriggerKey(DIK_SPACE))
	{
		SceneNo = GAME;
	}
	//光線方向初期値                  上奥
	//static XMVECTOR lightDir = { 0, 4, 0, 0 };

	if (SceneNo == GAME)
	{
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) || Input::GetInstance()->IsButtonDown(ButtonA)) {
			object3d2->PlayAnimation();
		}

		lightGroup->SetCircleShadowDir(0, XMVECTOR({ 0,-1,0,0 }));
		lightGroup->SetCircleShadowCasterPos(0, { 0,0,0 });
		lightGroup->SetCircleShadowAtten(0, XMFLOAT3(0.5, 0.6, 0));
		lightGroup->SetCircleShadowFactorAngle(0, XMFLOAT2(0, 0.5));



		//object3d->SetRotation({ a,0,b });
		//TouchableObjectのobjは	playerの前に書かないとエラー起こるよ


		//player->SetTsize(Tsize);
		player->Update();
		enemy->Update();
		//camera->FollowCamera({0,0,0}, XMFLOAT3{0,2,-distance}, 0, 0);

		
	for (int i = 0; i < 6; i++)
	{
		HitDrop[i] = Collision::CheckCircle2Circle(player->GetCircle(), enemy->GetDropCircle(i));
		if (HitDrop[i] && enemy->isDropHit[i] == true) {
			enemy->isDropHit[i] = false;
			player->OnCollisionCall();
			//DebugText::GetInstance()->Printf(100, 260, 3.0f, "Hit");
		}
	}
	
	for (int i = 0; i < 2; i++)
	{
		HitGrow[i] = Collision::CheckCircle2Circle(player->GetCircle(), enemy->GetGrowCircle(i));
		if (HitGrow[i] && enemy->isGrowHit[i] == true) {
			enemy->isGrowHit[i] = false;
			player->OnCollisionCall();
			
		}
		if(HitGrow[i] == false)
		{
			enemy->isGrowHit[i] = true;
		}
	}

	HitGolf = Collision::CheckCircle2Circle(player->GetCircle(), enemy->GetGolfCircle());
	if (HitGolf && enemy->isGolfHit == true) {
		enemy->isGolfHit = false;
		player->OnCollisionCall();
	}
	if (HitGolf == false)
	{
		enemy->isGolfHit = true;
	}

	

	HitRoll = Collision::CheckCircle2Circle(player->GetCircle(), enemy->GetCircle());
	if (HitRoll && enemy->isRollHit == true) {
		enemy->isRollHit = false;
		player->OnCollisionCall();
		
		DebugText::GetInstance()->Printf(100, 100, 3.0f, "Hit");
	}
	if (HitRoll == false)
	{
		enemy->isRollHit = true;
	}

#pragma endregion
#pragma region 音
		if (player->GetAudioFlag() == true) {
			audio->SEPlayWave(sound1);
		}
#pragma endregion
		particleMan->Update();
		object3d2->SetPosition(playerPosition);
		object3d2->SetRotation({ 0,90,0 });

		object3d2->Update();


		lightGroup->Update();

		colMan->CheckAllCollisions();

		newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize();
		newBullet->Init(player->GetOldPos(), player->GetVelocity());
		CheckAllCollision();
		playerBullet.push_back(std::move(newBullet));
		for (std::unique_ptr<PlayerBullet>& bullet : playerBullet)
		{
			bullet->Update();
		}
	}
}

void GameScene::DrawBG()
{
	//背景
	sprite->PreDraw(dxCommon->GetCmdList());
	sprite->Draw();
	sprite->PostDraw();
	dxCommon->ClearDepthBuffer();
	colMan->CheckAllCollisions();
}

void GameScene::Draw()
{
	Object3d::PreDraw(dxCommon->GetCmdList());
	FbxObject3d::PreDraw(dxCommon->GetCmdList());


	//object3d->Draw();
	//object3d2->Draw();
	//player->Draw();


	Object3d::PostDraw();
	FbxObject3d::PostDraw();

}
void GameScene::DrawFront()
{
	//前景
	sprite->PreDraw(dxCommon->GetCmdList());
	if (SceneNo == TITLE)
	{
		title->Draw();
	}
	else if (SceneNo == GAME)
	{
		//sprite->Draw();
		mapchip->Draw();
		enemy->Draw();
		player->DrawSprite();
	}
	else if (SceneNo == CLEAR)
	{
		clear->Draw();
	}
	else if (SceneNo == END)
	{
		gameover->Draw();
	}
	
	
	DebugText::GetInstance()->Printf(100, 20, 3.0f, "%f", enemy->GetEaseTimer());
	//DebugText::GetInstance()->Printf(100, 80, 3.0f, "%d", Alive[1]);
	//DebugText::GetInstance()->Printf(100,100, 3.0f, "WASD:MOVE");
	//DebugText::GetInstance()->Printf(100, 140, 2.0f, "0 : %f %f", enemy->GetCircle().center.x, enemy->GetCircle().center.y);
	//DebugText::GetInstance()->Printf(100, 165, 2.0f, "1 : %f %f", enemy->GetDropCircle(0).center.x, enemy->GetDropCircle(0).center.y);
	//DebugText::GetInstance()->Printf(100, 205, 2.0f, "1 : %f %f", enemy->GetDropCircle(1).center.x, enemy->GetDropCircle(1).center.y);
	//DebugText::GetInstance()->Printf(100, 225, 2.0f, "1 : %f %f", enemy->GetDropCircle(2).center.x, enemy->GetDropCircle(2).center.y);
	//DebugText::GetInstance()->Printf(100, 245, 2.0f, "1 : %f %f", enemy->GetDropCircle(3).center.x, enemy->GetDropCircle(3).center.y);
	//DebugText::GetInstance()->Printf(100, 265, 2.0f, "1 : %f %f", enemy->GetDropCircle(4).center.x, enemy->GetDropCircle(4).center.y);
	//DebugText::GetInstance()->Printf(100, 285, 2.0f, "1 : %f %f", enemy->GetDropCircle(5).center.x, enemy->GetDropCircle(5).center.y);
	//DebugText::GetInstance()->Printf(100, 305, 2.0f, "2 : %f %f", enemy->GetGolfCircle().center.x, enemy->GetGolfCircle().center.y);
	DebugText::GetInstance()->Printf(100, 325, 2.0f, "2 : %f %f", enemy->GetGolfCircle().center.x, enemy->GetGolfCircle().center.y);
	DebugText::GetInstance()->Printf(100, 355, 2.0f, "2 : %f %f", enemy->GetGolfCircle().center.x, enemy->GetGolfCircle().center.y);
	DebugText::GetInstance()->Printf(100, 255, 2.0f, "pos : %f %f", enemy->GetGrowPos().x, enemy->GetGrowPos().y);
	//DebugText::GetInstance()->Printf(100, 295, 2.0f, "pos : %f %f", enemy->GetGrowPos2().x, enemy->GetGrowPos2().y);
	DebugText::GetInstance()->Printf(100, 400, 3.0f, "playerHP : %d", player->GetHP());
	DebugText::GetInstance()->Printf(100, 460, 3.0f, "enemyHP : %d", enemy->GetHP());

	DebugText::GetInstance()->DrawAll(dxCommon->GetCmdList());
	sprite->PostDraw();
}
void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}

void GameScene::CheckAllCollision()
{
	XMFLOAT2 posA_1, posA_2, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullets();

	posA_1 = enemy->GetPosition();
	posA_2 = enemy->GetPosition();

	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets)
	{
		posB = bullet->GetPlayerBulletPos();

		float enemyBulletX = (posA_1.x + 100) - posB.x;
		float enemyBulletY = (posA_1.y - 100) - posB.y;
		float enemyBullet = sqrtf(pow(enemyBulletX, 2) + pow(enemyBulletY, 2));
		if (enemyBullet <= 180 + 8 && bullet->GetIsAlive() == false)
		{
			HitFlag = true;
			enemy->OnCollision();
			bullet->OnCollision();
			//DebugText::GetInstance()->Printf(100, 380, 3.0f, "Hit");
		}

		float enemy2BulletX = (posA_2.x + 100) - posB.x;
		float enemy2BulletY = (posA_2.y + 100) - posB.y;
		float enemy2Bullet = sqrtf(pow(enemy2BulletX, 2) + pow(enemy2BulletY, 2));
		//DebugText::GetInstance()->Printf(100, 300, 3.0f, "%f : 263", enemy2Bullet);
		//DebugText::GetInstance()->Printf(100, 340, 2.5f, "en : %f %f pb : %f %f", posA.x, posA.y, posB.x, posB.y);
		if (enemy2Bullet <= 200 + 8 && bullet->GetIsAlive() == false)
		{
			HitFlag = true;
			bullet->OnCollision();
			//DebugText::GetInstance()->Printf(100, 380, 3.0f, "Hit");
		}

		if (HitFlag)
		{
			enemy->OnCollision();

			HitFlag = false;
		}

		
	}
}
