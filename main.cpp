#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
#include "2d/Sprite.h"
#include "3d/Model.h"
#include "3d/Object3d.h"
#include "Scene/GameScene.h"

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

	// �Q�[���V�[���̏�����
	GameScene* gameScene = new GameScene();

#pragma endregion ��ՃV�X�e���̏�����

#pragma region �ŏ��̃V�[���̏�����

	gameScene->Initialize(dXCommon, winApp);
	
#pragma endregion �ŏ��̃V�[���̏�����

	while (true) {

	#pragma region ��ՃV�X�e���̍X�V

		// Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

	#pragma endregion ��ՃV�X�e���̍X�V

	#pragma region �ŏ��̃V�[���̍X�V

		// �Q�[���V�[���̍X�V
		gameScene->Update();
		
	#pragma endregion �ŏ��̃V�[���̍X�V

	#pragma region �ŏ��̃V�[���̕`��

		// �Q�[���V�[���̕`��
		gameScene->Draw(dXCommon);

	#pragma endregion �ŏ��̃V�[���̕`��

	}
#pragma region �ŏ��̃V�[���̏I��

	// �Q�[���V�[���̉��
	gameScene->Finalize();
	
#pragma endregion �ŏ��̃V�[���̏I��

#pragma region ��ՃV�X�e���̏I��

	// WindowsAPI�̏I������
	winApp->Finalize();

	// WindowsAPI���
	delete winApp;
	winApp = nullptr;

	// DirectX���
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;


#pragma endregion ��ՃV�X�e���̏I��

	return 0;
}