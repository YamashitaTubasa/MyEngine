#pragma once

#include <d3dcompiler.h>

#include "2d/SpriteCommon.h"

#pragma comment(lib, "d3dcompiler.lib")


// =================
// スプライト
// =================
class Sprite
{
public:
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 uv; // uv座標
	};

	struct PipelineSet
	{
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
	};

	struct SpritePipelineSet {
		PipelineSet pipelineSet;
	};

public: // メンバ関数
	// 初期化
	void Initialize(SpriteCommon* spriteCommon);
	// 更新
	void Update();
	// 描画
	void Draw(const SpritePipelineSet* pipelineSet);
	// パイプライン生成
	Sprite::PipelineSet Object3dCreateGraphicsPipeline(ID3D12Device* dev);

public:
	SpriteCommon* spriteCommon = nullptr;

private:
	ComPtr<ID3D12Device> dev;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
};
