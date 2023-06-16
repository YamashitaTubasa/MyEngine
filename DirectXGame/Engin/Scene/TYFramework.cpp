#include "TYFramework.h"

void TYFramework::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v 
	{
		// ���t���[���X�V
		Update();

		// �I�����N�G�X�g�������烋�[�v�𔲂���
		if (IsEndRequst()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		// �`��
		Draw();
	}

	// �Q�[���̏I��
	Finalize();
}

void TYFramework::Initialize()
{
	// WindowsAPI�̏�����
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	dXCommon = DirectXCommon::GetInstance();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);

	// ImGui�̏�����
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// Camera�̏�����
	/*camera = new Camera();
	camera->Initialize();*/

	// FBX
	FbxLoader::GetInstance()->Initialize(dXCommon->GetDevice());

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height, camera);
	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
}

void TYFramework::Finalize()
{
	FbxLoader::GetInstance()->Finalize();

	// imgui�̏I������
	imGuiManager->Finalize();
	// imgui�̉��
	delete imGuiManager;
	imGuiManager = nullptr;

	// WindowsAPI�̏I������
	winApp->Finalize();

	// DirectX���
	dXCommon->fpsFixedFinalize();
}

void TYFramework::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		// �Q�[�����[�v�𔲂���
		endRequst_ = true;
	}
}
