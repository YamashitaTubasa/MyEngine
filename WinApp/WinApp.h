#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp
{
public: // �ÓI�����o�֐�
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // �����o�֐�
	// WindowsAPI�̏�����
	void Initialize();
	// WindowsAPI�̍X�V
	void Update();

};