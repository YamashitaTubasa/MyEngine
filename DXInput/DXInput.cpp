#include "DXInput.h"

DXInput::DXInput()
{
}

DXInput::~DXInput()
{
}

void DXInput::InputProcess() {

    /*XInputGetState(0, &state);*/
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) pad_left = 1;  //�Q�[���p�b�h�\���L�[��
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) pad_right = 1;//�Q�[���p�b�h�\���L�[�E
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) pad_up = 1;      //�Q�[���p�b�h�\���L�[��
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) pad_down = 1;  //�Q�[���p�b�h�\���L�[��
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) pad_leftShoulder = 1;  //�Q�[���p�b�hL
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) pad_rightShoulder = 1;//�Q�[���p�b�hR
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) pad_A = 1;//�Q�[���p�b�hA
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) pad_B = 1;//�Q�[���p�b�hB
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) pad_X = 1;//�Q�[���p�b�hX
    //if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) pad_Y = 1;//�Q�[���p�b�hY

    //�Q�[���p�b�h�f�b�h�]�[������
    if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
        state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && 
            state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        state.Gamepad.sThumbLX = 0;
        state.Gamepad.sThumbLY = 0;
    }
}

