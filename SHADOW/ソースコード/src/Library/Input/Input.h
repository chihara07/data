#pragma once

//�L�[���̌�
constexpr int  KEY_BUF_LEN = 256;

class CInput {
private:
	//���݃t���[���̃L�[���
	static char _CurrentKeyBuf[KEY_BUF_LEN];
	//���݃t���[���̃p�b�h���
	static char _CurrentPadBuf;
	//�O�t���[���̃L�[���
	static char _PreKeyBuf[KEY_BUF_LEN];
	//�O�t���[���̃p�b�h���
	static char _PrePadBuf;
	//�p�b�h�̉E�X�e�B�b�N�̉������̓��͏��
	static int _PadRstickX;
	//�p�b�h�̉E�X�e�B�b�N�̏c�����̓��͏��
	static int _PadRstickY;
	//���݃t���[���̃p�b�h��XInput���
	static XINPUT_STATE _CurrentXinput;
	//�O�t���[���̃p�b�h��XInput���
	static XINPUT_STATE _PreXinput;
public:
	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	static void Step();

	//�������ꂽ
	static bool IsKeyPush(int key_code);

	//�������ꂽ(�p�b�h)
	static bool IsPadPush(int pad_code);

	//�����������Ă��邩
	static bool IsKeyKeep(int key_code);

	//�����������Ă��邩(�p�b�h)
	static bool IsPadKeep(int pad_code);

	//�������������ꂽ��
	static bool IsKeyRelease(int key_code);

	//�������������ꂽ��(�p�b�h)
	static bool IsPadRelease(int pad_code);

	//�P���ɉ�����Ă��邩
	static bool IsKeyDown(int key_code);

	//�P���ɉ�����Ă��邩(�p�b�h)
	static bool IsPadDown(int pad_code);

	//�������ꂽ(XInput)
	static bool IsXPadPush(int pad_code);

	//�����������Ă��邩(XInput)
	static bool IsXPadKeep(int pad_code);

	//�������������ꂽ��(XInput)
	static bool IsXPadRelease(int pad_code);

	//�P���ɉ�����Ă��邩(XInput)
	static bool IsXPadDown(int pad_code);

	//�p�b�h�̉E�X�e�B�b�N�̏���͂����邩
	static bool IsPadRstickUp();

	//�p�b�h�̉E�X�e�B�b�N�̉����͂����邩
	static bool IsPadRstickDown();

	//�p�b�h�̉E�X�e�B�b�N�̉E���͂����邩
	static bool IsPadRstickRight();

	//�p�b�h�̉E�X�e�B�b�N�̍����͂����邩
	static bool IsPadRstickLeft();

	//�p�b�h�̍��X�e�B�b�N��X�����͎擾
	static float GetLstickXInput();

	//�p�b�h�̍��X�e�B�b�N��Y�����͎擾
	static float GetLstickYInput();

	//�p�b�h�̉E�X�e�B�b�N��X�����͎擾
	static float GetRstickXInput();

	//�p�b�h�̉E�X�e�B�b�N��Y�����͎擾
	static float GetRstickYInput();
};
