#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include "ImGuiManager.h"
#include "Vector3.h"
#include "GameTitleScene.h"
#include "Camera.h"

class GameScene
{
private:
	enum Scene {
		Title,
		Scene_1,
		GameClear,
		GameOver
	};
	Scene scene;

public:
	GameScene();
	~GameScene();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dXCommon);

	/// <summary>
	/// ���
	/// </summary>
	void Finalize();

	/// <summary>
	/// �I�u�W�F�N�g�̏�����
	/// </summary>
	/// <param name="dXCommon"></param>
	void ObjectInitialize(DirectXCommon* dXCommon);

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void ObjectUpdate();

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void ObjectDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �I�u�W�F�N�g�̉��
	/// </summary>
	void ObjectFinalize();

	/// <summary>
	/// �X�v���C�g������
	/// </summary>
	void SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g�̍X�V
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// �X�v���C�g�̕`��
	/// </summary>
	void TitleDraw(DirectXCommon* dXCommon);
	void GameDraw(DirectXCommon* dXCommon);
	void GameClearDraw(DirectXCommon* dXCommon);
	void GameOverDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �X�v���C�g�̉��
	/// </summary>
	void SpriteFinalize();

	// �p�[�e�B�N���̏�����
	void ParticleInitialize();

	void ParticleUpdate();

	void ParticleDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �Q�[���̃��Z�b�g
	/// </summary>
	void GameReset();

	/// <summary>
	/// �����蔻��
	/// </summary>
	int CheckCollision(XMFLOAT3 object, XMFLOAT3 scale);

private:
	// ����
	Input* input = nullptr;
	// ���f��
	Model* Model[5];
	// �I�u�W�F�N�g
	Object3d* object3d[5];
	// �X�v���C�g
	Sprite* sprite = nullptr;
	Sprite title;
	Sprite gameClear;
	Sprite gameOver;
	Sprite hP;
	Sprite hP1;
	SpriteCommon spriteCommon_;

	// �p�[�e�B�N��
	ParticleManager* particleMan = nullptr;
	//ParticleManager* particleMan1 = nullptr;

	DirectXCommon* dXCommon = nullptr;

	ImGuiManager* imGuiManager = nullptr;
	GameTitleScene* gTS = nullptr;
	Camera* camera = nullptr;

	XMFLOAT3 position[5]{};
	XMFLOAT3 rotation[5]{};
	XMFLOAT3 scale[5]{};
	XMFLOAT3 eye[5]{};

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;
	int time = 0;
};
