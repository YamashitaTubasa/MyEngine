#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp
{
public: // �ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static int GetWinWidth(); // �E�B���h�E�̉����擾
	static int GetWinHeight(); // �E�B���h�E�̏c���擾
	static double GetFrameTime(); // 1�t���[��������̎��Ԏ擾

public: // �����o�֐�
	// WindowsAPI�̏�����
	void Initialize();

	// �I��
	void Finalize();

	// 1�t���[���̎��Ԃ̏���
	void CalculationFrameTime();

	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	// ���b�Z�[�W�̏���
	bool ProcessMessage();

public: // �萔
	// �E�B���h�E����
	static const int window_width = 1280;
	// �E�B���h�E�c��
	static const int window_height = 720;
	// �t���[���^�C��
	static double frameTime;

private:
	LARGE_INTEGER m_freq = { 0 };
	LARGE_INTEGER m_starttime = { 0 };
	LARGE_INTEGER m_nowtime = { 0 };
	LARGE_INTEGER m_frametime_a = { 0 };
	LARGE_INTEGER m_frametime_b = { 0 };

	// �E�B���h�E�n���h��
	HWND hwnd = nullptr;
	// �E�B���h�E�N���X�̐ݒ�
	WNDCLASSEX wc{};
};