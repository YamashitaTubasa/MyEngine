#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"

// windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// �R���\�[���ւ̕����o��
	OutputDebugStringA("Hellow,DirectX!!\n");

#pragma region ��ՃV�X�e���̏�����

	// WindowsAPI�̏�����
	WinApp* winApp = nullptr;
	winApp = new WinApp();
	winApp->Initialize();

	// DirectX�̏�����
	DirectXCommon* dXCommon = nullptr;
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	Input* input = nullptr;
	input = new Input();
	input->Initialize(winApp);

	// �X�v���C�g���ʕ��̏�����
	SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize();

#pragma endregion ��ՃV�X�e���̏�����

#pragma region �ŏ��̃V�[���̏�����

	// �X�v���C�g
	Sprite* sprite = new Sprite();
	sprite->Initialize(spriteCommon);
	
#pragma endregion �ŏ��̃V�[���̏�����

	while (true) {

	#pragma region ��ՃV�X�e���̍X�V

		// Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		input->Update();

	#pragma endregion ��ՃV�X�e���̍X�V

	#pragma region �ŏ��̃V�[���̍X�V

		sprite->Update();

	#pragma endregion �ŏ��̃V�[���̍X�V

		// �`��O����
		dXCommon->PreDraw();

	#pragma region �ŏ��̃V�[���̕`��

		Sprite::SpritePipelineSet spritePipelineSet;
		sprite->Draw(spritePipelineSet.pipelineSet);
		
	#pragma endregion �ŏ��̃V�[���̕`��

		// �`��㏈��
		dXCommon->PostDraw();
	}
#pragma region �ŏ��̃V�[���̏I��

	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;

#pragma endregion �ŏ��̃V�[���̏I��

#pragma region ��ՃV�X�e���̏I��

	// ���͊J��
	delete input;
	input = nullptr;

	// WindowsAPI�̏I������
	winApp->Finalize();

	// WindowsAPI���
	delete winApp;
	winApp = nullptr;

	// DirectX���
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;

	// �X�v���C�g�̉��
	delete spriteCommon;
	spriteCommon = nullptr;

#pragma endregion ��ՃV�X�e���̏I��

	return 0;
}