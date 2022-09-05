#include "NMGame.h"

void NMGame::Initialize()
{
	Framework::Initialize();
	//�Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(dxcommon, audio);

}

void NMGame::Update()
{
	Framework::Update();
	if (Input::GetInstance()->TriggerKey(DIK_1)/*������Getter����������*/) {
		postEffect->CreateGraphicsPipeline(L"Resources/shaders/PostEffectTestPS.hlsl", L"Resources/shaders/PostEffectTestVS.hlsl");
	}
	if (Input::GetInstance()->TriggerKey(DIK_2)/*������Getter����������*/) {
		postEffect->CreateGraphicsPipeline(L"Resources/shaders/PostEffectColorPS.hlsl", L"Resources/shaders/PostEffectColorVS.hlsl");
	}
	if (Input::GetInstance()->TriggerKey(DIK_3)/*������Getter����������*/) {
		postEffect->CreateGraphicsPipeline(L"Resources/shaders/BlurPS.hlsl", L"Resources/shaders/BlurVS.hlsl");
	}
	//�Q�[���V�[���̖��t���[������
	gameScene->Update();
}

void NMGame::Draw()
{
	//�`��
	postEffect->PreDrawScene(dxcommon->GetCmdList());

	gameScene->Draw();
	postEffect->PostDrawScene(dxcommon->GetCmdList());

	dxcommon->preDraw();
	gameScene->DrawBG();
	postEffect->Draw(dxcommon->GetCmdList());
	gameScene->DrawFront();
	//gameScene->Draw();
	dxcommon->postDraw();
}

void NMGame::Finalize()
{
	// �e����
	Framework::Finalize();
	safe_delete(gameScene);
}
