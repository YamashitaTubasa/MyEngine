#include "GameScene.h"

void GameScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp)
{
	// ���͂̏�����
	input = new Input();
	input->Initialize(winApp);
	// �I�u�W�F�N�g�̏�����
	ObjectInitialize(dXCommon);
	// �X�v���C�g�̏�����
	SpriteInitialize(dXCommon);
}

void GameScene::Update()
{
	// ���͂̍X�V
	input->Update();

	switch (scene) {
		case Title:
			if (input->TriggerKey(DIK_SPACE)) {
				scene = Scene_1;
			}
			break;
		case Scene_1:
			time++;
			if (time >= 1000) {
				scene = GameClear;
			}
			// �I�u�W�F�N�g�̍X�V
			ObjectUpdate();
			// �X�v���C�g�̍X�V
			SpriteUpdate();
			break;
		case GameClear:
			if (input->TriggerKey(DIK_SPACE)) {
				GameReset();
				scene = Title;
			}
			break;
		case GameOver:
			if (input->TriggerKey(DIK_SPACE)) {
				GameReset();
				scene = Title;
			}
			break;
	}
}

void GameScene::Draw(DirectXCommon* dXCommon)
{
	// �`��O����
	dXCommon->PreDraw();

	switch (scene) {
		case Title:
			#pragma region �X�v���C�g�̕`��

			// �^�C�g���̕`��
			TitleDraw(dXCommon);

			#pragma endregion �X�v���C�g�̕`��
			break;
		case Scene_1:
			#pragma region 3D�I�u�W�F�N�g�`��

			// 3D�I�u�W�F�N�g�̕`��
			ObjectDraw(dXCommon);

			#pragma endregion 3D�I�u�W�F�N�g�`��

			break;
		case GameClear:
			// �Q�[���N���A�̕`��
			GameClearDraw(dXCommon);
			break;
		case GameOver:
			//�Q�[���I�[�o�[�̕`��
			GameOverDraw(dXCommon);
			break;
	}

	// �`��㏈��
	dXCommon->PostDraw();
}

void GameScene::Finalize()
{
	// ���͊J��
	delete input;
	input = nullptr;
	// �I�u�W�F�N�g�̉��
	ObjectFinalize();
	// �X�v���C�g�̉��
	SpriteFinalize();
}

void GameScene::ObjectInitialize(DirectXCommon* dXCommon) {

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// OBJ���烂�f���f�[�^��ǂݍ���
	Model[0] = Model::LoadFromOBJ("fighter");
	Model[1] = Model::LoadFromOBJ("ironSphere");
	Model[2] = Model::LoadFromOBJ("skydome");
	// 3D�I�u�W�F�N�g����
	for (int i = 0; i < 5; i++) {
		object3d[i] = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	object3d[0]->SetModel(Model[0]);
	object3d[1]->SetModel(Model[1]);
	object3d[2]->SetModel(Model[2]);
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);

	position[1] = { 0,0,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetScale({ 5,5,5 });
	object3d[1]->SetRotation({ 0, 90, 0 });

	object3d[2]->SetPosition({ 0,-40,0 });
	object3d[2]->SetScale({ 100, 100, 100 });
	object3d[2]->SetRotation({0,100,20});
}

void GameScene::ObjectUpdate()
{
	// 3D�I�u�W�F�N�g�X�V
	for (int i = 0; i < 5; i++) {
		object3d[i]->Update();
	}

	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetRotation(rotation[0]);
	object3d[1]->SetPosition(position[1]);

	if (input->PushKey(DIK_W)) {
		position[0].y += 0.4;
	}

	if (input->PushKey(DIK_A)) {
		position[0].x -= 0.4;
		isPush_A = true;
	}
	else {
		isPush_A = false;
	}
	if (isPush_D == false) {
		if (isPush_A == true) {
			if (rotation[0].x >= -20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= -20) {
				rotation[0].x = -20;
			}
		}
		else {
			if (rotation[0].x >= -20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 0) {
				rotation[0].x = 0;
			}
		}
	}

	if (input->PushKey(DIK_S)) {
		position[0].y -= 0.4;
	}

	if (input->PushKey(DIK_D)) {
		position[0].x += 0.4;
		isPush_D = true;
	}else {
		isPush_D = false;
	}
	if (isPush_A == false) {
		if (isPush_D == true) {
			if (rotation[0].x <= 20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 20) {
				rotation[0].x = 20;
			}
		}
		else {
			if (rotation[0].x <= 20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= 0) {
				rotation[0].x = 0;
			}
		}
	}

	position[1].z -= 1;
	if (position[1].z < -100) {
		position[1].z = 50;
	}

	// �v���C���[�ƓS���̓����蔻��
	if (CheckCollision(object3d[1]->GetPosition(), object3d[1]->GetScale()) == true) {
		playerHp -= 1;
	}
	if (playerHp == 0) {
		scene = GameOver;
	}
}

void GameScene::ObjectDraw(DirectXCommon* dXCommon)
{
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < 5; i++) {
		object3d[i]->Draw();
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
}

void GameScene::ObjectFinalize()
{
	// 3D�I�u�W�F�N�g���
	for (int i = 0; i < 5; i++) {
		delete object3d[i];
	}
	// 3D���f�����
	for (int i = 0; i < 5; i++) {
		delete Model[i];
	}
}

void GameScene::SpriteInitialize(DirectXCommon* dXCommon)
{
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	sprite->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/gametitle.png", dXCommon->GetDevice());
	sprite->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/gameclear.png", dXCommon->GetDevice());
	sprite->SpriteCommonLoadTexture(spriteCommon_, 2, L"Resources/gameover.png", dXCommon->GetDevice());

	// �^�C�g���̑傫���̐ݒ�
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720);
	title.SetTexNumber(0);
	title.SetPosition(XMFLOAT3(0, 0, 0));
	title.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	title.SpriteTransferVertexBuffer(title);
	title.SpriteUpdate(title, spriteCommon_);

	// �Q�[���N���A�̑傫���̐ݒ�
	gameClear.SpriteCreate(dXCommon->GetDevice(), 1280, 720);
	gameClear.SetTexNumber(1);
	gameClear.SetPosition(XMFLOAT3(0, 0, 0));
	gameClear.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	gameClear.SpriteTransferVertexBuffer(gameClear);
	gameClear.SpriteUpdate(gameClear, spriteCommon_);

	// �Q�[���I�[�o�[�̑傫���̐ݒ�
	gameOver.SpriteCreate(dXCommon->GetDevice(), 1280, 720);
	gameOver.SetTexNumber(2);
	gameOver.SetPosition(XMFLOAT3(0, 0, 0));
	gameOver.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	gameOver.SpriteTransferVertexBuffer(gameOver);
	gameOver.SpriteUpdate(gameOver, spriteCommon_);

	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());
}

void GameScene::SpriteUpdate()
{
}

void GameScene::TitleDraw(DirectXCommon* dXCommon)
{
	sprite->SpriteCommonBeginDraw(dXCommon->GetCommandList(), spriteCommon_);
	title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);
}

void GameScene::GameClearDraw(DirectXCommon* dXCommon)
{
	sprite->SpriteCommonBeginDraw(dXCommon->GetCommandList(), spriteCommon_);
	gameClear.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gameClear.vbView);
}

void GameScene::GameOverDraw(DirectXCommon* dXCommon)
{
	sprite->SpriteCommonBeginDraw(dXCommon->GetCommandList(), spriteCommon_);
	gameOver.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gameOver.vbView);
}


void GameScene::SpriteFinalize()
{
	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;
}

void GameScene::GameReset()
{
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);
	position[1] = { 0,5,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetRotation({ 0, 90, 0 });
	object3d[1]->SetScale({ 5,5,5 });

	playerHp = 3;
	time = 0;
}

int GameScene::CheckCollision(XMFLOAT3 position, XMFLOAT3 scale) {
	//�I�u�W�F�N�g�̍��W
	float objLeftX = position.x - scale.x;
	float objRightX = position.x + scale.x;
	float objTopY = position.y + scale.y;
	float objBottomY = position.y - scale.y;
	float objFrontZ = position.z - scale.z;
	float objBZ = position.z + scale.z;
	//�v���C���[�̍��W
	float playerLeftX = object3d[0]->GetPosition().x - object3d[0]->GetScale().x;
	float playerRightX = object3d[0]->GetPosition().x + object3d[0]->GetScale().x;
	float playerTopY = object3d[0]->GetPosition().y + object3d[0]->GetScale().y;
	float playerBottomY = object3d[0]->GetPosition().y - object3d[0]->GetScale().y;
	float playerFrontZ = object3d[0]->GetPosition().z - object3d[0]->GetScale().z;
	float playerBZ = object3d[0]->GetPosition().z + object3d[0]->GetScale().z;

	if (objLeftX < playerRightX && playerLeftX < objRightX) {
		if (objBottomY < playerTopY && playerBottomY < objTopY) {
			if (objFrontZ < playerBZ && playerFrontZ < objBZ) {
				return true;
			}
		}
	}
}
