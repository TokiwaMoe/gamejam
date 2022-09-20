#include "MapCollision.h"
using namespace DirectX;
void MapCollision::Map2Player(Player* player, MapChip* mapchip)
{
	if (player == nullptr || mapchip == nullptr) { return; }
	//判定する箇所だけ行うため
	int X = player->GetPlayerPos().x / mapchip->GetMapSize();
	int Y = player->GetPlayerPos().y / (-mapchip->GetMapSize());

	for (int j = (Y - 2); j < (Y + 2); j++)
	{
		for (int i = (X - 2); i < (X + 2); i++)
		{
			if (j < 0 || i < 0 || j >= 24 || i >= 43)
			{
				continue;
			}
			if (!(mapchip->GetMap(i, j) == NONE))//0以外当たり判定
			{
				//プレイヤー
				bool HitFlag = Collision::CheckSphere2Box(player->GetSphere(), mapchip->GetBox(i, j));
				if (HitFlag)
				{
					player->SetPlayerPos(PushBack(player->GetPlayerPos(), player->GetOPos(), player->GetPSize(),
						mapchip->GetPos(i, j), mapchip->GetMapSize() / 2,
						mapchip->GetMap(i, (j + 1) % 24), mapchip->GetMap(i, (j - 1) % 24)));
				}
			}
		}
	}
}

XMFLOAT2 MapCollision::PushBack(XMFLOAT2 pos, XMFLOAT2 oldPos, float size, XMFLOAT2 BPos, float blockSize, const int up, const int down)
{
	//プレイヤー座標
	float PRight = pos.x + size, PLeft = pos.x - size;
	float PUp = pos.y + size, PDown = pos.y - size;
	//プレイヤーの前の座標
	float oldRight = oldPos.x + size, oldLeft = oldPos.x - size;
	float oldUp = oldPos.y + size, oldDown = oldPos.y - size;
	//ブロック座標
	float BRight = BPos.x + blockSize, BLeft = BPos.x - blockSize;
	float BUp = BPos.y + blockSize, BDown = BPos.y - blockSize;
	//左上
	if (oldLeft >= BRight && oldUp <= BDown)
	{
		if (!(up == NONE))
		{
		}
		//上にブロックがなかったら上優先
		else if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
	}
	//左下
	else if (oldLeft >= BRight && oldDown >= BUp)
	{
		if (!(down == NONE))
		{
		}
		//下にブロックがなかったら下優先
		else if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}
	//右上
	else if (oldRight <= BLeft && oldUp <= BDown)
	{
		if (!(up == NONE))
		{
		}
		//上にブロックがなかったら上優先
		else if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
	}
	//右下
	else if (oldRight <= BLeft && oldDown >= BUp)
	{
		if (!(down == NONE))
		{
		}
		//下にブロックがなかったら下優先
		else if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}
	else
	{
		//右
		if (oldRight <= BLeft)
		{
			pos.x = BLeft - size;
		}
		//左
		if (oldLeft >= BRight)
		{
			pos.x = BRight + size;
		}
		//上
		if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
		//下
		if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}

	return pos;
}
