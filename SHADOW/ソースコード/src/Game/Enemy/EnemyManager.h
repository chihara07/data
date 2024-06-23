#pragma once
#include "DxLib.h"
#include "../Object/EnemyObj.h"
#include "../../Game/Enemy/Enemy.h"
#include "../../Game/Enemy/EnemyFlash.h"
#include "../../Game/Enemy/EnemyShot.h"
#include "../../Game/Enemy/EnemyWall.h"
#include "../../Library/File/File.h"
#include "../Camera/Camera.h"
#include <list>
#include "../../Library/Common.h"
#include "../Coin/CoinManager.h"

using namespace std;

constexpr int ENEMY_NUM0 = 4;		//�G�̐�
constexpr int ENEMY_NUM = 12;		//�G�̐�
constexpr int ENEMY_NUM2 = 16;		//stage2�̓G�̐�
constexpr int ENEMY_NUM3 = 11;		//stage3�̓G�̐�
constexpr int ENEMY_NUM4 = 8;		//stage3�̓G�̐�

//�G�}�l�[�W���[�N���X
class CEnemyManager {
private:
	//�G�f�[�^
	enum class eEnemyData {
		ID = 0,				//�ԍ�
		VEC_X,				//�x�N�g��1X
		VEC_Y,				//�x�N�g��1Y
		VEC_Z,				//�x�N�g��1Z
		VEC2_X,				//�x�N�g��2X
		VEC2_Y,				//�x�N�g��2Y
		VEC2_Z,				//�x�N�g��2Z
		LIMIT_POS_X,		//�ړ�����X���W
		LIMIT_POS_Z,		//�ړ�����Z���W
		LIMIT_DIS_X,		//�ړ�����X����
		LIMIT_DIS_Y,		//�ړ�����Y����
		TYPE,				//���
		COIN_TYPE,			//�R�C���������Ă邩

		DATA_NUM,
	};

	//�R���X�g���N�^�E�f�X�g���N�^
	CEnemyManager();
	~CEnemyManager();

	//�C���X�^���X
	static CEnemyManager* _Instance;

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CEnemyManager(const CEnemyManager& other);
	CEnemyManager operator= (const CEnemyManager& other) {}

	int _EnemyID;						//�GID
	int _EnemyNum;						//�G�̐�
	vector<vector<float>> _EnemyData;	//�G�f�[�^

	//�R�C���}�l�[�W���[�擾
	CCoinManager* cCoinManager = CCoinManager::GetInstance();
public:
	//�C���X�^���X�擾
	static CEnemyManager* GetInstance();
	//�C���X�^���X�폜
	static void DeleteInstance();

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
	void Collision(int hndl);
	//�`��
	void Draw();
	//�I��
	void Fin();
	//�X�V����
	void Update();
	//���Z�b�g����
	void Reset();
	//�G����
	CEnemyObj* CreateEnemy(CEnemyObj::eEnemyType t) {
		CEnemyObj* result = nullptr;
		switch (t) {
		case CEnemyObj::eEnemyType::NORMAL:	result = New CEnemy;		break;
		case CEnemyObj::eEnemyType::SHOT:	result = New CEnemyShot;	break;
		case CEnemyObj::eEnemyType::FLASH:	result = New CEnemyFlash;	break;
		case CEnemyObj::eEnemyType::WALL:	result = New CEnemyWall;	break;
		default:												break;
		}
		_EnemyList.push_back(result);
		return result;
	}
	//�w��̓G�폜
	void DeleteEnemy(const CEnemyObj* p) {
		for (auto enemy_itr = _EnemyList.begin(); enemy_itr != _EnemyList.end(); ++enemy_itr) {
			auto enemy = *enemy_itr;
			if (enemy != p)
				continue;
			delete p;
			_EnemyList.erase(enemy_itr);
			break;
		}
	}

	//�G�i�[���X�g
	list<CEnemyObj*> _EnemyList;
};