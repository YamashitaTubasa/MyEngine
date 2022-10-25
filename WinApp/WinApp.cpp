#include "WinApp.h"
#include "Windows.h"

void WinApp::Initialize()
{
	// ウィンドウサイズ
	const int WIN_WIDTH = 1280; // ウィンドウ横幅
	const int WIN_HEIGHT = 720; // ウィンドウ縦幅

	// ウィンドウクラスの設定
	WNDCLASSEX w{};
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;    // ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";       // ウィンドクラス名
	w.hInstance = GetModuleHandle(nullptr); // ウィンドハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);// カーソル指定

	// ウィンドクラスをOSに登録する
	RegisterClassEx(&w);
	// ウィンドサイズ{X座標　Y座標　横幅　縦幅}
	RECT wrc = { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	// 自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウオブジェクトの生成
	HWND hwnd = CreateWindow(w.lpszClassName, // クラス名
		L"DirectXGame",       // タイトルバーの文字
		WS_OVERLAPPEDWINDOW,  // 標準的なウィンドウスタイル
		CW_USEDEFAULT,        // 標準X座標 (05に任せる)
		CW_USEDEFAULT,        // 標準Y座標 (05に任せる)
		wrc.right - wrc.left, // ウィンドウ横幅
		wrc.bottom - wrc.top, // ウィンドウ縦幅
		nullptr,
		nullptr,
		w.hInstance,
		nullptr);

	// ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update()
{

}