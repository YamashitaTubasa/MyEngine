#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GameScene.h"
#include "Camera.h"

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

	// Camera�̏�����
	Camera* camera = nullptr;
	camera = new Camera();
	camera->Initialize();

	// �X�v���C�g
	SpriteCommon spriteCommon;

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height,camera);
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// �Q�[���V�[���̏�����
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();

#pragma endregion ��ՃV�X�e���̏�����

#pragma region �V�[���̏�����

	gameScene->Initialize(dXCommon, winApp, spriteCommon);
	
#pragma endregion �V�[���̏�����

	while (true) {

	#pragma region ��ՃV�X�e���̍X�V

		// Windows�̃��b�Z�[�W����
		if (winApp->ProcessMessage()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

	#pragma endregion ��ՃV�X�e���̍X�V

	#pragma region �V�[���̍X�V

		// �Q�[���V�[���̍X�V
		gameScene->Update();
		
	#pragma endregion �V�[���̍X�V

	#pragma region �V�[���̕`��

		// �Q�[���V�[���̕`��
		gameScene->Draw(dXCommon);

	#pragma endregion �V�[���̕`��

	}
#pragma region �V�[���̏I��

	// �Q�[���V�[���̉��
	gameScene->Finalize();
	
#pragma endregion �V�[���̏I��

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