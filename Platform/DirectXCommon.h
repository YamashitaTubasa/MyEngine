#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <chrono>
#include <thread>

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#include "Platform/WinApp.h"
//#include "Input/Input.h"
#include "Platform/FPSFixed.h"

using namespace Microsoft::WRL;
using namespace DirectX;

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
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

private: // メンバ関数
	// FPS固定初期化
	void InitializeFixFPS();
	// FPS固定更新
	void UpdateFixFPS();
	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

public: // Getter
	// デバイスの取得
	ID3D12Device* GetDevice() const { return device.Get(); }
	// コマンドリスト取得
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;
	// Input
	/*Input* input = nullptr;*/
	// FPS
	/*FPSFixed* fpsFixed = nullptr;*/

	HRESULT result;
	// DirectX12デバイス
	ComPtr<ID3D12Device> device;
	// DXGIファクトリ
	ComPtr<IDXGIFactory7> dxgiFactory;
	// スワップチェイン
	ComPtr<IDXGISwapChain4> swapChain;
	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> commandList;
	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	//// スワップチェーンの設定
	//DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	//// コマンドキューの設定
	//D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//D3D12_RESOURCE_BARRIER barrierDesc{};
	//D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	//バックバッファ
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	// フェンスの生成
	ComPtr<ID3D12Fence> fence;
	UINT rtvHD;
	UINT64 fenceVal = 0;
};