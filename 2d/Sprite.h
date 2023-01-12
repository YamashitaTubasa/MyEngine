//#pragma once
//
//#include <d3dcompiler.h>
//
//#include "2d/SpriteCommon.h"
//
//#pragma comment(lib, "d3dcompiler.lib")
//
//
//// =================
//// スプライト
//// =================
//class Sprite
//{
//public:
//	struct VertexPosUv
//	{
//		XMFLOAT3 pos; // xyz座標
//		XMFLOAT3 uv; // uv座標
//	};
//
//	struct PipelineSet
//	{
//		// パイプラインステートオブジェクト
//		ComPtr<ID3D12PipelineState> pipelinestate;
//		// ルートシグネチャ
//		ComPtr<ID3D12RootSignature> rootsignature;
//	};
//
//	struct SpritePipelineSet {
//		PipelineSet pipelineSet;
//	};
//
//public: // メンバ関数
//	// 初期化
//	void Initialize(SpriteCommon* spriteCommon);
//	// 更新
//	void Update();
//	// 描画
//	void Draw(const SpritePipelineSet* pipelineSet);
//	// パイプライン生成
//	Sprite::PipelineSet Object3dCreateGraphicsPipeline(ID3D12Device* dev);
//
//public:
//	SpriteCommon* spriteCommon = nullptr;
//
//private:
//	ComPtr<ID3D12Device> dev;
//	ComPtr<ID3D12GraphicsCommandList> cmdList;
//};

#pragma once

#include <Windows.h>
#include <D3dx12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <cassert>
#include <DirectXTex.h>
#include <wrl.h>

#include "Platform/DirectXCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

struct PipelineSet {

	ComPtr<ID3D12PipelineState> pipelinestate;

	ComPtr<ID3D12RootSignature> rootsignature;

};


//スプライト用
struct VertexPosUv {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

//スプライトの共通データ
struct SpriteCommon {

	//テクスチャの最大枚数
	static const int spriteSRVCount = 512;

	//パイプラインセット
	PipelineSet pipelineSet;

	//射影行列
	XMMATRIX matProjrction{};

	//テクスチャ用デスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//テクスチャソース(テクスチャバッファ)の配列
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];

};

class Sprite
{
	//-----------スプライト----------

public:


	void SetPiplineSet(PipelineSet piplineSet);

	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* dev);

	//スプライト1枚分のデータ

	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};

private:
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//Z軸回りの回転角
	float rotation = 0.0f;
	//座標
	XMFLOAT3 position = { 0,0,0 };
	//ワールド行列
	XMMATRIX matWorld;

	UINT texNumber = 0;

	XMFLOAT2 size = { 100.0f,100.0f };

	struct ConstBufferData {
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat; //座標
	};

	//コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	DirectXCommon* dx = nullptr;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

public:

	//スプライト生成
	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height);

	//スプライト共通データ生成
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);

	//スプライト共通グラフィックスコマンドのセット
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	//スプライト単体描画

	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, ID3D12Device* dev,
		D3D12_VERTEX_BUFFER_VIEW& vbView);

	//スプライト単体更新
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	//スプライト共通テクスチャ読み込み
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);

	//スプライト単体頂点バッファの転送
	void SpriteTransferVertexBuffer(const Sprite& sprite);

	//セッター
	void SetTexNumber(UINT texnumber) { this->texNumber = texnumber; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetScale(XMFLOAT2 scale) { this->size = scale; }


	void Release();
};

