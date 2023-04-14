#include "ParticleM.h"

#include <DirectXTex.h>
#include <Windows.h>
#include <cassert>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace DirectX;
using namespace std;
using namespace Microsoft::WRL;

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device* ParticleM::device = nullptr;
UINT ParticleM::descriptorHandleIncrementSize = 0;
//ID3D12GraphicsCommandList* ParticleM::cmdList = nullptr;
ComPtr<ID3D12RootSignature> ParticleM::rootsignature;
ComPtr<ID3D12PipelineState> ParticleM::pipelinestate;
ComPtr<ID3D12DescriptorHeap> ParticleM::descHeap;
ComPtr<ID3D12Resource> ParticleM::vertBuff;
ComPtr<ID3D12Resource> ParticleM::texbuff;
CD3DX12_CPU_DESCRIPTOR_HANDLE ParticleM::cpuDescHandleSRV;
CD3DX12_GPU_DESCRIPTOR_HANDLE ParticleM::gpuDescHandleSRV;
D3D12_VERTEX_BUFFER_VIEW ParticleM::vbView{};
ParticleM::VertexPos ParticleM::vertices[vertexCount];

// XMFLOAT3���m�̉��Z����
const DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs)
{
	XMFLOAT3 result;

	result.x = lhs.x + rhs.x;
	result.y = lhs.y + rhs.y;
	result.z = lhs.z + rhs.z;

	return result;
}

ParticleM* ParticleM::LoadFromOBJ(const std::string& filename)
{
	ParticleM* particle = new ParticleM();

	particle->InitializeDescriptorHeap();

	particle->LoadTexture(filename);

	particle->CreateModel();

	return particle;
}

void ParticleM::Update()
{
	HRESULT result;

	// �������s�����p�[�e�B�N����S�폜
	particles.remove_if(
		[](Particle0& x) {
			return x.frame >= x.num_frame;
		}
	);

	// �S�p�[�e�B�N���X�V
	for (std::forward_list<Particle0>::iterator it = particles.begin();
		it != particles.end();
		it++) {
		// �o�߃t���[�������J�E���g
		it->frame++;
		// ���x�ɉ����x�����Z
		it->velocity = it->velocity + it->accel;
		// ���x�ɂ��ړ�
		it->position = it->position + it->velocity;
		// �i�s�x��0�`1�͈̔͂Ɋ��Z
		float f = (float)it->num_frame / it->frame;
		// �X�P�[���̐��`���
		it->scale = (it->e_scale - it->s_scale) / f,
			it->scale += it->s_scale;
	}

	// ���_�o�b�t�@�փf�[�^�]��
	VertexPos* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		// �p�[�e�B�N���̏���1�����f
		for (std::forward_list<Particle0>::iterator it = particles.begin();
			it != particles.end();
			it++) {
			// ���W
			vertMap->pos = it->position;
			// ���̒��_��
			vertMap++;
			// �X�P�[��
			vertMap->scale = it->scale;
		}
		vertBuff->Unmap(0, nullptr);
	}
}

void ParticleM::Draw(ID3D12GraphicsCommandList* cmdList)
{
	// nullptr�`�F�b�N
	assert(device);
	assert(cmdList);

	// ���_�o�b�t�@�̐ݒ�
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// �f�X�N���v�^�q�[�v�̔z��
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

	// �萔�o�b�t�@�r���[���Z�b�g
	//cmdList->SetGraphicsRootConstantBufferView(0, constBuff->GetGPUVirtualAddress());
	// �V�F�[�_���\�[�X�r���[���Z�b�g
	cmdList->SetGraphicsRootDescriptorTable(1, gpuDescHandleSRV);
	// �`��R�}���h
	cmdList->DrawInstanced((UINT)std::distance(particles.begin(), particles.end()), 1, 0, 0);
}

void ParticleM::LoadTexture(const std::string& filename)
{
	HRESULT result = S_FALSE;

	TexMetadata metadata{};
	ScratchImage scratchImg{};

	// �t�@�C���p�X������
	string filepath = filename;

	// ���j�R�[�h������ɕϊ�
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, filepath.c_str(), -1, wfilepath, _countof(wfilepath));

	// WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(wfilepath, WIC_FLAGS_NONE, &metadata, scratchImg);
	assert(SUCCEEDED(result));

	ScratchImage mipChain{};
	// �~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		TEX_FILTER_DEFAULT, 0, mipChain);
	if (SUCCEEDED(result)) {
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	// �ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = MakeSRGB(metadata.format);

	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format, metadata.width, (UINT)metadata.height, (UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps =
		CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	// �e�N�X�`���p�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // �e�N�X�`���p�w��
		nullptr, IID_PPV_ARGS(&texbuff));
	assert(SUCCEEDED(result));

	// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata.mipLevels; i++) {
		const Image* img = scratchImg.GetImage(i, 0, 0); // ���f�[�^���o
		result = texbuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // �S�̈�փR�s�[
			img->pixels,          // ���f�[�^�A�h���X
			(UINT)img->rowPitch,  // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}

	// �V�F�[�_���\�[�X�r���[�쐬
	cpuDescHandleSRV = CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);
	gpuDescHandleSRV = CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), 0, descriptorHandleIncrementSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // �ݒ�\����
	D3D12_RESOURCE_DESC resDesc = texbuff->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2D�e�N�X�`��
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texbuff.Get(), //�r���[�Ɗ֘A�t����o�b�t�@
		&srvDesc, //�e�N�X�`���ݒ���
		cpuDescHandleSRV
	);
}

void ParticleM::InitializeDescriptorHeap()
{
	HRESULT result = S_FALSE;

	// �f�X�N���v�^�q�[�v�𐶐�	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = 1; // �V�F�[�_�[���\�[�X�r���[1��
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//����
	if (FAILED(result)) {
		assert(0);
	}

	// �f�X�N���v�^�T�C�Y���擾
	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void ParticleM::CreateModel()
{
	HRESULT result = S_FALSE;

	UINT sizeVB = static_cast<UINT>(sizeof(vertices));

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeVB);

	// ���_�o�b�t�@����
	result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertBuff));
	assert(SUCCEEDED(result));

	// ���_�o�b�t�@�ւ̃f�[�^�]��
	//VertexPosNormalUv* vertMap = nullptr;
	VertexPos* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff->Unmap(0, nullptr);
	}

	// ���_�o�b�t�@�r���[�̍쐬
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(vertices);
	vbView.StrideInBytes = sizeof(vertices[0]);
}

void ParticleM::Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,
	float start_scale, float end_scale)
{
	// ���X�g�ɗv�f��ǉ�
	particles.emplace_front();
	// �ǉ������v�f�̎Q��
	Particle0& p = particles.front();
	// �l�̃Z�b�g
	p.position = position;
	p.velocity = velocity;
	p.accel = accel;
	p.num_frame = life;
	p.s_scale = start_scale;
	p.e_scale = end_scale;
	p.scale = start_scale;
}