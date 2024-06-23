#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"

//�G�N���X
class CEnemyFlash : public CEnemyObj {
public:
	//�G�ɋ߂����̗p�񋓌^
	enum class eNearType {
		AREA1 = 0,
		AREA2,
		AREA3,
		PLAYER,
	};
private:
	Vector3D _FlashScale;		//�t���b�V���U���g�嗦
	Vector3D _AreaChaseVec;		//�e�G���A��ǂ��x�N�g���p
	int _FlashCount;			//�t���b�V���U���J�E���g
	int _FlashHndl;				//�t���b�V���U���n���h��
	bool _IsFlashStandby;		//�t���b�V���U�������t���O
	bool _IsFindArea[AREA_NUM];	//�e�G���A�����t���O
	eNearType _NearType;		//�߂����̎��
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyFlash();
	~CEnemyFlash();

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
	//�q�b�g�֐�
	void HitCalc();
	//�X�V����
	void Update();
	//�ړ��֐�
	void Move();
	//��ԕω��֐�
	void ChangeState();
	//�e�G���A��ǂ������Ă����Ԋ֐�
	void ChaseAreaAct();
	//�U����Ԋ֐�
	void AttackAct();
	//���G�͈͂ɉe�G���A�����邩
	bool CheckPlayerAreaLength(int id);
	//�e�G���A�ƃv���C���[�̂ǂꂪ�߂���
	void CheckLength();
	//�e�G���A�̃`�F�b�N
	void CheckArea();
	//�t���b�V���U���\��
	bool IsFlash();
	//�e�G���A�̕����߂���
	bool IsNearArea();
};
