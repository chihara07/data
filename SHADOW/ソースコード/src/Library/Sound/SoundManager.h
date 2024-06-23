#pragma once
#include "DxLib.h"

//サウンド操作クラス
class CSoundManager {
public:
	//サウンドID
	enum class eSoundID {
		BGM,			//BGM
		CLEAR_BGN,		//クリアBGM
		GAMEOVER_BGM,	//ゲームオーバーBGM
		SE_PLJUMP,		//SE プレイヤージャンプ音
		SE_PLSHADOW,	//SE 影になる音
		SE_SWITCH,		//SE スイッチ音
		SE_PLCHANGE,	//SE プレイヤー変化音
		SE_PLTELEPORT,	//SE プレイヤーテレポート音
		SE_PLATTACK,	//SE プレイヤー攻撃音
		SE_PLRETURN,	//SE プレイヤー帰還音
		SE_ENCHARGE,	//SE 敵チャージ音
		SE_ENCOIN,		//SE コイン音
		SE_ENDEATH,		//SE 敵死亡音
		SE_ENFLASH,		//SE 敵フラッシュ攻撃攻撃音
		SE_ENSHOT,		//SE 敵攻撃音

		NUM,
	};
private:
	static int _Hndl[(int)eSoundID::NUM];		//サウンドハンドル

public:
	//コンストラクタ、デストラクタ
	CSoundManager();
	~CSoundManager();

	//初期化
	static void Init();
	//終了処理
	static void Fin();

	//全データ読み込み
	//return : true = 全ロード成功 false = 1つ以上読み込み失敗
	static bool LoadAllData();

	//再生時間取得(ミリ秒)
	static int GetSoundTime(eSoundID id);

	//再生総時間取得(ミリ秒)
	static int GetSoundAllTime(eSoundID id);

	//音楽再生判定
	//return : true = 再生中 false = 停止中
	static bool IsPlay(eSoundID id);

	//再生開始時間設定
	static void SetStartFrame(eSoundID id, int ms);

	//ボリューム設定
	static void SetVolume(eSoundID id, float vol);
	
	//音楽再生
	//[iType]	:	再生タイプ
	//				DX_PLAYTYPE_NORMAL	:	ノーマル再生
	//				DX_PLAYTYPE_BACK	:	バックグラウンド再生
	//				DX_PLAYTYPE_LOOP	:	ループ再生
	//[isStart]	:	true = 最初から再生 false = 途中から再生
	//return	:	0 = 成功、 -1 = エラー
	static int Play(eSoundID id, int type = DX_PLAYTYPE_BACK, bool is_start = true);

	//音楽停止
	//return	:	0 = 成功、 -1 = エラー
	static int Stop(eSoundID id);

	//全音楽停止
	static void StopAll(void);
};
