#pragma once
#include "PlayerUI.h"
#include "Player.h"
#include "PlayerAttack.h"

//�v���C���[�}�l�[�W���[�N���X
class CPlayerManager {
private:
	CPlayer* cPlayer = CPlayer::GetInstance();
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayerUI cPlayerUI;
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CPlayerManager();
	~CPlayerManager();

	//������
	void Init();
	//���[�h
	void Load();
	//�Z�b�g
	void Set();
	//���C������
	void Step();
	//�����蔻��
	void Collision(int map_hndl);
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�X�V����
	void Update();
	//�j��
	void Delete();
};
