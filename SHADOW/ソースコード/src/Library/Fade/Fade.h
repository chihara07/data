#pragma once

//フェードイン・フェードアウトクラス
class CFade {
public:
	//フェードの状態用列挙
	enum class eFadeState{
		NON,
		FADE_IN,
		FADE_OUT,
	};
private:
	static CFade* _Instance;		//インスタンス

	float _AlphaValue;				//フェードのアルファ値
	float _Spd;						//フェード速度
	eFadeState _State;			//フェードの状態
	int _WindowX;					//ウィンドウサイズ横
	int _WindowY;					//ウィンドウサイズ縦

public:
	//インスタンス取得
	static CFade* GetInstance();
	//インスタンス破棄
	static void DeleteInstance();

	/// <summary>
	/// フェードリクエスト
	/// </summary>
	/// <param name="spd">フェード速度0～255</param>
	/// <param name="is_in">true = フェードイン false = フェードアウト</param>
	void RequestFade(float spd, bool is_in = true);
	//更新
	void Update();
	//描画
	void Draw();
	//終了判定
	bool IsEnd();
	//フェードの状態取得
	const eFadeState GetState() { return _State; }
	//ウィンドウサイズ設定
	void SetWindowSize(int x, int y) { _WindowX = x; _WindowY = y; }
	//リセット
	void Reset() { _State = eFadeState::NON; }
private:

	//コンストラクタ・デストラクタ
	CFade();
	~CFade();

	//シングルトンなので他での生成を禁止
	CFade(const CFade& other);
	CFade operator= (const CFade& other) {}
};