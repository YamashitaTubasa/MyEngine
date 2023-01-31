#pragma once

#include <xaudio2.h>
#include <fstream>
#include <wrl.h>
#include <DirectXMath.h>
#include <map>
#include <string>

#pragma comment(lib, "xaudio2.lib")

//�萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
struct ConstBufferDataMaterial {
	DirectX::XMFLOAT4 color;//�F(RGBA)
};

//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
struct ConstBufferDataTransform {
	DirectX::XMMATRIX mat; //3D�ϊ��s��
};

// �`�����N�w�b�_
struct ChunkHeader
{
	char id[4]; // �`�����N�O��ID
	int32_t size; // �`�����N�T�C�Y
};

// RIFF�w�b�_�`�����N
struct RiffHeader
{
	ChunkHeader chunk; // "RIFF"
	char type[4]; // "WAVE"
};

// FMT�`�����N
struct FormatChunk {
	ChunkHeader chunk; // "fmt"
	WAVEFORMATEX fmt; // �g�`�t�H�[�}�b�g
};

// �����f�[�^
struct SoundData {
	// �g�`�t�H�[�}�b�g
	WAVEFORMATEX wfex;
	// �o�b�t�@�̐擪�A�h���X
	BYTE* pBuffer;
	// �o�b�t�@�̃T�C�Y
	unsigned int bufferSize;
};

// =============
// �I�[�f�B�I�N���X
// =============
class Audio final
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	Audio() = default;
	~Audio() = default;

public:
	Audio(const Audio& obj) = delete;
	Audio& operator=(const Audio& obj) = delete;

	// �C���X�^���X�𐶐�
	static Audio* GetInstance();

	// ������
	void Initialize(const std::string& directoryPath = "Resources/BGM/");
	// ���
	void Finalize();
	/// <summary>
	/// �����f�[�^�̓ǂݍ���
	/// </summary>
	/// <param name="filename">WAV�t�@�C����</param>
	void LoadWave(const std::string& filename);
	/// <summary>
	/// �����f�[�^���
	/// </summary>
	/// <param name="soundData">�T�E���h�f�[�^</param>
	void Unload(SoundData* soundData);
	/// <summary>
	/// �����Đ�
	/// </summary>
	/// <param name="filename">WAV�t�@�C����</param>
	void PlayWave(const std::string& filename);
	/// <summary>
	/// �����̃��[�v�Đ�
	/// </summary>
	/// <param name="filename">WAV�t�@�C����</param>
	void LoopPlayWave(const std::string& filename);
	/// <summary>
	/// ������~
	/// </summary>
	/// <param name="filename">WAV�t�@�C����</param>
	void StopWave(const std::string& filename);
	/// <summary>
	/// ���ʒ���
	/// </summary>
	/// <param name="filename">WAV�t�@�C����</param>
	/// <param name="volume">����</param>
	void SetVolume(const std::string& filename, float volume);

public:
	IXAudio2* GetxAudio2() { return xAudio2.Get(); }
	float GetVolume()const { return mVolume; }

private:
	HRESULT result;
	ComPtr<IXAudio2> xAudio2; // XAudio2�C���^�[�t�F�C�X
	IXAudio2MasteringVoice* mVoice; // �}�X�^�[�{�C�X
	IXAudio2SourceVoice* sVoice; // �\�[�X�{�C�X
	XAUDIO2_BUFFER buf{};

	// �T�E���h�f�[�^�̘A�z�z��
	std::map<std::string, SoundData> soundDatas_;
	// �T�E���h�i�[�f�B���N�g��
	std::string directoryPath_;

	float mVolume;
};

