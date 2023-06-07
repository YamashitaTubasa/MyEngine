#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp final
{
public: // �ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	// WindowsAPI�̏�����
	void Initialize();

	// �I��
	void Finalize();

	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	// ���b�Z�[�W�̏���
	bool ProcessMessage();

public:
	static WinApp* GetInstance();

private:
	WinApp() = default;
	~WinApp() = default;
	WinApp(const WinApp&) = delete;
	WinApp& operator=(const WinApp&) = delete;

public: // �萔
	// �E�B���h�E����
	static const int window_width = 1280;
	// �E�B���h�E�c��
	static const int window_height = 720;

private:
	// �E�B���h�E�n���h��
	HWND hwnd = nullptr;
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wc{};
};