#pragma once 
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "WinApp/WinApp.h"

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

	// DirectX12�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	// DXGI�t�@�N�g��
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	// �X���b�v�`�F�C��
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain;
	// �R�}���h�A���P�[�^
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
	// �R�}���h���X�g
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	// �R�}���h�L���[
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	//
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	// �o�b�N�o�b�t�@
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> backBuffers;
};