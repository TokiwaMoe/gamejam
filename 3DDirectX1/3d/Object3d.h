#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"

#include "Camera.h"
#include "LightGroup.h"
#include "CollisionInfo.h"
class BaseCollider;
class Object3d
{
protected: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	
	// パイプラインセット
	struct PipelineSet
	{
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX viewproj;//ビュープロジェクション行列
		XMMATRIX world;//ワールド行列
		XMFLOAT3 cameraPos;//カメラ座標(ワールド座標)
	};

	Object3d() = default;

	virtual ~Object3d();

	static void StaticInitialize(ID3D12Device* dev, Camera* camera= nullptr);

	void CreateGraphicsPipeline(const wchar_t* ps, const wchar_t* vs);

	static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}
	static void SetLight(LightGroup* lightGroup) {
		Object3d::lightGroup = lightGroup;
	}

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	static void PostDraw();

	static Object3d* Create(Model* model);


	virtual bool Initialize();

	void Quaternion();
	virtual void Update();

	virtual void Draw();

	const XMMATRIX& GetMatWorld() { return matWorld; }

	void SetCollider(BaseCollider* collider);

	virtual void OnCollision(const CollisionInfo& info) {}

	XMFLOAT3 GetWorldPosition();

	const XMFLOAT3& GetPosition() { return position; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }

	const XMVECTOR& GetRotation() { return rotation; }

	void SetRotation(XMVECTOR rotation) { this->rotation = rotation; }

	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// モデルとの連携
	void SetModel(Model* model) { this->model = model; };


	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }
	void SetParent(Object3d* parent) { this->parent = parent; }

	XMMATRIX GetMatRot() { return matRot; }
	XMMATRIX GetMatTrans() { return matTrans; }
	inline Model* GetModel() { return model; }
	BaseCollider* GetCollider() { return collider; }
	//unityのペアレントがしたい(親オブジェのサイズに影響しない&当たった場所にくっつく)
	void transformParent();
	// コライダー
	BaseCollider* collider = nullptr;
protected:
	const char* name = nullptr;
	// デバイス
	static ID3D12Device* dev;

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;

	// パイプライン
	PipelineSet pipelineSet;

	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	XMFLOAT4 color = { 1,0,0,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMVECTOR rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;

	Model* model = nullptr;
	XMMATRIX matWorld_parent, matTransV, matRotV, matScaleV, matWorld_Invers;
	XMMATRIX matScale, matRot, matTrans;
	XMVECTOR rotV;
	// カメラ
	static Camera* camera;
	static LightGroup* lightGroup;
	// ビルボード
	bool isBillboard = false;


};

