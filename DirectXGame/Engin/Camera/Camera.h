#pragma once

#include <DirectXMath.h>
#include <wrl.h>

// �J����
class Camera
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// ������
	void Initialize();

	// �X�V
	void Update();

	// �r���[�s��
	void UpdateViewMatrix();

	// �������e
	void UpdateProjectionMatrix();

public:
	const XMMATRIX& GetMatView() { return matView; }
	const XMMATRIX& GetMatProjection() { return matProjection; }
	const XMFLOAT3& GetEye() { return eye; }
	const XMFLOAT3& GetTarget() { return target; }
	const XMFLOAT3& GetUp() { return up; }

	void SetMatView(const XMMATRIX& matView) { this->matView = matView; }
	void SetMatProjection(const XMMATRIX& matProjection) { this->matProjection = matProjection; }
	void SetEye(const XMFLOAT3& eye) { this->eye = eye; }
	void SetTarget(const XMFLOAT3& target) { this->target = target; }
	void SetUp(const XMFLOAT3& up) { this->up = up; }

private:
	XMMATRIX matView;
	XMMATRIX matProjection;
	XMFLOAT3 eye;
	XMFLOAT3 target;
	XMFLOAT3 up;
};