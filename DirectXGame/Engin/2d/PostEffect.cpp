#include "PostEffect.h"

#include <d3dx12.h>

using namespace DirectX;

PostEffect::PostEffect()
	: Sprite(
		100, // �e�N�X�`���ԍ�
		{ 0,0 }, // ���W
		{ 500.0f,500.0f }, // �T�C�Y
		{ 1,1,1,1 }, // �F
		{ 0.0f,0.0f }, // �A���J�[�|�C���g
		false, // ���E���]�t���O
		false) // �㉺���]�t���O
{
}

void PostEffect::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//this->cmdList = cmdList_;

	//// ���_�o�b�t�@���Z�b�g
	//cmdList->IASetVertexBuffers(0, 1, &vbView);

	//// �萔�o�b�t�@(CBV)���Z�b�g
	//cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());

	////�V�F�[�_�[���\�[�X�r���[���Z�b�g
	//cmdList->SetGraphicsRootDescriptorTable(
	//	1, CD3DX12_GPU_DESCRIPTOR_HANDLE(
	//		spriteCommon.descHeap->GetGPUDescriptorHandleForHeapStart(),
	//		texNumber,
	//		dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)));

	////�|���S���̕`��(4���_�Ŏl�p�`)
	//cmdList->DrawInstanced(4, 1, 0, 0);
}
