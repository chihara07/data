#pragma once
#include "DxLib.h"
#include "../../Game/Coin/Coin.h"
#include "../../Library/File/File.h"
#include <list>
#include "../../Library/Common.h"

using namespace std;

//�R�C���̃��f���p�X
constexpr char COIN_PATH[] = "data/Enemy/coin.x";

//�G�}�l�[�W���[�N���X
class CCoinManager {
private:
	//�R���X�g���N�^�E�f�X�g���N�^
	CCoinManager();
	~CCoinManager();

	static CCoinManager* _Instance;		//�C���X�^���X

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CCoinManager(const CCoinManager& other);
	CCoinManager operator= (const CCoinManager& other) {}

	int _Hndl;							//�n���h��
public:
	//�C���X�^���X�擾
	static CCoinManager* GetInstance();

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
	//�R�C���N���X����
	CCoin* CreateCoin() {
		CCoin* result = nullptr;
		result = New CCoin();
		_CoinList.push_back(result);
		return result;
	}
	//�w��̃R�C���폜
	void DeleteCoin(const CCoin* p) {
		for (auto coin_itr = _CoinList.begin(); coin_itr != _CoinList.end(); ++coin_itr) {
			auto coin = *coin_itr;
			if (coin != p)
				continue;
			delete p;
			_CoinList.erase(coin_itr);
			break;
		}
	}

	list<CCoin*> _CoinList;		//�R�C���N���X�i�[���X�g
};