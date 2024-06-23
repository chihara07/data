#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Coin/CoinManager.h"
#include "../Player/PlayerAttack.h"

constexpr Vector3D ENEMY_SCALE(0.1f, 0.1f, 0.1f);	//�G�g�嗦
constexpr Vector2D DISCOVERY_GRAPH_POS(0.5f, 0.5f);	//�����}�[�N���W
constexpr int DISCOVERY_MAX_COUNT = 50;				//�ړ���
constexpr int ENEMY_LIFE = 2;						//�G�̃��C�t
constexpr float DISCOVERY_GRAPH_HEIGHT = 20.f;		//�����}�[�N�̍���
constexpr float DISCOVERY_GRAPH_SIZE = 15.f;		//�����}�[�N�̃T�C�Y
constexpr float SEARCH_RANGE = 150.0f;				//���G�͈�1
constexpr float SEARCH_RANGE2 = 200.0f;				//���G�͈�2
constexpr float ENEMY_SPD = 1.2f;					//�G�̈ړ����x
constexpr float KNOCKBACK_SPD = 5.f;				//�m�b�N�o�b�N���x
constexpr float ENEMY_CHASE_SPD = 2.0f;				//�G�̒ǐՈړ����x
constexpr float ENEMY_RAD = 10.0f;					//�G�̔��a
constexpr float KNOCKBACK_SPD_REDUCE = 0.9f;		//�m�b�N�o�b�N���x�����炷��
constexpr float KNOCKBACK_SPD_MIN = 0.1f;			//�m�b�N�o�b�N���x�Œ�l
constexpr float TURN_ROT = 6.f;						//�U�������]�p�x
constexpr float TURN_ROT_MAX = 180.f;				//�U�������]�p�x���
constexpr float RETURN_ERROR = 2.0f;				//�߂�Ƃ��̌덷

//�G�I�u�W�F�N�g�N���X
class CEnemyObj {
public:
	//�G�̏�ԗp�񋓌^
	enum class eEnemyState {
		NORMAL,		//�ʏ���
		CHASE,		//�v���C���[��ǂ������Ă�����
		CHASE_AREA,	//�e�G���A��ǂ������Ă�����
		FLASH,		//�t���b�V���U��
		KNOCKBACK,	//�m�b�N�o�b�N
		DISCOVERY,	//�v���C���[����
		TURN,		//�U�����

		NUM,
	};
	//�G�̎�ޗp�񋓌^
	enum class eCoin {
		NONE,		//�ʏ�
		HAVE,		//�R�C��

		NUM,
	};
	//�G�̈ړ���ԗp�񋓌^
	enum class eEnemyMoveState {
		MOVE_STATE_1 = 1,	//���1
		MOVE_STATE_2,		//���2

		NON,
	};
	//�G�̎��
	enum class eEnemyType {
		NORMAL,
		SHOT,
		FLASH,
		WALL,

		NUM
	};
protected:
	Vector3D _Pos;				//���W
	Vector3D _MovePos1;			//���W1
	Vector3D _MovePos2;			//���W2
	Vector3D _SavePos;			//���W�ۑ�
	Vector3D _BulletPos;		//�e���W
	Vector3D _Move;				//�ړ���
	Vector3D _MoveVec;			//�G�̈ړ��x�N�g���p
	Vector3D _SaveVec;			//�x�N�g���ۑ�
	Vector3D _CheckRot;			//��]�p�x�m�F
	Vector3D _LimitCenterPos;	//�ړ������̒��S
	Vector2D _LimitDistance;	//�ړ���������
	Vector3D _Scale;			//�g�嗦
	Vector3D _Rot;				//��]�p�x
	Vector3D _ResetRot;			//���Z�b�g�p��]�p�x
	int _Hndl;					//���f���n���h��
	int _Size;					//�T�C�Y
	int _Life;					//���C�t
	float _Rad;					//���a
	float _BulletRad;			//�e���a
	float _FlashRad;			//�t���b�V���U�����a
	float _Spd;					//�ړ����x
	bool _IsActive;				//�����t���O
	bool _IsBulletActive;		//�e�����t���O
	bool _IsFlashActive;		//�t���b�V���U�������t���O
	float _KnockBackSpd;		//�m�b�N�o�b�N�X�s�[�h
	float _SearchRange;			//���G�͈�
	float _SaveRotY;			//Y���p�x�ۑ�
	int _DiscoveryCount;		//�����J�E���g
	bool _IsForward;			//�O���t���O
	bool _HitArea[AREA_NUM];	//�e�G���A�ɐG��Ă邩
	eEnemyState _State;		//�G�̏��
	eEnemyState _OldState;	//�Â����
	eCoin _CoinType;			//�R�C���т̗L��
	eEnemyType _Type;			//�G�̎��
	eEnemyMoveState _MoveID;	//����ID
	eEnemyMoveState _OldID;	//�Â�ID

	CCoin* cCoin;				//�R�C���|�C���^
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyObj():_Hndl(-1), _IsActive(), _Size(), _Rad(), _Spd(), _Life(), _KnockBackSpd(),
		_SearchRange(), _SaveRotY(), _DiscoveryCount(), _IsForward(), _State(), _OldState(),
		_CoinType(), _MoveID(), _OldID(), cCoin() {};
	~CEnemyObj() {};

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
	virtual void HitCalc() = 0;
	//���S�֐�
	virtual void DeathCalc();
	//�ړ��֐�
	virtual void Move() {};
	//��ԕω��֐�
	virtual void ChangeState() {};
	//�ʏ��ԃA�N�V�����֐�
	virtual void NormalAct();
	//�v���C���[��ǂ������Ă����Ԋ֐�
	virtual void ChaseAct();
	//�e�G���A��ǂ������Ă����Ԋ֐�
	virtual void ChaseAreaAct() {};
	//�U����Ԋ֐�
	virtual void AttackAct() {};
	//�m�b�N�o�b�N��Ԋ֐�
	virtual void KnockBackAct();
	//�v���C���[������Ԋ֐�
	virtual void DiscoveryAct();
	//�U�������Ԋ֐�
	virtual void TurnAct();
	/// <summary>
	/// �ړI�n�Ɍ������֐�
	/// </summary>
	/// <param name="destination">�ړI�n���W</param>
	/// <param name="spd">�ړ����x</param>
	void HeadToDestination(Vector3D destination, Vector3D spd);

	//���W�擾
	Vector3D GetPos() { return _Pos; }
	//���W�Z�b�g
	void SetPos(Vector3D v) { _Pos = v; }
	//�e���W�擾
	Vector3D GetBulletPos() { return _BulletPos; }
	//�e���W�Z�b�g
	void SetBulletPos(Vector3D v) { _BulletPos = v; }
	//��]�p�x�Z�b�g
	void SetRot(Vector3D r) { _Rot = r; }
	//���Z�b�g��]�p�x�Z�b�g
	void SetResetRot(Vector3D r) { _ResetRot = r; }
	//�ړ��x�N�g���Z�b�g
	void SetMoveVec(Vector3D v) { _MoveVec = v; }
	//���W�Z�b�g
	void SetLimitCenterPos(Vector3D v) { _LimitCenterPos = v; }
	//���W�Z�b�g
	void SetLimitDistance(Vector2D v) { _LimitDistance = v; }
	//���W�Z�b�g
	void SetMovePos1(Vector3D v) { _MovePos1 = v; }
	//���W�Z�b�g
	void SetMovePos2(Vector3D v) { _MovePos2 = v; }
	//�����t���O�擾
	const bool GetActive() { return _IsActive; }
	//�O���t���O�擾
	const bool GetForward() { return _IsForward; }
	//���a�擾
	const float GetRad() { return _Rad; }
	//��Ԏ擾
	const eEnemyState GetState() { return _State; }
	//��ԃZ�b�g
	void SetState(eEnemyState s) { _State = s; }
	//�R�C����ގ擾
	const eCoin GetCoinType() { return _CoinType; }
	//��ގ擾
	const eEnemyType GetType() { return _Type; }
	//�R�C����ރZ�b�g
	void SetCoinType(eCoin t) { _CoinType = t; }
	//��ރZ�b�g
	void SetType(eEnemyType t) { _Type = t; }
	//���C�t����
	void SubLife() { _Life--; }
	//�R�C���Z�b�g
	void SetCoin(CCoin* c) { cCoin = c; }
	//�����t���O�擾
	const bool GetBulletActive() { return _IsBulletActive; }
	//���a�擾
	const float GetBulletRad() { return _BulletRad; }
	//�t���b�V���U�������t���O�擾
	const bool GetFlashActive() { return _IsFlashActive; }
	//�t���b�V���U�����a�擾
	const float GetFlashRad() { return _FlashRad; }
	//�e�G���A�G��Ă��邩�Z�b�g
	void SetHitArea(int id, bool f) { _HitArea[id] = f; }

	//�A�N�V�����؂�ւ��֐��|�C���^
	void (CEnemyObj::* ActFunc[static_cast<int>(eEnemyState::NUM)])() = {
		&CEnemyObj::NormalAct,
		&CEnemyObj::ChaseAct,
		&CEnemyObj::ChaseAreaAct,
		&CEnemyObj::AttackAct,
		&CEnemyObj::KnockBackAct,
		&CEnemyObj::DiscoveryAct,
		&CEnemyObj::TurnAct };
};