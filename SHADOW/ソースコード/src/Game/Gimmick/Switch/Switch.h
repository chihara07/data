#pragma once
#include "DxLib.h"
#include "../../Library/Vector/Vector3D.h"

constexpr int NEED_COIN_MAX_NUM = 3;	//�K�v�R�C���ő吔

//�X�C�b�`�N���X
class CSwitch {
private:
	Vector3D _Pos;						//���W
	Vector3D _Scale;					//�䗦
	Vector3D _Rot;						//��]�p�x
	int _Hndl;							//���f���n���h��
	int _PressedHndl;					//�����ꂽ���f���n���h��
	int _CoinHndl[NEED_COIN_MAX_NUM];	//�R�C���摜�n���h��
	int _NeedCoinNum;					//�K�v�R�C������
	float _Rad;							//���a
	bool _IsPressed;					//�����ꂽ��
	bool _IsHit;						//�G��Ă��邩
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSwitch();
	~CSwitch();

	//������
	void Init();
	//�Z�b�g
	void Set();
	//���[�h
	void Load();
	//���C������
	void Step();
	//�`��
	void Draw();
	//�K�v�R�C���\��
	void HitCalc();
	//�I��
	void Fin();
	//�X�V����
	void Update();
	//�����ꂽ�֐�
	void PressedCalc();

	//���W�擾
	Vector3D GetPos() { return _Pos; }
	//�����ꂽ���t���O�擾
	bool GetPressed() { return _IsPressed; }
	//���W�Z�b�g
	void SetPos(Vector3D v) { _Pos = v; }
	//���a�擾
	float GetRad() { return _Rad; }
	//�K�v�R�C�������擾
	int GetNeedCoinNum() { return _NeedCoinNum; }
	//�K�v�R�C�������Z�b�g
	void SetNeedCoinNum(int n) { _NeedCoinNum = n; }
};
