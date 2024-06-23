#pragma once
#include "DxLib.h"

//�T�E���h����N���X
class CSoundManager {
public:
	//�T�E���hID
	enum class eSoundID {
		BGM,			//BGM
		CLEAR_BGN,		//�N���ABGM
		GAMEOVER_BGM,	//�Q�[���I�[�o�[BGM
		SE_PLJUMP,		//SE �v���C���[�W�����v��
		SE_PLSHADOW,	//SE �e�ɂȂ鉹
		SE_SWITCH,		//SE �X�C�b�`��
		SE_PLCHANGE,	//SE �v���C���[�ω���
		SE_PLTELEPORT,	//SE �v���C���[�e���|�[�g��
		SE_PLATTACK,	//SE �v���C���[�U����
		SE_PLRETURN,	//SE �v���C���[�A�҉�
		SE_ENCHARGE,	//SE �G�`���[�W��
		SE_ENCOIN,		//SE �R�C����
		SE_ENDEATH,		//SE �G���S��
		SE_ENFLASH,		//SE �G�t���b�V���U���U����
		SE_ENSHOT,		//SE �G�U����

		NUM,
	};
private:
	static int _Hndl[(int)eSoundID::NUM];		//�T�E���h�n���h��

public:
	//�R���X�g���N�^�A�f�X�g���N�^
	CSoundManager();
	~CSoundManager();

	//������
	static void Init();
	//�I������
	static void Fin();

	//�S�f�[�^�ǂݍ���
	//return : true = �S���[�h���� false = 1�ȏ�ǂݍ��ݎ��s
	static bool LoadAllData();

	//�Đ����Ԏ擾(�~���b)
	static int GetSoundTime(eSoundID id);

	//�Đ������Ԏ擾(�~���b)
	static int GetSoundAllTime(eSoundID id);

	//���y�Đ�����
	//return : true = �Đ��� false = ��~��
	static bool IsPlay(eSoundID id);

	//�Đ��J�n���Ԑݒ�
	static void SetStartFrame(eSoundID id, int ms);

	//�{�����[���ݒ�
	static void SetVolume(eSoundID id, float vol);
	
	//���y�Đ�
	//[iType]	:	�Đ��^�C�v
	//				DX_PLAYTYPE_NORMAL	:	�m�[�}���Đ�
	//				DX_PLAYTYPE_BACK	:	�o�b�N�O���E���h�Đ�
	//				DX_PLAYTYPE_LOOP	:	���[�v�Đ�
	//[isStart]	:	true = �ŏ�����Đ� false = �r������Đ�
	//return	:	0 = �����A -1 = �G���[
	static int Play(eSoundID id, int type = DX_PLAYTYPE_BACK, bool is_start = true);

	//���y��~
	//return	:	0 = �����A -1 = �G���[
	static int Stop(eSoundID id);

	//�S���y��~
	static void StopAll(void);
};
