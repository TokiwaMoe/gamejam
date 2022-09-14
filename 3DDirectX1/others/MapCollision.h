#pragma once
#include"MapChip.h"
#include"Player.h"
class MapCollision
{
private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	void Map2Player(class Player*player,class MapChip*mapchip);
	static XMFLOAT2 PushBack(XMFLOAT2 pos, XMFLOAT2 oldPos, float size, XMFLOAT2 BPos, float blockSize, const int up, const int down);

};