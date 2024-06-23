#pragma once
#include "DxLib.h"
#include "../../Object/GimmickObj.h"
#include "../../Library/Vector/Vector3D.h"

//�e���|�[�g�e�N���X
class CTeleportShadow : public CGimmickObj {
private:
	Vector3D _SelectingPos;		//�I�𒆂̉e���W
	int _SelectHndl;			//�I�𒆂̉e���f���n���h��
	bool _CheckTeleport;		//�e���|�[�g�\���ǂ����t���O
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CTeleportShadow();
	~CTeleportShadow();

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
	//�q�b�g�֐�
	void HitCalc();

	//�e���|�[�g�\���ǂ����t���O�Z�b�g
	void SetCheckTeleport(bool f) { _CheckTeleport = f; }
};
