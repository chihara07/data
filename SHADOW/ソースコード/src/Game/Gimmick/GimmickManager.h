#pragma once
#include "DxLib.h"
#include "../Object/GimmickObj.h"
#include "Block/Block.h"
#include "Fence/Fence.h"
#include "Goal/Goal.h"
#include "NoShadow/NoShadow.h"
#include "Teleport/Teleport.h"
#include "Trap/Trap.h"
#include "Wall/Wall.h"
#include "Cross/Cross.h"
#include "Switch/SwitchManager.h"
#include "../../Library/File/File.h"
#include "../Camera/Camera.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

constexpr int GIMMICK_NUM0 = 5;			//stage0�̃M�~�b�N�̐�
constexpr int GIMMICK_NUM = 14;			//stage1�̃M�~�b�N�̐�
constexpr int GIMMICK_NUM2 = 29;		//stage2�̃M�~�b�N�̐�
constexpr int GIMMICK_NUM3 = 31;		//stage3�̃M�~�b�N�̐�
constexpr int GIMMICK_NUM4 = 28;		//stage4�̃M�~�b�N�̐�

//�M�~�b�N�}�l�[�W���[�N���X
class CGimmickManager {
private:
	//�M�~�b�N�f�[�^
	enum class eGimmickData {
		ID = 0,				//�ԍ�
		VEC_X,				//�x�N�g��1X
		VEC_Y,				//�x�N�g��1Y
		VEC_Z,				//�x�N�g��1Z
		VEC2_X,				//�x�N�g��2X
		VEC2_Y,				//�x�N�g��2Y
		VEC2_Z,				//�x�N�g��2Z
		VEC3_X,				//�x�N�g��3X
		VEC3_Y,				//�x�N�g��3Y
		VEC3_Z,				//�x�N�g��3Z
		SCALE_X,			//�g�嗦X
		SCALE_Y,			//�g�嗦Y
		SCALE_Z,			//�g�嗦Z
		TYPE,				//�M�~�b�N���Ƃ̎��
		NOSHADOW_ID,		//�e�֎~�G���A�̓���ID
		TYPE2,				//�M�~�b�N�̎��

		DATA_NUM,
	};

	int _GimmickID;						//�GID
	int _GimmickNum;					//�G�̐�
	vector<vector<float>> _GimmickData;	//�G�f�[�^

	//�X�C�b�`�}�l�[�W���[�擾
	CSwitchManager* cSwitchManager = CSwitchManager::GetInstance();
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	CGimmickManager();
	~CGimmickManager();

	//������
	void Init();
	//���[�h
	void Load();
	//�Z�b�g
	void Set();
	//�f�[�^�Z�b�g
	void DataSet();
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
	//�M�~�b�N����
	CGimmickObj* CreateGimmick(CGimmickObj::eGimmickType t) {
		CGimmickObj* result = nullptr;
		switch (t) {
		case CGimmickObj::eGimmickType::BLOCK:		result = New CBlock;			break;
		case CGimmickObj::eGimmickType::FENCE:		result = New CFence;			break;
		case CGimmickObj::eGimmickType::GOAL:		result = New CGoal;				break;
		case CGimmickObj::eGimmickType::NOSHADOW:	result = New CNoShadow;			break;
		case CGimmickObj::eGimmickType::TELEPORT:	result = New CTeleportShadow;	break;
		case CGimmickObj::eGimmickType::TRAP:		result = New CTrap;				break;
		case CGimmickObj::eGimmickType::WALL:		result = New CWall;				break;
		case CGimmickObj::eGimmickType::CROSS:		result = New CCross;				break;
		default:																	break;
		}
		_GimmickList.push_back(result);
		return result;
	}
	//�w��̃M�~�b�N�폜
	void DeleteGimmick(const CGimmickObj* p) {
		for (auto enemy_itr = _GimmickList.begin(); enemy_itr != _GimmickList.end(); ++enemy_itr) {
			auto enemy = *enemy_itr;
			if (enemy != p)
				continue;
			delete p;
			_GimmickList.erase(enemy_itr);
			break;
		}
	}

	//�M�~�b�N�i�[�p���X�g
	list<CGimmickObj*> _GimmickList;
};
