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
//// �X�v���C�g
//// =================
//class Sprite
//{
//public:
//	struct VertexPosUv
//	{
//		XMFLOAT3 pos; // xyz���W
//		XMFLOAT3 uv; // uv���W
//	};
//
//	struct PipelineSet
//	{
//		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
//		ComPtr<ID3D12PipelineState> pipelinestate;
//		// ���[�g�V�O�l�`��
//		ComPtr<ID3D12RootSignature> rootsignature;
//	};
//
//	struct SpritePipelineSet {
//		PipelineSet pipelineSet;
//	};
//
//public: // �����o�֐�
//	// ������
//	void Initialize(SpriteCommon* spriteCommon);
//	// �X�V
//	void Update();
//	// �`��
//	void Draw(const SpritePipelineSet* pipelineSet);
//	// �p�C�v���C������
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


//�X�v���C�g�p
struct VertexPosUv {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

//�X�v���C�g�̋��ʃf�[�^
struct SpriteCommon {

	//�e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;

	//�p�C�v���C���Z�b�g
	PipelineSet pipelineSet;

	//�ˉe�s��
	XMMATRIX matProjrction{};

	//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//�e�N�X�`���\�[�X(�e�N�X�`���o�b�t�@)�̔z��
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];

};

class Sprite
{
	//-----------�X�v���C�g----------

public:


	void SetPiplineSet(PipelineSet piplineSet);

	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* dev);

	//�X�v���C�g1�����̃f�[�^

	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};

private:
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//Z�����̉�]�p
	float rotation = 0.0f;
	//���W
	XMFLOAT3 position = { 0,0,0 };
	//���[���h�s��
	XMMATRIX matWorld;

	UINT texNumber = 0;

	XMFLOAT2 size = { 100.0f,100.0f };

	struct ConstBufferData {
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat; //���W
	};

	//�R�}���h���X�g
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	DirectXCommon* dx = nullptr;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

public:

	//�X�v���C�g����
	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height);

	//�X�v���C�g���ʃf�[�^����
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);

	//�X�v���C�g���ʃO���t�B�b�N�X�R�}���h�̃Z�b�g
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	//�X�v���C�g�P�̕`��

	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, ID3D12Device* dev,
		D3D12_VERTEX_BUFFER_VIEW& vbView);

	//�X�v���C�g�P�̍X�V
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	//�X�v���C�g���ʃe�N�X�`���ǂݍ���
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);

	//�X�v���C�g�P�̒��_�o�b�t�@�̓]��
	void SpriteTransferVertexBuffer(const Sprite& sprite);

	//�Z�b�^�[
	void SetTexNumber(UINT texnumber) { this->texNumber = texnumber; }

	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetScale(XMFLOAT2 scale) { this->size = scale; }


	void Release();
};

