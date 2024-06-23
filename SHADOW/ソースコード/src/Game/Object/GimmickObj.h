#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Gimmick/Switch/Switch.h"
#include "../Gimmick/Switch/SwitchManager.h"
#include "../Camera/Camera.h"

//�I�u�W�F�N�g�N���X
class CGimmickObj {
public:
	//�M�~�b�N�̏��
	enum class eState {
		NORMAL,		//�ʏ���
		MOVE,		//�������
		SPECIAL,	//������

		NUM,
	};
	//�����̏��
	enum class eMoveState {
		MOVE1,		//����1
		MOVE2,		//����2

		NUM,
	};
	//�M�~�b�N�̎��
	enum class eGimmickType {
		BLOCK,		//�u���b�N
		FENCE,		//�t�F���X
		GOAL,		//�S�[��
		NOSHADOW,	//�e�֎~
		TELEPORT,	//�e���|�[�g
		TRAP,		//�g���b�v
		WALL,		//��
		CROSS,		//�\��

		NUM,
	};
protected:
	Vector3D _Pos;				//���W
	Vector3D _MovePos1;			//�������W1
	Vector3D _MovePos2;			//�������W2
	Vector3D _SavePos;			//�ꎞ�ۑ����W
	Vector3D _MoveVec;			//�ړ��x�N�g��
	Vector3D _Scale;			//�䗦
	Vector3D _CollisionScale;	//�䗦
	Vector3D _Rot;				//��]�p�x
	int _Hndl;					//���f���n���h��
	int _CollisionHndl;			//�����蔻�胂�f���n���h��
	bool _IsActive;				//�����t���O
	float _Spd;					//�ړ����x
	float _Rad;					//���a
	eState _State;			//�M�~�b�N�̏��
	eMoveState _MoveID;		//����ID
	eGimmickType _Type;			//�M�~�b�N�̎��

	CSwitch* _cSwitch;			//�X�C�b�`�|�C���^
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CGimmickObj() :_Hndl(-1), _Pos(), _Scale(), _Rot(), _IsActive(), _CollisionHndl(), _MoveID(),
					_Rad(), _Spd(), _State(), _Type(), _cSwitch() {};
	~CGimmickObj() {};

	//������
	virtual void Init() = 0;
	//���[�h
	virtual void Load() = 0;
	//�Z�b�g
	virtual void Set() = 0;
	//���C������
	virtual void Step() = 0;
	//�`��
	virtual void Draw() = 0;
	//�I��
	virtual void Fin() = 0;
	//�X�V����
	virtual void Update() = 0;
	//�q�b�g�֐�
	virtual void HitCalc() {};

	//���W�擾
	Vector3D GetPos() { return _Pos; }
	//���W�Z�b�g
	void SetPos(Vector3D v) { _Pos = v; }
	//�������W1�Z�b�g
	void SetMovePos1(Vector3D v) { _MovePos1 = v; }
	//�������W2�Z�b�g
	void SetMovePos2(Vector3D v) { _MovePos2 = v; }
	//��]�p�x�Z�b�g
	void SetRot(Vector3D r) { _Rot = r; }
	//�䗦�Z�b�g
	void SetScale(Vector3D s) { _Scale = s; }
	//��ԃZ�b�g
	void SetState(eState s) { _State = s; }
	//����ID�Z�b�g
	void SetMoveID(eMoveState id) { _MoveID = id; }
	//�����t���O�擾
	const bool GetActive() { return _IsActive; }
	//�����t���O�Z�b�g
	void SetActive(bool f) { _IsActive = f; }
	//��ރZ�b�g
	void SetType(eGimmickType t) { _Type = t; }
	//��ގ擾
	const eGimmickType GetType() { return _Type; }
	//�n���h���擾
	const int GetHndl() { return _Hndl; }
	//�����蔻��n���h���擾
	const int GetCollisionHndl() { return _CollisionHndl; }
	//���a�擾
	const float GetRad() { return _Rad; }
	//���x�Z�b�g
	void SetSpd(float s) { _Spd = s; }
	//�X�C�b�`�Z�b�g
	void SetSwitch(CSwitch* s) { _cSwitch = s; }
};