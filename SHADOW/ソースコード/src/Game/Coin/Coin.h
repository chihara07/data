#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

//�G�N���X
class CCoin {
public:
	//�G�̎�ޗp�񋓌^
	enum class eCoinType {
		NONE,		//�s����
		HAVE,		//����

		NUM,
	};
private:
	Vector3D _Pos;			//���W1
	Vector3D _Rot;			//�R�C����]�p�x
	Vector3D _Scale;		//�g�嗦
	int _Hndl;				//�n���h��
	float _Rad;				//���a
	bool _IsActive;			//�R�C�������t���O
	eCoinType _CoinType;	//�G�̎��
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCoin();
	~CCoin();

	//������
	void Init();
	//�Z�b�g
	void Set();
	//���[�h
	void Load(int coin_hndl);
	//���C������
	void Step();
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�����蔻��
	void Collision();
	//�X�V����
	void Update();

	//���W�擾
	Vector3D GetPos() { return _Pos; }
	//���W�Z�b�g
	void SetPos(Vector3D v) { _Pos = v; }
	//���a�擾
	const float GetRad() { return _Rad; }
	//�����t���O�擾
	const bool GetActive() { return _IsActive; }
	//�����t���O�Z�b�g
	void SetActive(bool f) { _IsActive = f; }
	//��ގ擾
	const eCoinType GetCoinType() { return _CoinType; }
	//��ރZ�b�g
	void SetCoinType(eCoinType t) { _CoinType = t; }
};
