#include "MapChip.h"

void MapChip::Initialize()
{


	Sprite::LoadTexture(20, L"Resources/block.png");
	for (int j = 0; j < 24; j++) {
		for (int i = 0; i < 43; i++) {
			floor[j][i] = Sprite::CreateSprite(20, { pos.x + i * mapSize ,pos.y + j * mapSize });
			floor[j][i]->SetSize({ mapSize,mapSize });
		}
	}
}

void MapChip::Init()
{
}

void MapChip::Update()
{
}  

void MapChip::Draw()
{
	for (int j = 0; j < 24; j++) {
		for (int i = 0; i < 43; i++) {

			if (map[j][i] == 1) {
				floor[j][i]->Draw();
			}
		}
	}
}
