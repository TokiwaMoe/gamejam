#pragma once
#include"Collision.h"
//�I�u�W�F�N�g�̍\���̂������w�b�_�[�t�@�C��

// Microsoft::WRL::���ȗ�
template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
// DirectX::���ȗ�
using XMFLOAT2 = DirectX::XMFLOAT2;
using XMFLOAT3 = DirectX::XMFLOAT3;
using XMFLOAT4 = DirectX::XMFLOAT4;
using XMMATRIX = DirectX::XMMATRIX;
using XMVECTOR = DirectX::XMVECTOR;
struct object
{
	Sphere sphere;//�����蔻��p�̋�
	float oSize;//�I�u�W�F�N�g�̃T�C�Y(����傫�����邽�߂ɐݒ肷����)
	//�����艺��position�ȂǏ����Ă���
	XMFLOAT3 pos = {};//�ʒu
	XMVECTOR rot = {};//�p�x(�N�H�[�^�j�I�����g�p���Ă��邽�߁AXMVECTOR)
	XMFLOAT3 size = {};//�����ڂ̃T�C�Y(oSize�Ƃ͈Ⴄ)
};