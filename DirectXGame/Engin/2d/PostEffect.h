#pragma once

#include "Sprite.h"

/// <summary>
/// �|�X�g�G�t�F�N�g
/// </summary>
class PostEffect : public Sprite
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

	/// <summary>
	/// �`��R�}���h�̔��s
	/// </summary>
	/// <param name="cmdList"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
};

