#include "Audio.h"

Audio* Audio::GetInstance()
{
	static Audio instance;

	return &instance;
}

void Audio::Initialize(const std::string& directoryPath)
{	
	directoryPath_ = directoryPath;

	// XAudio�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(result));

	// �}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&mVoice);
	assert(SUCCEEDED(result));
}

void Audio::Finalize()
{
	// XAudio2���
	xAudio2.Reset();

	// �����f�[�^���
	std::map<std::string, SoundData>::iterator it = soundDatas_.begin();
	for (; it != soundDatas_.end(); ++it) {
		Unload(&it->second);
	}
	soundDatas_.clear();
}

void Audio::LoadWave(const std::string& filename)
{
	if (soundDatas_.find(filename) != soundDatas_.end()) {
		// �d���ǂݍ��݂Ȃ̂ŁA��������������
		return;
	}

	// �f�B���N�g���p�X�ƃt�@�C������A�����ăt���p�X�𓾂�
	std::string fullpath = directoryPath_ + filename;

	// �@�t�@�C���I�[�v��
	// �t�@�C�����̓X�g���[���̃C���X�^���X
	std::ifstream file;
	// .wav�t�@�C���o�C�i�����[�h�ŊJ��
	file.open(fullpath, std::ios_base::binary);
	// �t�@�C���I�[�v�����s�����o
	assert(file.is_open());

	// �A.WAV�f�[�^�ǂݍ���
	// RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	// �^�C�v��WAVE���`�F�b�N
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}
	// Format�`�����N�̓ǂݍ���
	FormatChunk format = {};
	// �`�����N�w�b�_�[�̊m�F
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	// �`�����N�{�̂̓ǂݍ���
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;;
	file.read((char*)&data, sizeof(data));
	// JUNK�`�����N�����o�����ꍇ
	if (strncmp(data.id, "JUNK", 4) == 0) {
		// �ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size, std::ios_base::cur);
		// �ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	// DATA�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	// WAVE�t�@�C���ƕ���
	file.close();

	// �C�ǂݍ��񂾉����f�[�^��return
	// return����ׂ̉����f�[�^
	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	// �T�E���h�f�[�^��A�z�z��Ɋi�[
	soundDatas_.insert(std::make_pair(filename, soundData));
}

void Audio::Unload(SoundData* soundData) {
	// �o�b�t�@�̃����������
	delete[] soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void Audio::PlayWave(const std::string& filename) {
	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	// ���ǂݍ��݂̌��o
	assert(it != soundDatas_.end());

	// �T�E���h�f�[�^�̎Q�Ƃ��擾
	SoundData& soundData = it->second;;

	// �g�`�t�H�[�}�b�g������SourceVoice�̐���
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();
}

void Audio::LoopPlayWave(const std::string& filename)
{
	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	// ���ǂݍ��݂̌��o
	assert(it != soundDatas_.end());
	// �T�E���h�f�[�^�̎Q�Ƃ��擾
	SoundData& soundData = it->second;

	// �g�`�t�H�[�}�b�g�����Ƃ�SoundVoice�̐���
	result = xAudio2->CreateSourceVoice(&sVoice, &soundData.wfex);
	assert((SUCCEEDED(result)));

	// �Đ�����g�`�f�[�^�̐ݒ�
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// �������[�v
	buf.LoopCount = XAUDIO2_LOOP_INFINITE;

	// �g�`�f�[�^�̍Đ�
	result = sVoice->SubmitSourceBuffer(&buf);
	result = sVoice->Start();
}

void Audio::StopWave(const std::string& filename)
{
	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	// ���ǂݍ��݂̌��o
	assert(it != soundDatas_.end());
	// �T�E���h�f�[�^�̎Q�Ƃ��擾
	SoundData& soundData = it->second;

	// �g�`�t�H�[�}�b�g�����Ƃ�SoundVoice�̐���
	result = xAudio2->CreateSourceVoice(&sVoice, &soundData.wfex);
	assert((SUCCEEDED(result)));

	// �Đ�����g�`�f�[�^�̐ݒ�
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	result = sVoice->SubmitSourceBuffer(&buf);
	result = sVoice->Stop();
	result = sVoice->FlushSourceBuffers();
	sVoice->DestroyVoice();
}

void Audio::SetVolume(const std::string& filename, float volume)
{
	std::map<std::string, SoundData>::iterator it = soundDatas_.find(filename);
	// ���ǂݍ��݂̌��o
	assert(it != soundDatas_.end());
	// �T�E���h�f�[�^�̎Q�Ƃ��擾
	SoundData& soundData = it->second;

	// �g�`�t�H�[�}�b�g�����Ƃ�SoundVoice�̐���
	result = xAudio2->CreateSourceVoice(&sVoice, &soundData.wfex);
	assert((SUCCEEDED(result)));

	// �Đ�����g�`�f�[�^�̐ݒ�
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	result = sVoice->SubmitSourceBuffer(&buf);
	result = sVoice->SetVolume(volume);
}

