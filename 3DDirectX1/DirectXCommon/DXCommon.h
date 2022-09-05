#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include "WinApp.h"

class DXCommon {
public:
	void Initialize(WinApp* winapp);
	void preDraw();
	void postDraw();

	void ClearRenderTarget();

	void ClearDepthBuffer();

	ID3D12Device* Getdev() { return dev.Get(); }

	ID3D12GraphicsCommandList* GetCmdList() { return cmdList.Get(); }
private:
	void InitializeDevice();//�f�o�C�X������
	void InitializeCommand();//�R�}���h������
	void InitializeSwapchain();//�X���b�v�`�F�[��
	void InitializeRenderTargetView();//�����_�[�^�[�Q�b�g
	void InitializeDepthBuffer();//�[�x�o�b�t�@
	void InitializeFance();//�t�F���X����

private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	WinApp* winapp = nullptr;
	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;//����������o�ϐ��ɂ��Ȃ��Ɨ�O�X���[���N����̂Œ���!!
	UINT64 fenceVal = 0;
};
