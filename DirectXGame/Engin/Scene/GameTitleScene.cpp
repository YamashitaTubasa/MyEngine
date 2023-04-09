#include "GameTitleScene.h"

using namespace DirectX;

GameTitleScene::GameTitleScene()
{
}

GameTitleScene::~GameTitleScene()
{
	delete particleMan1;
}

void GameTitleScene::Initialize()
{
	particleMan1 = ParticleManager::Create();
	particleMan1->LoadTexture(L"Resources/effect1.png");
	particleMan1->Update();

	for (int i = 0; i < 100; i++) {
		// X,Y,Z���ׂ�[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float md_pos = 10.0f;
		XMFLOAT3 pos{};
		float px = 5;
		float py = 3;
		float pz = 3;
		pos.x = (float)rand() / RAND_MAX * px - px / 2.0f + px;
		pos.y = (float)rand() / RAND_MAX * py - py / 2.0f + py;
		pos.z = (float)rand() / RAND_MAX * pz - pz / 2.0f;
		// X,Y,Z�S��[-0.05f,+0.05f]�Ń����_�����z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		// �d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		// �ǉ�
		particleMan1->Add(60, pos, vel, acc, 1.0f, 0.0);
	}
}

void GameTitleScene::Update()
{
	//// �J�����ړ�
	//if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	//{
	//	if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
	//	else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
	//	if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
	//	else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	//}

	particleMan1->Update();
}

void GameTitleScene::Draw(DirectXCommon* dXCommon)
{
	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�N�W�F�N�g�̕`��
	particleMan1->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();
}
