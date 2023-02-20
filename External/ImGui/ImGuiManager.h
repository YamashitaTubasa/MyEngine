#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include <imgui_impl_win32.h>
#include <imgui_impl_dx12.h>

//==============
// Imgui�̊Ǘ�
//==============
class ImGuiManager 
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon_, WinApp* winApp_);

	/// <summary>
	/// �I��
	/// </summary>
	void Finalize();

	/// <summary>
	/// ImGui��t�J�n
	/// </summary>
	void Begin();

	/// <summary>
	/// ImGui��t�I��
	/// </summary>
	void End();

	/// <summary>
	/// ��ʂւ̕`��
	/// </summary>
	void Draw(DirectXCommon* dXCommon);

	/// <summary>
	/// �Z�[�u
	/// </summary>
	void MySaveFunction();

private:
	WinApp* winApp_ = nullptr;
	DirectXCommon* dXCommon_ = nullptr;

	// SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;
};
