#pragma once
#include"WinApp.h"
#include"Audio.h"
#include"DXCommon.h"
#include "input.h"
#include "Object3d.h"
#include "FbxLoader.h"
#include "PostEffect.h"
#include"LightGroup.h"
class Framework
{
public:
	//������
	void Run();
	virtual void Initialize();
	//�I��
	virtual void Finalize();
	// ���t���[������
	virtual void Update();
	// �`��
	virtual void Draw() = 0;
	bool eR() { return endRequst; }
protected:
	bool endRequst = false;
	WinApp* winapp = nullptr;
	DXCommon* dxcommon = nullptr;
	Audio* audio = nullptr;
	Input* input = nullptr;

	PostEffect* postEffect = nullptr;
};

