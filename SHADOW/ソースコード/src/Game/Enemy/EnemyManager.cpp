#include "EnemyManager.h"
#include "../CollisionManager/CollisionManager.h"

//敵のモデルパス
constexpr char ENEMY_PATH[] = "data/Enemy/enemy.x";
//敵データパス
constexpr char ENEMY_DATA_PATH0[] = { "Data/Enemy/Enemydata0.csv" };
constexpr char ENEMY_DATA_PATH[] = { "Data/Enemy/EnemyData.csv" };
constexpr char ENEMY_DATA_PATH2[] = { "Data/Enemy/EnemyData2.csv" };
constexpr char ENEMY_DATA_PATH3[] = { "Data/Enemy/EnemyData3.csv" };
constexpr char ENEMY_DATA_PATH4[] = { "Data/Enemy/EnemyData4.csv" };

CEnemyManager* CEnemyManager::_Instance = nullptr;

CEnemyManager* CEnemyManager::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CEnemyManager;
	}

	return _Instance;
}

void CEnemyManager::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CEnemyManager::CEnemyManager(): _EnemyID(), _EnemyNum() {

}

CEnemyManager::~CEnemyManager() {
	Fin();
}

//初期化
void CEnemyManager::Init() {
	//ステージIDにあわせてデータロード
	if (StageID == eStageID::STAGE_0) {
		CFile::Load(_EnemyData, ENEMY_DATA_PATH0);
		_EnemyNum = ENEMY_NUM0;
	}
	else if (StageID == eStageID::STAGE_1) {
		CFile::Load(_EnemyData, ENEMY_DATA_PATH);
		_EnemyNum = ENEMY_NUM;
	}
	else if (StageID == eStageID::STAGE_2) {
		CFile::Load(_EnemyData, ENEMY_DATA_PATH2);
		_EnemyNum = ENEMY_NUM2;
	}
	else if (StageID == eStageID::STAGE_3) {
		CFile::Load(_EnemyData, ENEMY_DATA_PATH3);
		_EnemyNum = ENEMY_NUM3;
	}
	else if (StageID == eStageID::STAGE_4) {
		CFile::Load(_EnemyData, ENEMY_DATA_PATH4);
		_EnemyNum = ENEMY_NUM4;
	}

	//データの敵の種類にあわせて敵生成
	for (int enemy_index = 0; enemy_index < _EnemyNum; enemy_index++) {
		CreateEnemy(static_cast<CEnemyObj::eEnemyType>(_EnemyData[enemy_index][static_cast<int>(eEnemyData::TYPE)]));
	}

	//初期化
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Init();
	}
	_EnemyID = 0;
}

//ロード
void CEnemyManager::Load() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Load();
	}
}

//セット
void CEnemyManager::Set() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Set();
	}
}

//データセット
void CEnemyManager::DataSet() {
	//データの種類ごとにデータセット
	for (auto enemy_itr : _EnemyList) {
		//代入時長くなるのでいったん保存する
		Vector3D vec1(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC_X)], _EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC_Y)],
						_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC_Z)]);
		Vector3D vec2(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_X)], _EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_Y)],
			_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_Z)]);
		Vector3D rot(Vector3D::VGet(MyLib::ConvertDegreesToRadian(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_X)]),
			MyLib::ConvertDegreesToRadian(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_Y)]),
			MyLib::ConvertDegreesToRadian(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::VEC2_Z)])));
		Vector3D limitCenterPos(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::LIMIT_POS_X)], 0.f,
			_EnemyData[_EnemyID][static_cast<int>(eEnemyData::LIMIT_POS_Z)]);
		Vector2D limitDistance(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::LIMIT_DIS_X)],
			_EnemyData[_EnemyID][static_cast<int>(eEnemyData::LIMIT_DIS_Y)]);

		if (static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]) == CEnemyObj::eEnemyType::NORMAL ||
			static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]) == CEnemyObj::eEnemyType::FLASH ||
			static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]) == CEnemyObj::eEnemyType::WALL) {
			enemy_itr->SetMovePos1(vec1);
			enemy_itr->SetMovePos2(vec2);
			enemy_itr->SetPos(vec1);
			enemy_itr->SetLimitCenterPos(limitCenterPos);
			enemy_itr->SetLimitDistance(limitDistance);
			enemy_itr->SetType(static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]));
			enemy_itr->SetCoinType(static_cast<CEnemyObj::eCoin>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::COIN_TYPE)]));

			//コインを持っているならコイン生成
			if (enemy_itr->GetCoinType() == CEnemyObj::eCoin::HAVE) {
				enemy_itr->SetCoin(cCoinManager->CreateCoin());
			}
		}
		else if (static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]) == CEnemyObj::eEnemyType::SHOT) {
			enemy_itr->SetPos(vec1);
			enemy_itr->SetResetRot(rot);
			enemy_itr->SetType(static_cast<CEnemyObj::eEnemyType>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::TYPE)]));
			enemy_itr->SetCoinType(static_cast<CEnemyObj::eCoin>(_EnemyData[_EnemyID][static_cast<int>(eEnemyData::COIN_TYPE)]));
		
			//コインを持っているならコイン生成
			if (enemy_itr->GetCoinType() == CEnemyObj::eCoin::HAVE) {
				enemy_itr->SetCoin(cCoinManager->CreateCoin());
			}
		}
		_EnemyID++;
	}
}

//メイン処理
void CEnemyManager::Step() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Step();
	}
}

//当たり判定
void CEnemyManager::Collision(int hndl) {
	//敵の種類ごとに当たり判定処理
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->SetPos(CCOllisionManager::HitCheck(enemy_itr->GetPos(), enemy_itr->GetRad(), hndl));
		CCOllisionManager::CheckHitPlayerToEnemy(enemy_itr);
		if (enemy_itr->GetType() == CEnemyObj::eEnemyType::NORMAL) {
			CCOllisionManager::CheckHitPlayerAttackToEnemy(enemy_itr);
		}
		else if (enemy_itr->GetType() == CEnemyObj::eEnemyType::SHOT) {
			CCOllisionManager::CheckHitPlayerAttackToEnemy(enemy_itr);
			CCOllisionManager::CheckHitPlayerToEnemyBullet(enemy_itr);
		}
		else if (enemy_itr->GetType() == CEnemyObj::eEnemyType::FLASH) {
			CCOllisionManager::CheckHitPlayerAttackToEnemy(enemy_itr);
			CCOllisionManager::CheckHitFlashToArea(enemy_itr);
			CCOllisionManager::CheckHitPlayerToFlash(enemy_itr);
		}
		else if (enemy_itr->GetType() == CEnemyObj::eEnemyType::WALL) {

		}
	}
}

//描画
void CEnemyManager::Draw() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Draw();
	}
}

//終了
void CEnemyManager::Fin() {
	for (auto enemy_itr = _EnemyList.begin(); enemy_itr != _EnemyList.end();) {
		(*enemy_itr)->Fin();
		delete* enemy_itr;
		enemy_itr = _EnemyList.erase(enemy_itr);
	}

	_EnemyData.clear();

	_EnemyID = 0;
	_EnemyNum = 0;
}

//更新処理
void CEnemyManager::Update() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->Update();
	}
}

//リセット処理
void CEnemyManager::Reset() {
	for (auto enemy_itr : _EnemyList) {
		enemy_itr->HitCalc();
	}
}
