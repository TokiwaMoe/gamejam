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

			if (map[j][i] == BLOCK) {
				floor[j][i]->Draw();
			}
		}
	}
}

Box MapChip::GetBox(int j, int i)
{
	Box box;
	box.maxPosition = XMVectorSet(
		pos.x + i * mapSize + mapSize / 2,
		pos.y + j * (-mapSize) + mapSize / 2,
		0,
		1);
	box.minPosition = XMVectorSet(
		pos.x + i * mapSize - mapSize / 2,
		pos.y + j * (-mapSize) - mapSize / 2,
		0,
		1);
	return box;
}

XMFLOAT2 MapChip::GetPos(int i, int j)
{
	return XMFLOAT2( pos.x + i * mapSize ,pos.y + j * mapSize );
}
