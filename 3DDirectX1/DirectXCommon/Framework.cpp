#include "Framework.h"

void Framework::Run()
{
	Initialize();
	while (true)
	{
		if (endRequst == true) { break; }
		Update();
		Draw();

	}
	Finalize();
}

void Framework::Initialize()
{
	//�E�B���h�E�̐���
	winapp = new WinApp();
	winapp->CreateGameWindow();
	//DirectX�̏�����
	dxcommon = new DXCommon();
	dxcommon->Initialize(winapp);

	//�ėp�@�\�̏�����
	audio = new Audio();
	if (!audio->Initialize()) {
		assert(0);
		return;
	}

	if (!Sprite::StaticInitialize(dxcommon->Getdev(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return;
	}

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxcommon->Getdev());
	//���C�g�ÓI������
	LightGroup::StaticInitialize(dxcommon->Getdev());
	FbxLoader::GetInstance()->Initialize(dxcommon->Getdev());

	input = Input::GetInstance();
	input->Initialize(winapp);
	//�|�X�g�G�t�F�N�g�p�̃e�N�X�`���ǂݍ���
	//Sprite::LoadTexture(100, L"Resources/white1x1.png");
	//�|�X�g�G�t�F�N�g�̏�����
	postEffect = new PostEffect();
	postEffect->Initialize();
	postEffect->CreateGraphicsPipeline(L"Resources/shaders/PostEffectTestPS.hlsl", L"Resources/shaders/PostEffectTestVS.hlsl");
}

void Framework::Finalize()
{
	//�E�B���h�E�N���X��o�^����
	winapp->TerminateGameWindow();




	delete audio;
	delete dxcommon;
	delete winapp;
	delete postEffect;
}

void Framework::Update()
{
	if (winapp->ProcessMessage())
	{
		endRequst = true;
		return;
	}
	//���͊֘A�̖��t���[������
	input->update();


	}
