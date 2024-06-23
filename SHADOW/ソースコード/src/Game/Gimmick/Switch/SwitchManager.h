#pragma once
#include "DxLib.h"
#include "Switch.h"
#include "../../Library/File/File.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

//�X�C�b�`�}�l�[�W���[�N���X
class CSwitchManager {
private:
	//�R���X�g���N�^�E�f�X�g���N�^
	CSwitchManager();
	~CSwitchManager();

	static CSwitchManager* _Instance;		//�C���X�^���X

	//����������h��
	CSwitchManager(const CSwitchManager& other);
	CSwitchManager operator= (const CSwitchManager& other) {}

	int _Hndl;							//�X�C�b�`�̃��f���n���h��
	int _PressedHndl;					//�����ꂽ���f���n���h��
public:
	//�C���X�^���X�擾
	static CSwitchManager* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();

	//������
	void Init();
	//���[�h
	void Load();
	//�Z�b�g
	void Set();
	//���C������
	void Step();
	//�����蔻��
	void Collision();
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�X�V����
	void Update();
	//�X�C�b�`����
	CSwitch* CreateSwitch(Vector3D p, int n) {
		CSwitch* result = nullptr;
		result = New CSwitch();
		//���W�ƕK�v�R�C�������Z�b�g���i�[����
		result->SetPos(p);
		result->SetNeedCoinNum(n);
		_SwitchList.push_back(result);
		return result;
	}
	//�w��̓G�폜
	void DeleteSwitch(const CSwitch* p) {
		for (auto switch_itr = _SwitchList.begin(); switch_itr != _SwitchList.end(); ++switch_itr) {
			auto coin = *switch_itr;
			if (coin != p)
				continue;
			delete p;
			_SwitchList.erase(switch_itr);
			break;
		}
	}

	//�X�C�b�`�i�[�p���X�g
	list<CSwitch*> _SwitchList;
};