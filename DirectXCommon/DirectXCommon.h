#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp/WinApp.h"
#include <vector>

using namespace Microsoft::WRL;

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
	HRESULT result;
	// DirectX12デバイス
	ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	ComPtr<IDXGIFactory7> dxgiFactory;
	// スワップチェイン
	ComPtr<IDXGISwapChain4> swapChain;
	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> commndAllocator;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> commandList;
	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue;
	//
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// スワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	// コマンドキューの設定
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//バックバッファ
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	
};