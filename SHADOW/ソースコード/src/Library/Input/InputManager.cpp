#include "InputManager.h"
#include "DxLib.h"
#include "Input.h"

vector<int> CInputManager::_InputKey;
vector<int> CInputManager::_InputPad;

//���͐��䏉����
void CInputManager::Init() {
	CInput::Init();

	_InputKey.push_back(KEY_INPUT_W);
	_InputKey.push_back(KEY_INPUT_S);
	_InputKey.push_back(KEY_INPUT_D);
	_InputKey.push_back(KEY_INPUT_A);
	_InputKey.push_back(KEY_INPUT_LSHIFT);
	_InputKey.push_back(KEY_INPUT_SPACE);
	_InputKey.push_back(KEY_INPUT_V);
	_InputKey.push_back(KEY_INPUT_Q);
	_InputKey.push_back(KEY_INPUT_E);

	_InputPad.push_back(XINPUT_BUTTON_DPAD_UP);
	_InputPad.push_back(XINPUT_BUTTON_DPAD_DOWN);
	_InputPad.push_back(XINPUT_BUTTON_DPAD_RIGHT);
	_InputPad.push_back(XINPUT_BUTTON_DPAD_LEFT);
	_InputPad.push_back(XINPUT_BUTTON_RIGHT_SHOULDER);
	_InputPad.push_back(XINPUT_BUTTON_A);
	_InputPad.push_back(XINPUT_BUTTON_X);
	_InputPad.push_back(XINPUT_BUTTON_LEFT_SHOULDER);
	_InputPad.push_back(XINPUT_BUTTON_B);
}

//���͐���X�e�b�v
void CInputManager::Step() {
	CInput::Step();
}

//�������ꂽ
bool CInputManager::IsPush(eInputType input_code) {
	if (CInput::IsKeyPush(_InputKey[static_cast<int>(input_code)]) == true ||
		CInput::IsXPadPush(_InputPad[static_cast<int>(input_code)]) == true)
		return true;

	return false;
}

//�����������Ă��邩
bool CInputManager::IsKeep(eInputType input_code) {
	if (CInput::IsKeyKeep(_InputKey[static_cast<int>(input_code)]) == true ||
		CInput::IsXPadKeep(_InputPad[static_cast<int>(input_code)]) == true)
		return true;

	return false;
}

//�������������ꂽ��
bool CInputManager::IsRelease(eInputType input_code) {
	if (CInput::IsKeyRelease(_InputKey[static_cast<int>(input_code)]) == true ||
		CInput::IsXPadRelease(_InputPad[static_cast<int>(input_code)]) == true)
		return true;

	return false;
}

//�P���ɉ�����Ă��邩
bool CInputManager::IsDown(eInputType input_code) {
	if (CInput::IsKeyDown(_InputKey[static_cast<int>(input_code)]) == true ||
		CInput::IsXPadDown(_InputPad[static_cast<int>(input_code)]) == true)
		return true;

	return false;
}

//X�����͒l(�E�X�e�B�b�N�A�����L�[)
float CInputManager::GetRInputX() {
	if (CInput::IsKeyDown(KEY_INPUT_RIGHT) == true)
		return 1.f;
	else if (CInput::IsKeyDown(KEY_INPUT_LEFT) == true)
		return -1.f;
	else
		return CInput::GetRstickXInput();
}

//Y�����͒l(�E�X�e�B�b�N�A�����L�[)
float CInputManager::GetRInputY() {
	if (CInput::IsKeyDown(KEY_INPUT_UP) == true)
		return 1.f;
	else if (CInput::IsKeyDown(KEY_INPUT_DOWN) == true)
		return -1.f;
	else
		return CInput::GetRstickYInput();
}

//X�����͒l(���X�e�B�b�N�A�����{�^���AA.D�L�[)
float CInputManager::GetLInputX() {
	if (CInput::IsKeyDown(KEY_INPUT_D) == true || CInput::IsXPadDown(XINPUT_BUTTON_DPAD_RIGHT) == true)
		return 1.f;
	else if (CInput::IsKeyDown(KEY_INPUT_A) == true || CInput::IsXPadDown(XINPUT_BUTTON_DPAD_LEFT) == true)
		return -1.f;
	else
		return CInput::GetLstickXInput();
}

//Y�����͒l(���X�e�B�b�N�A�����{�^���AW.S�L�[)
float CInputManager::GetLInputY() {
	if (CInput::IsKeyDown(KEY_INPUT_W) == true || CInput::IsXPadDown(XINPUT_BUTTON_DPAD_UP) == true)
		return 1.f;
	else if (CInput::IsKeyDown(KEY_INPUT_S) == true || CInput::IsXPadDown(XINPUT_BUTTON_DPAD_DOWN) == true)
		return -1.f;
	else
		return CInput::GetLstickYInput();
}
