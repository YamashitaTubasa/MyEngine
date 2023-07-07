#include "PostEffect.h"

#include <d3dx12.h>

using namespace DirectX;

PostEffect::PostEffect()
	: Sprite(
		100,               // テクスチャ番号
		{ 0,0,0 },         // 座標
		{ 500.0f,500.0f }, // サイズ
		{ 1,1,1,1 },       // 色
		{ 0.0f,0.0f },     // アンカーポイント
		false,             // 左右反転フラグ
		false)             // 上下反転フラグ
{
}

void PostEffect::Initialize()
{
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList_)
{
	// 非表示フラグがtrueなら
	if (isInvisible) {
		// 描画せずに抜ける
		return;
	}

	this->cmdList = cmdList_;

	// パイプラインステートとルートシグネチャの設定
	cmdList->SetPipelineState(pipelinestate.Get());
	cmdList->SetGraphicsRootSignature(rootsignature.Get());

	// プリミティブ形状の設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP); // 三角形リスト

	// 頂点バッファをセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	// 定数バッファ(CBV)をセット
	cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	//テクスチャ用でスクリプタヒープの設定
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	//シェーダーリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(
		1, CD3DX12_GPU_DESCRIPTOR_HANDLE(
			descHeap->GetGPUDescriptorHandleForHeapStart(),
			texNumber,
			device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	//ポリゴンの描画(4頂点で四角形)
	cmdList->DrawInstanced(4, 1, 0, 0);
}
