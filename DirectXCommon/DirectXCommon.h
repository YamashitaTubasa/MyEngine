#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp/WinApp.h"

// DirectX基盤
class DirectXCommon
{
public: // メンバ関数
	// 初期化
	void Initialize(WinApp* winApp);

	// デバイスの初期化
	void InitializeDevice();

	// コマンド関連の初期化
	void InitializeCommand();

	// スワップチェーンの初期化
	void InitializeSwapchain();

	// レンダーターゲットビューの初期化
	void InitializeRenderTargetView();

	// 深度バッファの初期化
	void InitializeDepthBuffer();

	// フェンスの初期化
	void InitializeFence();

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;

	// DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	// スワップチェイン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	// コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
};