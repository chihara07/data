#include "DxLib.h"
#include "Input.h"

//フラグ用
constexpr int FLAG_TRUE = 1;
constexpr int FLAG_FALSE = 0;

constexpr short INPUT_LOWEST = 2000;			//入力を受け付ける最低値
constexpr float INPUT_LOWEST_F = 0.0610372f;	//入力を受け付ける最低値(float)
constexpr float MAX_INPUT = 32767;				//入力の最大値

//変数の初期化
char CInput::_CurrentKeyBuf[KEY_BUF_LEN] = { 0 };	//現在フレームのキー情報
char CInput::_CurrentPadBuf = 0;					//現在フレームのパッド情報
char CInput::_PreKeyBuf[KEY_BUF_LEN] = { 0 };		//前フレームのキー情報
char CInput::_PrePadBuf = 0;						//前フレームのパッド情報
int CInput::_PadRstickX = 0;						//パッドの右スティックの横方向の入力情報
int CInput::_PadRstickY = 0;						//パッドの右スティックの縦方向の入力情報
XINPUT_STATE CInput::_CurrentXinput = { 0 };		//現在フレームのパッドのXInput情報
XINPUT_STATE CInput::_PreXinput = { 0 };			//前フレームのパッドのXInput情報

//入力制御初期化
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

//入力制御ステップ
//他のStepより早く呼ぶ
void CInput::Step()
{
	//前フレームのキー情報変換を記録しておく
	for (int index = 0; index < KEY_BUF_LEN; index++)
		_PreKeyBuf[index] = _CurrentKeyBuf[index];
	//前フレームのパッド情報変換を記録しておく
		_PrePadBuf = _CurrentPadBuf;
	//前フレームのパッドのXInput情報変換を記録しておく
		_PreXinput = _CurrentXinput;

	//現在のキー情報を取得
	GetHitKeyStateAll(_CurrentKeyBuf);
	//現在のパッド情報を取得
	_CurrentPadBuf = GetJoypadInputState(DX_INPUT_PAD1);
	//現在のパッド情報を取得
	GetJoypadAnalogInputRight(&_PadRstickX, &_PadRstickY, DX_INPUT_PAD1);
	// 現在フレームのパッドのXInput情報を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &_CurrentXinput);
}

//今押された
bool CInput::IsKeyPush(int key_code)
{
	//前フレで押されていない　かつ　現フレで押されている
	if (_PreKeyBuf[key_code] == FLAG_FALSE && _CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//押されていないので　false
	return false;
}

//今押された(パッド)
bool CInput::IsPadPush(int pad_code)
{
	//前フレで押されていない　かつ　現フレで押されている
	if ((_PrePadBuf & pad_code) == FLAG_FALSE && (_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//押されていないので　false
	return false;
}

//押し続けられているか
bool CInput::IsKeyKeep(int key_code)
{
	//前フレで押されている　かつ　現フレで押されている
	if (_PreKeyBuf[key_code] == FLAG_TRUE && _CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//押し続けられていないので　false
	return false;
}

//押し続けられているか(パッド)
bool CInput::IsPadKeep(int pad_code) {
	//前フレで押されている　かつ　現フレで押されている
	if ((_PrePadBuf & pad_code) != FLAG_FALSE && (_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//押し続けられていないので　false
	return false;
}

//たった今離されたか
bool CInput::IsKeyRelease(int key_code)
{
	//前フレで押されている　かつ　現フレで押されていない
	if (_PreKeyBuf[key_code] == FLAG_TRUE && _CurrentKeyBuf[key_code] == FLAG_FALSE)
		return true;

	//今離されていないので　false
	return false;
}

//たった今離されたか(パッド)
bool CInput::IsPadRelease(int pad_code) {
	//前フレで押されている　かつ　現フレで押されていない
	if ((_PrePadBuf & pad_code) != FLAG_FALSE && (_CurrentPadBuf & pad_code) == FLAG_FALSE)
		return true;

	//押し続けられていないので　false
	return false;
}

//単純に押されているか
bool CInput::IsKeyDown(int key_code)
{
	//現フレで押されている（前フレの状態は関係なし）
	if (_CurrentKeyBuf[key_code] == FLAG_TRUE)
		return true;

	//押されていないので　false
	return false;
}

//単純に押されているか(パッド)
bool CInput::IsPadDown(int pad_code) {
	//現フレで押されている（前フレの状態は関係なし）
	if ((_CurrentPadBuf & pad_code) != FLAG_FALSE)
		return true;

	//押し続けられていないので　false
	return false;
}

//今押された(XInput)
bool CInput::IsXPadPush(int pad_code) {
	//前フレで押されていない　かつ　現フレで押されている
	if (_PreXinput.Buttons[pad_code] == FLAG_FALSE && _CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//押されていないので　false
	return false;
}

//押し続けられているか(XInput)
bool CInput::IsXPadKeep(int pad_code) {
	//前フレで押されている　かつ　現フレで押されている
	if (_PreXinput.Buttons[pad_code] == FLAG_TRUE && _CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//押されていないので　false
	return false;
}

//たった今離されたか(XInput)
bool CInput::IsXPadRelease(int pad_code) {
	//前フレで押されている　かつ　現フレで押されていない
	if (_PreXinput.Buttons[pad_code] == FLAG_TRUE && _CurrentXinput.Buttons[pad_code] == FLAG_FALSE)
		return true;

	//押されていないので　false
	return false;
}

//単純に押されているか(XInput)
bool CInput::IsXPadDown(int pad_code) {
	//現フレで押されている（前フレの状態は関係なし）
	if (_CurrentXinput.Buttons[pad_code] == FLAG_TRUE)
		return true;

	//押されていないので　false
	return false;
}

//パッドの右スティックの上入力があるか
bool CInput::IsPadRstickUp() {
	if (_PreXinput.ThumbRY > INPUT_LOWEST)
		return true;

	return false;
}

//パッドの右スティックの下入力があるか
bool CInput::IsPadRstickDown() {
	if (_PreXinput.ThumbRY < -INPUT_LOWEST)
		return true;

	return false;
}

//パッドの右スティックの右入力があるか
bool CInput::IsPadRstickRight() {
	if (_PreXinput.ThumbRX > INPUT_LOWEST)
		return true;

	return false;
}

//パッドの右スティックの左入力があるか
bool CInput::IsPadRstickLeft() {
	if (_PreXinput.ThumbRX < -INPUT_LOWEST)
		return true;

	return false;
}

//パッドの左スティックのX軸入力取得
float CInput::GetLstickXInput() {
	float xInput = static_cast<float>(_PreXinput.ThumbLX) / MAX_INPUT;

	return (xInput < INPUT_LOWEST_F && xInput > -INPUT_LOWEST_F) ? 0.0f : xInput;
}

//パッドの左スティックのY軸入力取得
float CInput::GetLstickYInput() {
	float yInput = static_cast<float>(_PreXinput.ThumbLY) / MAX_INPUT;

	return (yInput < INPUT_LOWEST_F && yInput > -INPUT_LOWEST_F) ? 0.0f : yInput;
}

//パッドの右スティックのX軸入力取得
float CInput::GetRstickXInput() {
	float xInput = static_cast<float>(_PreXinput.ThumbRX) / MAX_INPUT;

	return (xInput < INPUT_LOWEST_F && xInput > -INPUT_LOWEST_F) ? 0.0f : xInput;
}

//パッドの右スティックのY軸入力取得
float CInput::GetRstickYInput() {
	float yInput = static_cast<float>(_PreXinput.ThumbRY) / MAX_INPUT;

	return (yInput < INPUT_LOWEST_F && yInput > -INPUT_LOWEST_F) ? 0.0f : yInput;
}

