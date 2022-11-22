#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp/WinApp.h"
#include <vector>

using namespace Microsoft::WRL;

// DirectX���
class DirectXCommon
{
public: // �����o�֐�
	// ������
	void Initialize(WinApp* winApp);

	// �f�o�C�X�̏�����
	void InitializeDevice();

	// �R�}���h�֘A�̏�����
	void InitializeCommand();

	// �X���b�v�`�F�[���̏�����
	void InitializeSwapchain();

	// �����_�[�^�[�Q�b�g�r���[�̏�����
	void InitializeRenderTargetView();

	// �[�x�o�b�t�@�̏�����
	void InitializeDepthBuffer();

	// �t�F���X�̏�����
	void InitializeFence();

private: 
	// WindowsAPI
	WinApp* winApp = nullptr;
	HRESULT result;
	// DirectX12�f�o�C�X
	ComPtr<ID3D12Device> device;
	// DXGI�t�@�N�g��
	ComPtr<IDXGIFactory7> dxgiFactory;
	// �X���b�v�`�F�C��
	ComPtr<IDXGISwapChain4> swapChain;
	// �R�}���h�A���P�[�^
	ComPtr<ID3D12CommandAllocator> commndAllocator;
	// �R�}���h���X�g
	ComPtr<ID3D12GraphicsCommandList> commandList;
	// �R�}���h�L���[
	ComPtr<ID3D12CommandQueue> commandQueue;
	//
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// �X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	// �R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
	
};