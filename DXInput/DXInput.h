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

#define MaxCountrollers 4

/// <summary>
/// �Q�[���p�b�h
/// </summary>
class DXInput
{
public:
    struct CountrolerState
    {
        XINPUT_STATE state;
        bool Connected;
    };
    CountrolerState GamePad;

public:// �����o�֐�
    DXInput();
    ~DXInput();

    void InputProcess();

    void XInputInvaid();

    /*HRESULT UpdateCountrollerState();*/

    XINPUT_STATE GetState() const { return state; }

private:// �����o�ϐ�
    WinApp* winApp = nullptr;    // WindowsAPI
    XINPUT_STATE state;          // �R���g���[���[�̏�Ԃ̎擾
    XINPUT_VIBRATION vibration;  // �o�C�u���[�V����

private:
    static int  pad_A, pad_B, pad_X, pad_Y;
    static int pad_leftShoulder, pad_rightShoulder;
    static int pad_left, pad_right, pad_up, pad_down;
};