#pragma once
#include "DxLib.h"
#include "../../Game/Camera/Camera.h"
#include "../Object/Object.h"

//�v���C���[�N���X
class CPlayer : public CObj {
private:
	static CPlayer* _Instance;

	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayer();
	~CPlayer();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CPlayer(const CPlayer& other);
	CPlayer operator= (const CPlayer& other) {}
public:
	//�v���C���[�̏�ԗp�񋓌^
	enum class ePlayerState {
		NORMAL,
		SHADOW,
		JUMP,
		TELEPORT,
		CLIMB,

		NUM,
	};

	//�C���X�^���X�擾
	static CPlayer* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();
private:
	Vector3D _SavePos;				//�v���C���[���W�ۑ�
	Vector3D _TeleportPos;			//�e���|�[�g�p���W
	Vector3D _TeleportMove;			//�e���|�[�g�ړ���
	Vector3D _TeleportTargetPos;	//�e���|�[�g��̍��W
	Vector3D _Forward;				//�O�����x�N�g��
	float _ShadowSpd;				//�e�ړ����x
	float _TeleportSpd;				//�e���|�[�g�ړ����x
	float _Gravity;					//�d��
	int _ShadowHndl;				//�e��Ԃ̃n���h��
	int _TeleportHndl;				//�e���|�[�g�̃n���h��
	int _DeathEffectHndl;			//���S���G�t�F�N�g�n���h��
	int _ChangeEffectHndl;			//�ϐg���G�t�F�N�g�n���h��
	int _HaveCoin;					//�R�C��������
	bool _Teleport;					//�e���|�[�g�o���邩
	bool _IsClimb;					//�o��邩
	bool _IsGround;					//�n�ʂɂ��邩
	bool _HitArea;					//�G���A�ɐG��Ă��邩
	bool _IsClear = false;			//�N���A������
	bool _IsDeath = false;			//���񂾂�
	ePlayerState _State;			//�v���C���[�̏��
	ePlayerState _OldState;		//�O�t���[���̃v���C���[�̏��
public:
	//������
	void Init(Vector3D v);
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
	//�ړ��֐�
	void Move(float rot_y);
	//�ʏ��Ԃ̃A�N�V�����֐�
	void NormalAct();
	//�e��Ԃ̃A�N�V�����֐�
	void ShadowAct();
	//�W�����v��Ԃ̃A�N�V�����֐�
	void JumpAct();
	//�e���|�[�g��Ԃ̃A�N�V�����֐�
	void TeleportAct();
	//�ǂ̂ڂ��Ԃ̃A�N�V�����֐�
	void ClimbAct();
	//�e���|�[�g�֐�
	void TeleportCalc(Vector3D shadow_pos);
	//���S�֐�
	void DeathCalc();
	//���X�|�[���֐�
	void ReSpawn();

	//���W�擾
	Vector3D GetPos() { return _Pos; }
	//��]�p�x��
	Vector3D GetRot() { return _Rot; }
	//���W�Z�b�g
	void SetPos(Vector3D v) { _Pos = v; }
	//��]�p�xX�Z�b�g
	void SetRotX(float rot_x) { _Rot._X = rot_x; }
	//��]�p�xX�Z�b�g
	void SetRotY(float rot_y) { _Rot._Y = rot_y; }
	//�e���|�[�g���W�擾
	Vector3D GetTeleportPos() { return _TeleportPos; }
	//�e���|�[�g���W�Z�b�g
	void SetTeleportPos(Vector3D v) { _TeleportPos = v; }
	//�O�����x�N�g���擾
	Vector3D GetForward() { return _Forward; }
	//��Ԏ擾
	const ePlayerState GetState() { return _State; }
	//��ԃZ�b�g
	void SetState(ePlayerState s) { _State = s; }
	//�R�C���擾
	const int GetCoin() { return _HaveCoin; }
	//�R�C�����Z
	void AddCoin() { _HaveCoin++; }
	//�R�C�����Z
	void SubCoin(int n) { _HaveCoin -= n; }
	//�����t���O�擾
	const bool GetActive() { return _IsActive; }
	//�e���|�[�g�t���O�擾
	const bool GetTeleport() { return _Teleport; }
	//�e���|�[�g�t���O�Z�b�g
	void SetTeleport(bool f) { _Teleport = f; }
	//�o��t���O�擾
	const bool GetClimb() { return _IsClimb; }
	//�o��t���O�Z�b�g
	void SetClimb(bool f) { _IsClimb = f; }
	//�n�ʂɂ��邩�t���O�擾
	const bool GetGround() { return _IsGround; }
	//�n�ʂɂ��邩�t���O�Z�b�g
	void SetGround(bool f) { _IsGround = f; }
	//�G���A�ɐG��Ă��邩�t���O�擾
	const bool GetHitArea() { return _HitArea; }
	//�G���A�ɐG��Ă��邩�t���O�Z�b�g
	void SetHitArea(bool f) { _HitArea = f; }
	//�N���A�������t���O�擾
	const bool GetClear() { return _IsClear; }
	//�N���A�������t���O�Z�b�g
	void SetClear(bool f) { _IsClear = f; }
	//���񂾂��t���O�擾
	const bool GetDeath() { return _IsDeath; }
	//���񂾂��t���O�Z�b�g
	void SetDeath(bool f) { _IsDeath = f; }
	//�G�t�F�N�g�n���h���擾
	const int GetEffectHndl() { return _DeathEffectHndl; }
	//�G�t�F�N�g�n���h���Z�b�g
	void SetEffectHndl(int hndl) { _DeathEffectHndl = hndl; }
	//���a�擾
	const float GetRad() { return _Rad; }

	//�A�N�V�����؂�ւ��֐��|�C���^
	void (CPlayer::* ActFunc[static_cast<int>(ePlayerState::NUM)])() =
	{ &CPlayer::NormalAct, &CPlayer::ShadowAct, &CPlayer::JumpAct, &CPlayer::TeleportAct, &CPlayer::ClimbAct };
};
