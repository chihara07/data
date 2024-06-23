#include "SoundManager.h"

constexpr int ONE_SECOND_MILI_TIME = 1000;		//1秒(ミリ秒)
constexpr float MAX_VOLUME = 255.f;				//最大サウンド

int CSoundManager::_Hndl[(int)eSoundID::NUM];

//コンストラクタ
CSoundManager::CSoundManager()
{
	for (int sound_index = 0; sound_index < (int)eSoundID::NUM; sound_index++)
	{
		_Hndl[sound_index] = -1;
	}
}

//デストラクタ
CSoundManager::~CSoundManager()
{
	Fin();
}

//初期化
void CSoundManager::Init() {
	for (int sound_index = 0; sound_index < (int)eSoundID::NUM; sound_index++)
	{
		_Hndl[sound_index] = -1;
	}
}
//終了処理
void CSoundManager::Fin() {
	for (int sound_index = 0; sound_index < (int)eSoundID::NUM; sound_index++)
	{
		if (_Hndl[sound_index] != -1)
		{
			DeleteSoundMem(_Hndl[sound_index]);
			_Hndl[sound_index] = -1;
		}
	}
}

//全データ読み込み
//return : true = 全ロード成功 false = 1つ以上読み込み失敗
bool CSoundManager::LoadAllData() {
	bool isRet = true;
	const char pFileName[(int)eSoundID::NUM][128] =
	{
		"data/Sound/bgm.mp3",
		"data/Sound/clear.mp3",
		"data/Sound/gameover.mp3",
		"data/Sound/jump.wav",
		"data/Sound/shadow.wav",
		"data/Sound/switch.wav",
		"data/Sound/change.wav",
		"data/Sound/teleport.wav",
		"data/Sound/attack.wav",
		"data/Sound/back.wav",
		"data/Sound/charge.mp3",
		"data/Sound/coin.mp3",
		"data/Sound/enemydeath.wav",
		"data/Sound/flash.mp3",
		"data/Sound/shot.mp3",
	};

	for (int i = 0; i < (int)eSoundID::NUM; i++)
	{
		_Hndl[i] = LoadSoundMem(pFileName[i]);
		//一つでもロード失敗であればフラグをオフに
		if (_Hndl[i] == -1) isRet = false;
	}

	return isRet;
}

//再生時間取得(ミリ秒)
int CSoundManager::GetSoundTime(eSoundID id) {
	return (int)GetSoundCurrentTime(_Hndl[(int)id]);
}

//再生総時間取得(ミリ秒)
int CSoundManager::GetSoundAllTime(eSoundID id) {
	return (int)GetSoundTotalTime(_Hndl[(int)id]);
}

//音楽再生判定
//return : true = 再生中 false = 停止中
bool CSoundManager::IsPlay(eSoundID id) {
	return CheckSoundMem(_Hndl[(int)id]) == 1 ? true : false;
}

//再生開始時間設定
void CSoundManager::SetStartFrame(eSoundID id, int ms) {
	//指定IDの周波数を取得して設定
	int iFreq = GetFrequencySoundMem(_Hndl[(int)id]) * ms / ONE_SECOND_MILI_TIME;
	SetCurrentPositionSoundMem(iFreq, _Hndl[(int)id]);
}

//ボリューム設定
void CSoundManager::SetVolume(eSoundID id, float vol){
	if (vol < 0.f || vol > 1.f) return;
	ChangeVolumeSoundMem((int)(MAX_VOLUME * vol), _Hndl[(int)id]);
}

//音楽再生
//[iType]	:	再生タイプ
//				DX_PLAYTYPE_NORMAL	:	ノーマル再生
//				DX_PLAYTYPE_BACK	:	バックグラウンド再生
//				DX_PLAYTYPE_LOOP	:	ループ再生
//[isStart]	:	true = 最初から再生 false = 途中から再生
//return	:	0 = 成功、 -1 = エラー
int CSoundManager::Play(eSoundID id, int type, bool is_start) {
	return PlaySoundMem(_Hndl[(int)id], type, is_start);
}

//音楽停止
//return	:	0 = 成功、 -1 = エラー
int CSoundManager::Stop(eSoundID id) {
	return StopSoundMem(_Hndl[(int)id]);
}

//全音楽停止
void CSoundManager::StopAll(void) {
	for (int i = 0; i < (int)eSoundID::NUM; i++)
		StopSoundMem(_Hndl[i]);
}
