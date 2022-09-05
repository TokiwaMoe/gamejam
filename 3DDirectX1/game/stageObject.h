#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include<DirectXMath.h>
/// <summary>
/// �n�`�I�u�W�F�N�g
/// </summary>
class TouchableObject;
class StageObject
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	StageObject();
	~StageObject();
	void Initialize();
	void Init();
	void Update();
	void Draw();


private:
	TouchableObject* slope;
	Model* modelSlope;

	XMFLOAT3 position = {0,0,0 };
	XMFLOAT3 size = { 1,1,1 };
	XMVECTOR rota = { 0,0,0,0 };

};

