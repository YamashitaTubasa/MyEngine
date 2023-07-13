#pragma once

#include "Sprite.h"
#include "Input.h"

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

private:
	// 定数バッファ用データ構造体
	struct ConstBufferData {
		DirectX::XMFLOAT4 color; // 色 (RGBA)
		DirectX::XMMATRIX mat; // 座標
		bool isBlur; // ブラーフラグ
		float alpha; // アルファ値
	};

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

	/// <summary>
	/// シーン描画前処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// </summary>
	/// <param name="cmdList">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// パイプライン生成
	/// </summary>
	void CreateGraphicsPipelineState();

public: // セッター
	// カラーの設定
	void SetColor(const XMFLOAT4& color);
	// アルファ値の設定
	void SetAlpha(float alpha);
	// ブラーの設定
	void SetBlur(bool isBlur);

	XMFLOAT4 GetColor() const { return PostEffect::color_; }

private: // メンバ変数
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff[2];
	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	// 震度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	// RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	// DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	// グラフィクスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
	// デバイス
	ComPtr<ID3D12Device> device;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	// 定数バッファ用データ構造体
	ConstBufferData* constMap = nullptr;

private: // 定数
	// 画面クリアカラー
	static const float clearColor[4];
	// 頂点数
	static const int vertNum = 4;
	// 色
	DirectX::XMFLOAT4 color_ = { 1,1,1,1 };
	// ブラーフラグ
	bool isBlur_ = false;
	// アルファ値
	float alpha_ = 1.0f;
};

