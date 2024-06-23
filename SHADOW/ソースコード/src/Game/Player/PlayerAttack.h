#pragma once
#include "DxLib.h"
#include "Player.h"
#include "../../Library/Vector/Vector3D.h"

constexpr int ATTACK_NUM = 2;						//�U���̐�
constexpr int AREA_NUM = 3;							//�e�G���A�̐�
constexpr float AREA_ENERGY_MAX = 600.f;			//�e�G���A�ő�G�l���M�[��

class CPlayerAttack {
private:
	static CPlayerAttack* _Instance;		//�C���X�^���X

	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayerAttack();
	~CPlayerAttack();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CPlayerAttack(const CPlayerAttack& other);
	CPlayerAttack operator= (const CPlayerAttack& other) {}
public:
	//�C���X�^���X�擾
	static CPlayerAttack* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();
private:
	Vector3D _Pos[ATTACK_NUM];		//���W
	Vector3D _AreaPos[AREA_NUM];	//�e�G���A���W
	Vector3D _Scale;				//�g�嗦
	Vector3D _AreaScale[AREA_NUM];	//�e�G���A�g�嗦
	float _Rad;						//���a
	float _AreaRad[AREA_NUM];		//�e�G���A���a
	int _Cnt;						//�J�E���g
	float _Energy;					//�G�l���M�[
	float _EnergyCnt;				//�G�l���M�[�J�E���g
	float _HoldCnt;					//����������
	int _Interval;					//�C���^�[�o��
	int _Hndl;						//�n���h��
	int _AreaHndl[AREA_NUM];		//�e�G���A�n���h��
	bool _IsActive;					//�����t���O
	bool _AreaIsActive[AREA_NUM];	//�e�G���A�����t���O
	bool _IsPlayerMove;				//�v���C���[�������Ă��邩
	bool _IsHold;					//����������Ă邩
	bool _IsCharge;					//�`���[�W����Ă邩
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
public:
	//������
	void Init();
	//���[�h
	void Load();
	//�Z�b�g
	void Set();
	//���C������
	void Step();
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�X�V����
	void Update();
	//���N�G�X�g
	void Request();
	//�e�G���A���N�G�X�g
	void AreaRequest(bool f);

	//���W�擾
	Vector3D GetPos(int id) { if (id >= ATTACK_NUM) id = ATTACK_NUM - 1; return _Pos[id]; }
	//�e�G���A���W�擾
	Vector3D GetAreaPos(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1; return _AreaPos[id]; }
	//�����t���O�擾
	const bool GetActive() { return _IsActive; }
	//�e�G���A�����t���O�擾
	const bool GetAreaActive(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1;  return _AreaIsActive[id]; }
	//�v���C���[�ړ��t���O�擾
	const bool GetPlayerMove() { return _IsPlayerMove; }
	//�v���C���[�ړ��t���O�Z�b�g
	void SetPlayerMove(bool f) { _IsPlayerMove = f; }
	//�������t���O�擾
	const bool GetHold() { return _IsHold; }
	//�������t���O�Z�b�g
	void SetHold(bool f) { _IsHold = f; }
	//�`���[�W�t���O�擾
	const bool GetCharge() { return _IsCharge; }
	//���a�擾
	const float GetRad() { return _Rad; }
	//���������Ԏ擾
	const float GetHoldCnt() { return _HoldCnt; }
	//�G�l���M�[�擾
	const float GetEnergy() { return _Energy; }
	//�G�l���M�[�J�E���g�擾
	const float GetEnergyCnt() { return _EnergyCnt; }
	//�G���A���a�擾
	float GetAreaRad(int id) { if (id >= AREA_NUM) id = AREA_NUM - 1; return _AreaRad[id]; }
	//�w�肵���e�G���A���Z�b�g
	void AreaReset(int id);
	//���Z�b�g
	void AllReset();
};
