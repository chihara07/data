#pragma once

//キー情報の個数
constexpr int  KEY_BUF_LEN = 256;

class CInput {
private:
	//現在フレームのキー情報
	static char _CurrentKeyBuf[KEY_BUF_LEN];
	//現在フレームのパッド情報
	static char _CurrentPadBuf;
	//前フレームのキー情報
	static char _PreKeyBuf[KEY_BUF_LEN];
	//前フレームのパッド情報
	static char _PrePadBuf;
	//パッドの右スティックの横方向の入力情報
	static int _PadRstickX;
	//パッドの右スティックの縦方向の入力情報
	static int _PadRstickY;
	//現在フレームのパッドのXInput情報
	static XINPUT_STATE _CurrentXinput;
	//前フレームのパッドのXInput情報
	static XINPUT_STATE _PreXinput;
public:
	//入力制御初期化
	static void Init();

	//入力制御ステップ
	static void Step();

	//今押された
	static bool IsKeyPush(int key_code);

	//今押された(パッド)
	static bool IsPadPush(int pad_code);

	//押し続けられているか
	static bool IsKeyKeep(int key_code);

	//押し続けられているか(パッド)
	static bool IsPadKeep(int pad_code);

	//たった今離されたか
	static bool IsKeyRelease(int key_code);

	//たった今離されたか(パッド)
	static bool IsPadRelease(int pad_code);

	//単純に押されているか
	static bool IsKeyDown(int key_code);

	//単純に押されているか(パッド)
	static bool IsPadDown(int pad_code);

	//今押された(XInput)
	static bool IsXPadPush(int pad_code);

	//押し続けられているか(XInput)
	static bool IsXPadKeep(int pad_code);

	//たった今離されたか(XInput)
	static bool IsXPadRelease(int pad_code);

	//単純に押されているか(XInput)
	static bool IsXPadDown(int pad_code);

	//パッドの右スティックの上入力があるか
	static bool IsPadRstickUp();

	//パッドの右スティックの下入力があるか
	static bool IsPadRstickDown();

	//パッドの右スティックの右入力があるか
	static bool IsPadRstickRight();

	//パッドの右スティックの左入力があるか
	static bool IsPadRstickLeft();

	//パッドの左スティックのX軸入力取得
	static float GetLstickXInput();

	//パッドの左スティックのY軸入力取得
	static float GetLstickYInput();

	//パッドの右スティックのX軸入力取得
	static float GetRstickXInput();

	//パッドの右スティックのY軸入力取得
	static float GetRstickYInput();
};
