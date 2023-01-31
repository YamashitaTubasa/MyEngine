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

// ���_�f�[�^
struct VertexPosUv {
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};

// �p�C�v���C���Z�b�g
struct PipelineSet {
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
};

// �X�v���C�g�̋��ʃf�[�^
struct SpriteCommon {
	// �p�C�v���C���Z�b�g
	PipelineSet pipelineSet;
	// �ˉe�s��
	XMMATRIX matProjection{};
	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���̍ő喇��
	static const int spriteSRVCount = 512;
	// �e�N�X�`���\�[�X(�e�N�X�`���o�b�t�@)�̔z��
	ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
};

class Sprite
{
public:
	Sprite();
	~Sprite();

public:
	/// <summary>
	/// �X�v���C�g���ʃf�[�^����
	/// </summary>
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);

	/// <summary>
	/// 3D�I�u�W�F�N�g�p�p�C�v���C������
	/// </summary>
	/// <param name="device"></param>
	/// <returns></returns>
	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	/// <summary>
	/// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	/// </summary>
	void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, 
		const wchar_t* filename, ID3D12Device* dev);

	/// <summary>
	/// �X�v���C�g����
	/// </summary>
	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height, 
		UINT texNumber, const SpriteCommon& spriteCommon, XMFLOAT2 anchorpoint, bool isFlipX, bool FlipY);

	/// <summary>
	/// �X�v���C�g�P�̒��_�o�b�t�@�̓]��
	/// </summary>
	void SpriteTransferVertexBuffer(const Sprite& sprite, const SpriteCommon& spriteCommon, UINT texNumber);

	/// <summary>
	/// �X�v���C�g�P�̍X�V
	/// </summary>
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g���ʃO���t�B�b�N�X�R�}���h�̃Z�b�g
	/// </summary>
	void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g�P�̕`��
	/// </summary>
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, 
		ID3D12Device* dev,D3D12_VERTEX_BUFFER_VIEW& vbView);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

public: // �Z�b�^�[
	// ���W�ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	// �T�C�Y�ݒ�
	void SetScale(XMFLOAT2 scale) { this->scale = scale; }
	// ��]
	void SetRotation(const XMFLOAT3& rotation) { this->rotation_ = rotation; }
	// �e�N�X�`���T�C�Y
	void SetTexSize(XMFLOAT2 texSize) { this->texSize = texSize; }
	// �ԍ�
	void SetTexNumber(UINT texNumber) { this->texNumber = texNumber; }

public:
	// �ԍ�
	UINT GetTexNumber() const { return texNumber; }

public:
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_RESOURCE_DESC resDesc;

private:
	struct ConstBufferData {
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat; //���W
	};

	DirectXCommon* dXCommon = nullptr;

	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	// �e�N�X�`���ԍ�
	UINT texNumber = 0;
	// ���W�A�傫��
	XMFLOAT3 position = { 0.0f, 0.0f, 0.0f };
	XMFLOAT2 scale = { 1.0f, 1.0f };
	XMFLOAT3 rotation_ = { 0.0f,0.0f,0.0f };
	// ���[���h�s��
	XMMATRIX matWorld;
	// �A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0.0f,0.0f };
	// �e�N�X�`��������W�ݒ�
	XMFLOAT2 texLeftTop = { 50, 50 };
	// �e�N�X�`���؂�o���T�C�Y
	XMFLOAT2 texSize = { 100, 100 };

	// Z�����̉�]
	float rotation = 0.0f;
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// ��\��
	bool isInvisible = false;
};

