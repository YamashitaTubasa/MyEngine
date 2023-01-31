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
using namespace std;

// 頂点データ
struct VertexPosUv {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

// パイプラインセット
struct PipelineSet {
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
};

// スプライトの共通データ
struct SpriteCommon {
	// パイプラインセット
	PipelineSet pipelineSet;
	// 射影行列
	XMMATRIX matProjection{};
	// テクスチャ用デスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャの最大枚数
	static const int spriteSRVCount = 512;
	// テクスチャソース(テクスチャバッファ)の配列
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
};

class Sprite
{
public:
	Sprite();
	~Sprite();

public:
	/// <summary>
	/// スプライト共通データ生成
	/// </summary>
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);

	/// <summary>
	/// 3Dオブジェクト用パイプライン生成
	/// </summary>
	/// <param name="device"></param>
	/// <returns></returns>
	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	/// <summary>
	/// スプライト共通テクスチャ読み込み
	/// </summary>
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, 
		const wchar_t* filename, ID3D12Device* dev);

	/// <summary>
	/// スプライト生成
	/// </summary>
	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height, 
		UINT texNumber, const SpriteCommon& spriteCommon, XMFLOAT2 anchorpoint, bool isFlipX, bool FlipY);

	/// <summary>
	/// スプライト単体頂点バッファの転送
	/// </summary>
	void SpriteTransferVertexBuffer(const Sprite& sprite, const SpriteCommon& spriteCommon, UINT texNumber);

	/// <summary>
	/// スプライト単体更新
	/// </summary>
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	/// <summary>
	/// スプライト共通グラフィックスコマンドのセット
	/// </summary>
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// <summary>
	/// スプライト単体描画
	/// </summary>
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, 
		ID3D12Device* dev,D3D12_VERTEX_BUFFER_VIEW& vbView);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

public: // セッター
	// 座標設定
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	// サイズ設定
	void SetScale(XMFLOAT2 scale) { this->scale = scale; }
	// 回転
	void SetRotation(const XMFLOAT3& rotation) { this->rotation_ = rotation; }
	// テクスチャサイズ
	void SetTexSize(XMFLOAT2 texSize) { this->texSize = texSize; }
	// 番号
	void SetTexNumber(UINT texNumber) { this->texNumber = texNumber; }

public:
	// 番号
	UINT GetTexNumber() const { return texNumber; }

public:
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_RESOURCE_DESC resDesc;

private:
	struct ConstBufferData {
		XMFLOAT4 color; // 色 (RGBA)
		XMMATRIX mat; //座標
	};

	DirectXCommon* dXCommon = nullptr;

	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	// テクスチャ番号
	UINT texNumber = 0;
	// 座標、大きさ
	XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	XMFLOAT2 scale = { 1.0f, 1.0f };
	XMFLOAT3 rotation_ = { 0.0f,0.0f,0.0f };
	// ワールド行列
	XMMATRIX matWorld;
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0.0f,0.0f };
	// テクスチャ左上座標設定
	XMFLOAT2 texLeftTop = { 50, 50 };
	// テクスチャ切り出しサイズ
	XMFLOAT2 texSize = { 100, 100 };

	// Z軸回りの回転
	float rotation = 0.0f;
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// 非表示
	bool isInvisible = false;
};

