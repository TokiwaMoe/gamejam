#include "MapCollision.h"
using namespace DirectX;
void MapCollision::Map2Player(Player* player, MapChip* mapchip)
{
}

XMFLOAT2 MapCollision::PushBack(XMFLOAT2 pos, XMFLOAT2 oldPos, float size, XMFLOAT2 BPos, float blockSize, const int up, const int down)
{
	//�v���C���[���W
	float PRight = pos.x + size, PLeft = pos.x - size;
	float PUp = pos.y + size, PDown = pos.y - size;
	//�v���C���[�̑O�̍��W
	float oldRight = oldPos.x + size, oldLeft = oldPos.x - size;
	float oldUp = oldPos.y + size, oldDown = oldPos.y - size;
	//�u���b�N���W
	float BRight = BPos.x + blockSize, BLeft = BPos.x - blockSize;
	float BUp = BPos.y + blockSize, BDown = BPos.y - blockSize;
	//����
	if (oldLeft >= BRight && oldUp <= BDown)
	{
		if (!(up == NONE))
		{
		}
		//��Ƀu���b�N���Ȃ��������D��
		else if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
	}
	//����
	else if (oldLeft >= BRight && oldDown >= BUp)
	{
		if (!(down == NONE))
		{
		}
		//���Ƀu���b�N���Ȃ������牺�D��
		else if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}
	//�E��
	else if (oldRight <= BLeft && oldUp <= BDown)
	{
		if (!(up == NONE))
		{
		}
		//��Ƀu���b�N���Ȃ��������D��
		else if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
	}
	//�E��
	else if (oldRight <= BLeft && oldDown >= BUp)
	{
		if (!(down == NONE))
		{
		}
		//���Ƀu���b�N���Ȃ������牺�D��
		else if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}
	else
	{
		//�E
		if (oldRight <= BLeft)
		{
			pos.x = BLeft - size;
		}
		//��
		if (oldLeft >= BRight)
		{
			pos.x = BRight + size;
		}
		//��
		if (oldUp <= BDown)
		{
			pos.y = BDown - size;
		}
		//��
		if (oldDown >= BUp)
		{
			pos.y = BUp + size;
		}
	}

	return pos;
}
