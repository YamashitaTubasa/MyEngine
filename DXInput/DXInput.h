#pragma once

#include <dwrite.h>
#include <wchar.h>
#include <wrl/client.h>
#include <random>
#include <xinput.h>
#include "WinApp/WinApp.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment (lib, "xinput.lib")

/// <summary>
/// ゲームパッド
/// </summary>
class DXInput
{
public:// メンバ関数
    DXInput();
    ~DXInput();

    void InputProcess();

    XINPUT_STATE GetState() const { return state; }

private:// メンバ変数
    WinApp* winApp = nullptr;    // WindowsAPI
    XINPUT_STATE state;          // コントローラーの状態の取得
    XINPUT_VIBRATION vibration;  // バイブレーション

private:
    static int  pad_A, pad_B, pad_X, pad_Y;
    static int pad_leftShoulder, pad_rightShoulder;
    static int pad_left, pad_right, pad_up, pad_down;
};