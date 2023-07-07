#pragma once

#include "Sprite.h"

/// <summary>
/// ポストエフェクト
/// </summary>
class PostEffect : public Sprite
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	PostEffect();

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画コマンドの発行
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList_);

private:
	SpriteCommon spriteCommon;

	ID3D12GraphicsCommandList* cmdList = nullptr;
	ComPtr<ID3D12Resource> constBuff;
	ComPtr<ID3D12PipelineState> pipelinestate;
	ComPtr<ID3D12RootSignature> rootsignature;
	ComPtr<ID3D12DescriptorHeap> descHeap;
};

