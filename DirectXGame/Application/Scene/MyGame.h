#pragma once

#include "TYFramework.h"
#include "GameScene.h"

// �Q�[���S��
class MyGame : public TYFramework
{
public: // �����o�֐�
	// ������
	void Initialize() override;

	// �I��
	void Finalize() override;

	// ���t���[���X�V
	void Update() override;

	// �`��
	void Draw() override;

private:
	GameScene* gameScene = nullptr;
};
