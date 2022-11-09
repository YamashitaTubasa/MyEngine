#pragma once
#include <Windows.h>

// WindowsAPI
class WinApp
{
public: // 静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static int GetWinWidth(); // ウィンドウの横幅取得
	static int GetWinHeight(); // ウィンドウの縦幅取得
	static double GetFrameTime(); // 1フレームあたりの時間取得

public: // メンバ関数
	// WindowsAPIの初期化
	void Initialize();

	// 終了
	void Finalize();

	// 1フレームの時間の処理
	void CalculationFrameTime();

	// getter
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return wc.hInstance; }

	// メッセージの処理
	bool ProcessMessage();

public: // 定数
	// ウィンドウ横幅
	static const int window_width = 1280;
	// ウィンドウ縦幅
	static const int window_height = 720;
	// フレームタイム
	static double frameTime;

private:
	LARGE_INTEGER m_freq = { 0 };
	LARGE_INTEGER m_starttime = { 0 };
	LARGE_INTEGER m_nowtime = { 0 };
	LARGE_INTEGER m_frametime_a = { 0 };
	LARGE_INTEGER m_frametime_b = { 0 };

	// ウィンドウハンドル
	HWND hwnd = nullptr;
	// ウィンドウクラスの設定
	WNDCLASSEX wc{};
};