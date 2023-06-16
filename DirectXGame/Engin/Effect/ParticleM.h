#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>
#include <string>

//==============
// �p�[�e�B�N��
//==============
class ParticleM
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPos
	{
		XMFLOAT3 pos; // xyz���W
		float scale; // �X�P�[��
	};

	// �p�[�e�B�N��1��
	struct Particle0
	{
		// DirectX::���ȗ�
		using XNFLOAT3 = DirectX::XMFLOAT3;
		// ���W
		XMFLOAT3 position = {};
		// ���x
		XMFLOAT3 velocity = {};
		// �����x
		XMFLOAT3 accel = {};
		// ���݃t���[��
		int frame = 0;
		// �I���t���[��
		int num_frame = 0;
		// �X�P�[��
		float scale = 1.0f;
		// �����l
		float s_scale = 1.0f;
		// �ŏI�l
		float e_scale = 0.0f;
	};

private: // �萔
	static const int vertexCount = 1024; // ���_��

private: // �ÓI�����o�ϐ�
    // �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	static ComPtr<ID3D12Resource> vertBuff;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// ���_�f�[�^�z��
	static VertexPos vertices[vertexCount];

public:// �ÓI�����o�֐�
	/// <summary>
	/// OBJ�t�@�C������p�[�e�B�N���}�l�[�W���[��ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <returns></returns>
	static ParticleM* LoadFromOBJ(const std::string& filename);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	void LoadTexture(const std::string& filename);

	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	void InitializeDescriptorHeap();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	void CreateModel();

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name = "life">��������</param>
	/// <param name = "position">�������W</param>
	/// <param name = "velocity">���x</param>
	/// <param name = "accel">�����x</param>
	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel, float start_scale, float end_scale);

public:
	static void SetDevice(ID3D12Device* device) { ParticleM::device = device; }

private: // �����o�ϐ�
	// �e�I�u�W�F�N�g
	std::forward_list<Particle0> particles;
};