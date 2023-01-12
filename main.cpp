#include "Input/Input.h"
#include "Platform/WinApp.h"
#include "Platform/DirectXCommon.h"
//#include "2d/SpriteCommon.h"
#include "2d/Sprite.h"
#include "3d/Model.h"
#include "3d/Object3d.h"

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
	/*SpriteCommon* spriteCommon = nullptr;
	spriteCommon = new SpriteCommon();
	spriteCommon->Initialize();*/

#pragma endregion ��ՃV�X�e���̏�����

#pragma region �ŏ��̃V�[���̏�����

	// �X�v���C�g
	Sprite* sprite = new Sprite();
	//sprite->Initialize(spriteCommon);
	Sprite title;
	SpriteCommon spriteCommon_;
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/mario.jpg", dXCommon->GetDevice());
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720);
	title.SetTexNumber(0);

	// �^�C�g���̑傫���̐ݒ�
	title.SetPosition(XMFLOAT3(300, 100, 0));
	title.SetScale(XMFLOAT2(414 * 0.5, 410 * 0.5));
	title.SpriteTransferVertexBuffer(title);
	title.SpriteUpdate(title, spriteCommon_);

	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height );
	// OBJ���烂�f���f�[�^��ǂݍ���
	Model* model = Model::LoadFromOBJ("kagi");
	// 3D�I�u�W�F�N�g����
	Object3d* object3d = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	object3d->SetModel(model);
	object3d->SetPosition(XMFLOAT3(0, -20, 0));
	object3d->SetRotation(XMFLOAT3(0, 90, 0));
	
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

		//sprite->Update();
		// 3D�I�u�W�F�N�g�X�V
		object3d->Update();

	#pragma endregion �ŏ��̃V�[���̍X�V

		// �`��O����
		dXCommon->PreDraw();

	#pragma region �ŏ��̃V�[���̕`��

	#pragma region 3D�I�u�W�F�N�g�`��

		// 3D�I�u�W�F�N�g�`��O����
		Object3d::PreDraw(dXCommon->GetCommandList());

		// 3D�I�u�W�F�N�g�̕`��
		object3d->Draw();

		// 3D�I�u�W�F�N�g�`��㏈��
		Object3d::PostDraw();

	#pragma endregion 3D�I�u�W�F�N�g�`��

		//Sprite::SpritePipelineSet spritePipelineSet;
		//sprite->Draw(spritePipelineSet.pipelineSet);
		sprite->SpriteCommonBeginDraw(dXCommon->GetCommandList(), spriteCommon_);
		title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);
		
	#pragma endregion �ŏ��̃V�[���̕`��

		// �`��㏈��
		dXCommon->PostDraw();
	}
#pragma region �ŏ��̃V�[���̏I��

	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;

	// 3D�I�u�W�F�N�g���
	delete object3d;
	// 3D���f�����
	delete model;

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


#pragma endregion ��ՃV�X�e���̏I��

	return 0;
}