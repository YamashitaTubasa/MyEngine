#include "Camera.h"
#include "WinApp.h"

using namespace DirectX;

void Camera::Initialize() 
{
	eye = { 0, 0, -distance }; // ���_���W
	target = { 0, 0, 0 };      // �����_���W
	up = { 0, 1, 0 };          // ������x�N�g��

	UpdateViewMatrix();
	UpdateProjectionMatrix();

	viewProjection = matView * matProjection;
}

void Camera::Update()
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();

	viewProjection = matView * matProjection;
}

void Camera::UpdateViewMatrix()
{
	// �r���[�s��̌v�Z
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void Camera::UpdateProjectionMatrix()
{
	// �������e
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)WinApp::window_width / WinApp::window_height, 0.1f, 1000.0f
	);
}