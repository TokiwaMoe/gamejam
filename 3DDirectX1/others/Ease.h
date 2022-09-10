#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Eas
{

private:
	// Microsoft::WRL::Çè»ó™
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();
	static const XMFLOAT2 lerp(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeIn(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeIn(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	static const XMFLOAT2 easeInOut(const XMFLOAT2& start, const XMFLOAT2& end, const float t);
	static const XMFLOAT3 easeInOut(const XMFLOAT3& start, const XMFLOAT3& end, const float t);

	float easeInCubic(float x);//1
	float easeOutCubic(float x);//2
	float easeInQuad(float x);//3
	float easeOutQuad(float x);//4
	float easeOutBounce(float x);//5
	float easeInBounce(float x);//6
	float ease(const float& start, const float& end, float t, float d, int i);
	XMFLOAT2 ease(const XMFLOAT2& start, const XMFLOAT2& end, float t,float d, int i);
	XMFLOAT3 ease(const XMFLOAT3& start, const XMFLOAT3& end, float t,float d, int i);

	XMFLOAT2 easeOut_Bounce(XMFLOAT2 start, XMFLOAT2 end, float flame);

	float Bounce_out(float x);

public:
	XMFLOAT2 position = { 0,0 };
	float time = 0;
	const float maxflame = 10.0f;
	const float PI = 3.141592;
	XMFLOAT2 difference = { 0,0 };
};

