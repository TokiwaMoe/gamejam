#pragma once
#include"Framework.h"
#include "GameScene.h"
class GameScene;
class NMGame :public Framework
{
public:
	// ������
	void Initialize() override;
	//�I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;
private:
	GameScene* gameScene = nullptr;

};

