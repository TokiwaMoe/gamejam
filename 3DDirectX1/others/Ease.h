#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class Eas
{

private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
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
	
	XMFLOAT2 ease(const XMFLOAT2& start, const XMFLOAT2& end, float t,float d, int i);
	XMFLOAT3 ease(const XMFLOAT3& start, const XMFLOAT3& end, float t,float d, int i);

};

