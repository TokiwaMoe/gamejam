#pragma once
#include<DirectXMath.h>

struct Sphere
{
	//���S���W
	DirectX::XMVECTOR center = { 0,0,0,1 };
	//���a
	float radius = 1.0f;
};
struct Box
{
	//�ŏ��l
	DirectX::XMVECTOR minPosition;
	//�ő�l
	DirectX::XMVECTOR maxPosition;

};

struct Plane
{
	//�@���x�N�g��
	DirectX::XMVECTOR normal = { 0,1,0,0 };
	//���_����̋���
	float distance = 0.0f;
};
struct Ray
{
	DirectX::XMVECTOR start = { 0,0,0,1 };
	DirectX::XMVECTOR dir = { 1,0,0,0 };
};
class Triangle
{
public:
	//���_���W3��
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;
	//�@���x�N�g��
	DirectX::XMVECTOR normal;

	void ComputeNormal();
};
class OBB {

public:
	
		DirectX::XMVECTOR m_Pos;
		DirectX::XMVECTOR m_NormaDirect[3];
		float m_fLength[3];

		DirectX::XMVECTOR GetDirect(int elem) { return m_NormaDirect[elem]; }   // �w�莲�ԍ��̕����x�N�g�����擾
		float GetLen_W(int elem) { return m_fLength[elem]; }          // �w�莲�����̒������擾
		DirectX::XMVECTOR GetPos_W() { return m_Pos; }
};