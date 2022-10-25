#include "WinApp.h"
#include "Windows.h"

void WinApp::Initialize()
{
	// �E�B���h�E�T�C�Y
	const int WIN_WIDTH = 1280; // �E�B���h�E����
	const int WIN_HEIGHT = 720; // �E�B���h�E�c��

	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;    // �E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"DirectXGame";       // �E�B���h�N���X��
	w.hInstance = GetModuleHandle(nullptr); // �E�B���h�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);// �J�[�\���w��

	// �E�B���h�N���X��OS�ɓo�^����
	RegisterClassEx(&w);
	// �E�B���h�T�C�Y{X���W�@Y���W�@�����@�c��}
	RECT wrc = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	// �����ŃT�C�Y��␳����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�I�u�W�F�N�g�̐���
	HWND hwnd = CreateWindow(w.lpszClassName, // �N���X��
		L"DirectXGame",       // �^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,  // �W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,        // �W��X���W (05�ɔC����)
		CW_USEDEFAULT,        // �W��Y���W (05�ɔC����)
		wrc.right - wrc.left, // �E�B���h�E����
		wrc.bottom - wrc.top, // �E�B���h�E�c��
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

	// �E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{

}