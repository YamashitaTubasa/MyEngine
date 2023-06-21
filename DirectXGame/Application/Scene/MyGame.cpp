#include "MyGame.h"

void MyGame::Initialize()
{	
	// ���N���X�̏���������
	TYFramework::Initialize();

	//dXCommon = DirectXCommon::GetInstance();

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(spriteCommon);
}

void MyGame::Finalize()
{
	// �Q�[���V�[���̉��
	gameScene->Finalize();
	delete gameScene;

	// ���N���X�̏I������
	TYFramework::Finalize();
}

void MyGame::Update()
{
	// ���N���X�̍X�V����
	TYFramework::Update();

	// �Q�[���V�[���̍X�V
	gameScene->Update();
}

void MyGame::Draw()
{
#pragma region �`��

	// �`��O����
	dXCommon->PreDraw();

	// �Q�[���V�[���̕`��
	gameScene->Draw(spriteCommon);

	// ImGui�`��
	//imGuiManager->Draw(dXCommon);

	// �`��㏈��
	dXCommon->PostDraw();

#pragma endregion
}
