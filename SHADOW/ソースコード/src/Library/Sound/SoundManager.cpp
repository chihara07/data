#include "SoundManager.h"

constexpr int ONE_SECOND_MILI_TIME = 1000;		//1�b(�~���b)
constexpr float MAX_VOLUME = 255.f;				//�ő�T�E���h

int CSoundManager::_Hndl[(int)eSoundID::NUM];

//�R���X�g���N�^
CSoundManager::CSoundManager()
{
	for (int sound_index = 0; sound_index < (int)eSoundID::NUM; sound_index++)
	{
		_Hndl[sound_index] = -1;
	}
}

//�f�X�g���N�^
CSoundManager::~CSoundManager()
{
	Fin();
}

//������
void CSoundManager::Init() {
	for (int sound_index = 0; sound_index < (int)eSoundID::NUM; sound_index++)
	{
		_Hndl[sound_index] = -1;
	}
}
//�I������
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

//�S�f�[�^�ǂݍ���
//return : true = �S���[�h���� false = 1�ȏ�ǂݍ��ݎ��s
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
		//��ł����[�h���s�ł���΃t���O���I�t��
		if (_Hndl[i] == -1) isRet = false;
	}

	return isRet;
}

//�Đ����Ԏ擾(�~���b)
int CSoundManager::GetSoundTime(eSoundID id) {
	return (int)GetSoundCurrentTime(_Hndl[(int)id]);
}

//�Đ������Ԏ擾(�~���b)
int CSoundManager::GetSoundAllTime(eSoundID id) {
	return (int)GetSoundTotalTime(_Hndl[(int)id]);
}

//���y�Đ�����
//return : true = �Đ��� false = ��~��
bool CSoundManager::IsPlay(eSoundID id) {
	return CheckSoundMem(_Hndl[(int)id]) == 1 ? true : false;
}

//�Đ��J�n���Ԑݒ�
void CSoundManager::SetStartFrame(eSoundID id, int ms) {
	//�w��ID�̎��g�����擾���Đݒ�
	int iFreq = GetFrequencySoundMem(_Hndl[(int)id]) * ms / ONE_SECOND_MILI_TIME;
	SetCurrentPositionSoundMem(iFreq, _Hndl[(int)id]);
}

//�{�����[���ݒ�
void CSoundManager::SetVolume(eSoundID id, float vol){
	if (vol < 0.f || vol > 1.f) return;
	ChangeVolumeSoundMem((int)(MAX_VOLUME * vol), _Hndl[(int)id]);
}

//���y�Đ�
//[iType]	:	�Đ��^�C�v
//				DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
//				DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
//				DX_PLAYTYPE_LOOP	:	���[�v�Đ�
//[isStart]	:	true = �ŏ�����Đ� false = �r������Đ�
//return	:	0 = �����A -1 = �G���[
int CSoundManager::Play(eSoundID id, int type, bool is_start) {
	return PlaySoundMem(_Hndl[(int)id], type, is_start);
}

//���y��~
//return	:	0 = �����A -1 = �G���[
int CSoundManager::Stop(eSoundID id) {
	return StopSoundMem(_Hndl[(int)id]);
}

//�S���y��~
void CSoundManager::StopAll(void) {
	for (int i = 0; i < (int)eSoundID::NUM; i++)
		StopSoundMem(_Hndl[i]);
}
