#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp
{
public: // 静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	// WindowsAPIの初期化
	void Initialize();
	// WindowsAPIの更新
	void Update();

};