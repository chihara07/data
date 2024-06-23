#include "DxLib.h"
#include "Input.h"

//�t���O�p
constexpr int FLAG_TRUE = 1;
constexpr int FLAG_FALSE = 0;

constexpr short INPUT_LOWEST = 2000;			//���͂��󂯕t����Œ�l
constexpr float INPUT_LOWEST_F = 0.0610372f;	//���͂��󂯕t����Œ�l(float)
constexpr float MAX_INPUT = 32767;				//���͂̍ő�l

//�ϐ��̏�����
char CInput::_CurrentKeyBuf[KEY_BUF_LEN] = { 0 };	//���݃t���[���̃L�[���
char CInput::_CurrentPadBuf = 0;					//���݃t���[���̃p�b�h���
char CInput::_PreKeyBuf[KEY_BUF_LEN] = { 0 };		//�O�t���[���̃L�[���
char CInput::_PrePadBuf = 0;						//�O�t���[���̃p�b�h���
int CInput::_PadRstickX = 0;						//�p�b�h�̉E�X�e�B�b�N�̉������̓��͏��
int CInput::_PadRstickY = 0;						//�p�b�h�̉E�X�e�B�b�N�̏c�����̓��͏��
XINPUT_STATE CInput::_CurrentXinput = { 0 };		//���݃t���[���̃p�b�h��XInput���
XINPUT_STATE CInput::_PreXinput = { 0 };			//�O�t���[���̃p�b�h��XInput���

//���͐��䏉����
void CInput::Init()
{
	for (int index = 0; index < KEY_BUF_LEN; index++)
	{
		_CurrentKeyBuf[index] = '\0';
		_PreKeyBuf[index] = '\0';
	}

		_CurrentPadBuf = '\0';
		_PrePadBuf = '\0';

		_CurrentXinput = { 0 };
		_PreXinput = { 0 };
}

//���͐���X�e�b�v
//����Step��葁���Ă�
void CInput::Step()
{
	//�O�t���[���̃L�[���ϊ����L�^���Ă���
	for (int index = 0; index < KEY_BUF_LEN; index++)
		_PreKeyBuf[index] = _CurrentKeyBuf[index];
	//�O�t���[���̃p�b�h���ϊ����L�^���Ă���
		_PrePadBuf = _CurrentPadBuf;
	//�O�t���[���̃p�b�h��XInput���ϊ����L�^���Ă���
		_PreXinput = _CurrentXinput;

	//���݂̃L�[�����擾
	GetHitKeyStateAll(_CurrentKeyBuf);
	//���݂̃p�b�h�����擾
	_CurrentPadBuf = GetJoypadInputState(DX_INPUT_PAD1);
	//���݂̃p�b�h�����擾
	GetJoypadAnalogInputRight(&_PadRstickX, &_PadRstickY, DX_INPUT_PAD1);
	// ���݃t���[���̃p�b�h��XInput�����擾
	GetJoypadXInputState(DX_INPUT_PAD1, &_CurrentXinput);
}

//�������ꂽ
bool CInput::IsKeyPush(int key_code)
{
	//�O�t���ŉ�����Ă��Ȃ��@���@���t���ŉ�����Ă���
	if (_PreKeyBuf[key_code] == FLAG_FALSE && _CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�������ꂽ(�p�b�h)
bool CInput::IsPadPush(int pad_code)
{
	//�O�t���ŉ�����Ă��Ȃ��@���@���t���ŉ�����Ă���
	if ((_PrePadBuf & pad_code) == FLAG_FALSE && (_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�����������Ă��邩
bool CInput::IsKeyKeep(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (_PreKeyBuf[key_code] == FLAG_TRUE && _CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//�����������Ă��Ȃ��̂Ł@false
	return false;
}

//�����������Ă��邩(�p�b�h)
bool CInput::IsPadKeep(int pad_code) {
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if ((_PrePadBuf & pad_code) != FLAG_FALSE && (_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//�����������Ă��Ȃ��̂Ł@false
	return false;
}

//�������������ꂽ��
bool CInput::IsKeyRelease(int key_code)
{
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (_PreKeyBuf[key_code] == FLAG_TRUE && _CurrentKeyBuf[key_code] == FLAG_FALSE)
		return true;

	//��������Ă��Ȃ��̂Ł@false
	return false;
}

//�������������ꂽ��(�p�b�h)
bool CInput::IsPadRelease(int pad_code) {
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if ((_PrePadBuf & pad_code) != FLAG_FALSE && (_CurrentPadBuf & pad_code) == FLAG_FALSE)
		return true;

	//�����������Ă��Ȃ��̂Ł@false
	return false;
}

//�P���ɉ�����Ă��邩
bool CInput::IsKeyDown(int key_code)
{
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (_CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�P���ɉ�����Ă��邩(�p�b�h)
bool CInput::IsPadDown(int pad_code) {
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if ((_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//�����������Ă��Ȃ��̂Ł@false
	return false;
}

//�������ꂽ(XInput)
bool CInput::IsXPadPush(int pad_code) {
	//�O�t���ŉ�����Ă��Ȃ��@���@���t���ŉ�����Ă���
	if (_PreXinput.Buttons[pad_code] == FLAG_FALSE && _CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�����������Ă��邩(XInput)
bool CInput::IsXPadKeep(int pad_code) {
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă���
	if (_PreXinput.Buttons[pad_code] == FLAG_TRUE && _CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�������������ꂽ��(XInput)
bool CInput::IsXPadRelease(int pad_code) {
	//�O�t���ŉ�����Ă���@���@���t���ŉ�����Ă��Ȃ�
	if (_PreXinput.Buttons[pad_code] == FLAG_TRUE && _CurrentXinput.Buttons[pad_code] == FLAG_FALSE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�P���ɉ�����Ă��邩(XInput)
bool CInput::IsXPadDown(int pad_code) {
	//���t���ŉ�����Ă���i�O�t���̏�Ԃ͊֌W�Ȃ��j
	if (_CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//������Ă��Ȃ��̂Ł@false
	return false;
}

//�p�b�h�̉E�X�e�B�b�N�̏���͂����邩
bool CInput::IsPadRstickUp() {
	if (_PreXinput.ThumbRY > INPUT_LOWEST)
		return true;

	return false;
}

//�p�b�h�̉E�X�e�B�b�N�̉����͂����邩
bool CInput::IsPadRstickDown() {
	if (_PreXinput.ThumbRY < -INPUT_LOWEST)
		return true;

	return false;
}

//�p�b�h�̉E�X�e�B�b�N�̉E���͂����邩
bool CInput::IsPadRstickRight() {
	if (_PreXinput.ThumbRX > INPUT_LOWEST)
		return true;

	return false;
}

//�p�b�h�̉E�X�e�B�b�N�̍����͂����邩
bool CInput::IsPadRstickLeft() {
	if (_PreXinput.ThumbRX < -INPUT_LOWEST)
		return true;

	return false;
}

//�p�b�h�̍��X�e�B�b�N��X�����͎擾
float CInput::GetLstickXInput() {
	float xInput = static_cast<float>(_PreXinput.ThumbLX) / MAX_INPUT;

	return (xInput < INPUT_LOWEST_F && xInput > -INPUT_LOWEST_F) ? 0.0f : xInput;
}

//�p�b�h�̍��X�e�B�b�N��Y�����͎擾
float CInput::GetLstickYInput() {
	float yInput = static_cast<float>(_PreXinput.ThumbLY) / MAX_INPUT;

	return (yInput < INPUT_LOWEST_F && yInput > -INPUT_LOWEST_F) ? 0.0f : yInput;
}

//�p�b�h�̉E�X�e�B�b�N��X�����͎擾
float CInput::GetRstickXInput() {
	float xInput = static_cast<float>(_PreXinput.ThumbRX) / MAX_INPUT;

	return (xInput < INPUT_LOWEST_F && xInput > -INPUT_LOWEST_F) ? 0.0f : xInput;
}

//�p�b�h�̉E�X�e�B�b�N��Y�����͎擾
float CInput::GetRstickYInput() {
	float yInput = static_cast<float>(_PreXinput.ThumbRY) / MAX_INPUT;

	return (yInput < INPUT_LOWEST_F && yInput > -INPUT_LOWEST_F) ? 0.0f : yInput;
}

