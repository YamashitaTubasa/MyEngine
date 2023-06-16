#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GameScene.h"
#include "Camera.h"
#include "ImGuiManager.h"

class TYFramework
{
public:
	// ���s
	void Run();

public: // �����o�֐�
	// ������
	virtual void Initialize();

	// �I��
	virtual void Finalize();

	// ���t���[���X�V
	virtual void Update();

	// �`��
	virtual void Draw() = 0;

	// �I���`�F�b�N
	virtual bool IsEndRequst() { return endRequst_; }


public:
	virtual ~TYFramework() = default;

private:
	// �Q�[���I���t���O
	bool endRequst_ = false;

protected:
	// �X�v���C�g
	SpriteCommon spriteCommon;
	DirectXCommon* dXCommon = nullptr;
	WinApp* winApp = nullptr;
	Input* input = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	Camera* camera = nullptr;
};

