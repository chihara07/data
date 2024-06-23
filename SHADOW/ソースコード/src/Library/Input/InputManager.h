#pragma once
#include <vector>

using namespace std;

class  CInputManager{
private:
	static vector<int> _InputKey;		//キー入力用配列
	static vector<int> _InputPad;		//パッド入力用配列
public:
	//入力判別用列挙型
	enum class eInputType{
		MOVE_UP,		//上移動
		MOVE_DOWN,		//下移動
		MOVE_R,			//右移動
		MOVE_L,			//左移動
		SHADOW,			//影
		JUMP,			//ジャンプ
		FALL,			//下降
		TELEPORT,		//テレポート
		SELECT,			//選択

		NUM
	};

	//入力制御初期化
	static void Init();

	//入力制御ステップ
	static void Step();

	//今押された
	static bool IsPush(eInputType input_code);

	//押し続けられているか
	static bool IsKeep(eInputType input_code);

	//たった今離されたか
	static bool IsRelease(eInputType input_code);

	//単純に押されているか
	static bool IsDown(eInputType input_code);

	//X軸入力値(右スティック、←→キー)
	static float GetRInputX();

	//Y軸入力値(右スティック、↑↓キー)
	static float GetRInputY();

	//X軸入力値(左スティック、←→ボタン、A.Dキー)
	static float GetLInputX();

	//Y軸入力値(左スティック、↑↓ボタン、W.Sキー)
	static float GetLInputY();
};
