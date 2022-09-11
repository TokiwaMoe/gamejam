#pragma once
#include"CSV.h"
#include"Sprite.h"
class MapChip
{
public:
	void Initialize();
	void Init();
	void Update();
	void Draw();
private:
	Sprite* floor = nullptr;
};