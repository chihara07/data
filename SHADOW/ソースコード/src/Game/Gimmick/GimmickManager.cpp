#include "GimmickManager.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Player/Player.h"

//�M�~�b�N�f�[�^�p�X
constexpr char GIMMICK_DATA_PATH0[] = { "Data/Gimmick/GimmickData0.csv" };
constexpr char GIMMICK_DATA_PATH[] = { "Data/Gimmick/GimmickData.csv" };
constexpr char GIMMICK_DATA_PATH2[] = { "Data/Gimmick/GimmickData2.csv" };
constexpr char GIMMICK_DATA_PATH3[] = { "Data/Gimmick/GimmickData3.csv" };
constexpr char GIMMICK_DATA_PATH4[] = { "Data/Gimmick/GimmickData4.csv" };

//�R���X�g���N�^�E�f�X�g���N�^
CGimmickManager::CGimmickManager(): _GimmickID(), _GimmickNum() {

}

CGimmickManager::~CGimmickManager() {
	Fin();
	cSwitchManager->DeleteInstance();
}

//������
void CGimmickManager::Init() {
	//�X�e�[�WID�ɂ��킹�ăf�[�^���[�h
	if (StageID == eStageID::STAGE_0) {
		CFile::Load(_GimmickData, GIMMICK_DATA_PATH0);
		_GimmickNum = GIMMICK_NUM0;
	}
	else if (StageID == eStageID::STAGE_1) {
		CFile::Load(_GimmickData, GIMMICK_DATA_PATH);
		_GimmickNum = GIMMICK_NUM;
	}
	else if (StageID == eStageID::STAGE_2) {
		CFile::Load(_GimmickData, GIMMICK_DATA_PATH2);
		_GimmickNum = GIMMICK_NUM2;
	}
	else if (StageID == eStageID::STAGE_3) {
		CFile::Load(_GimmickData, GIMMICK_DATA_PATH3);
		_GimmickNum = GIMMICK_NUM3;
	}
	else if (StageID == eStageID::STAGE_4) {
		CFile::Load(_GimmickData, GIMMICK_DATA_PATH4);
		_GimmickNum = GIMMICK_NUM4;
	}

	//�f�[�^�̃M�~�b�N�̎�ނɍ��킹�ăM�~�b�N����
	for (int gimmick_index = 0; gimmick_index < _GimmickNum; gimmick_index++) {
		CreateGimmick(static_cast<CGimmickObj::eGimmickType>(_GimmickData[gimmick_index][static_cast<int>(eGimmickData::TYPE2)]));
	}

	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Init();
	}
	_GimmickID = 0;
}

//���[�h
void CGimmickManager::Load() {
	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Load();
	}
	cSwitchManager->Load();
}

//�Z�b�g
void CGimmickManager::Set() {
	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Set();
	}
	cSwitchManager->Set();
}

//�f�[�^�Z�b�g
void CGimmickManager::DataSet() {
	//�f�[�^�̎�ނ��ƂɃf�[�^�Z�b�g
	for (auto gimmick_itr : _GimmickList) {
		CGimmickObj::eGimmickType t = static_cast<CGimmickObj::eGimmickType>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE2)]);
		//����������Ȃ�̂ł�������ۑ�����
		Vector3D vec1(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC_X)], _GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC_Y)],
			_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC_Z)]);
		Vector3D vec2(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_X)], _GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_Y)],
			_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_Z)]);
		Vector3D vec3(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC3_X)], _GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC3_Y)],
			_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC3_Z)]);
		Vector3D rot(Vector3D::VGet(MyLib::ConvertDegreesToRadian(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_X)]),
			MyLib::ConvertDegreesToRadian(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_Y)]),
			MyLib::ConvertDegreesToRadian(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::VEC2_Z)])));
		Vector3D scale(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::SCALE_X)], _GimmickData[_GimmickID][static_cast<int>(eGimmickData::SCALE_Y)],
			_GimmickData[_GimmickID][static_cast<int>(eGimmickData::SCALE_Z)]);

		switch (t) {
		case CGimmickObj::eGimmickType::BLOCK:
			if (static_cast<CGimmickObj::eState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]) == CGimmickObj::eState::NORMAL) {
				gimmick_itr->SetPos(vec1);
			}
			else if(static_cast<CGimmickObj::eState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]) == CGimmickObj::eState::MOVE) {
				gimmick_itr->SetPos(vec1);
				gimmick_itr->SetMovePos1(vec1);
				gimmick_itr->SetMovePos2(vec2);
			}
			gimmick_itr->SetState(static_cast<CGimmickObj::eState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]));
			break;
		case CGimmickObj::eGimmickType::FENCE:
			gimmick_itr->SetPos(vec1);
			gimmick_itr->SetRot(rot);
			break;
		case CGimmickObj::eGimmickType::GOAL:
			gimmick_itr->SetPos(vec1);
			break;
		case CGimmickObj::eGimmickType::NOSHADOW:
			if (static_cast<CGimmickObj::eState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]) == CGimmickObj::eState::SPECIAL) {
				gimmick_itr->SetPos(vec3);
			}
			else {
				gimmick_itr->SetPos(vec1);
			}
			gimmick_itr->SetMovePos1(vec1);
			gimmick_itr->SetMovePos2(vec2);
			gimmick_itr->SetState(static_cast<CGimmickObj::eState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]));
			gimmick_itr->SetMoveID(static_cast<CGimmickObj::eMoveState>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::NOSHADOW_ID)]));
			break;
		case CGimmickObj::eGimmickType::TELEPORT:
			gimmick_itr->SetPos(vec1);
			gimmick_itr->SetRot(rot);
			if (static_cast<int>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]) != 0) {
				gimmick_itr->SetSwitch(cSwitchManager->CreateSwitch(vec3,
					static_cast<int>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)])));
			}
			else {
				gimmick_itr->SetActive(true);
			}
			break;
		case CGimmickObj::eGimmickType::TRAP:
			gimmick_itr->SetPos(vec1);
			break;
		case CGimmickObj::eGimmickType::WALL:
			gimmick_itr->SetPos(vec1);
			gimmick_itr->SetRot(rot);
			break;
		case CGimmickObj::eGimmickType::CROSS:
			gimmick_itr->SetPos(vec1);
			gimmick_itr->SetSpd(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE)]);
			break;
		default:																	break;
		}
		
		gimmick_itr->SetScale(scale);
		gimmick_itr->SetType(static_cast<CGimmickObj::eGimmickType>(_GimmickData[_GimmickID][static_cast<int>(eGimmickData::TYPE2)]));

		_GimmickID++;
	}
}

//���C������
void CGimmickManager::Step() {
	//�Ƃ肠�����v���C���[�̕ǂ̂ڂ�t���O�I�t
	CPlayer::GetInstance()->SetClimb(false);
	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Step();
	}
	cSwitchManager->Step();
}

//�����蔻��
void CGimmickManager::Collision() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	//�M�~�b�N�̎�ނ��Ƃɓ����蔻�菈��
	for (auto gimmick_itr : _GimmickList) {
		switch (gimmick_itr->GetType()) {
		case CGimmickObj::eGimmickType::BLOCK:
			break;
		case CGimmickObj::eGimmickType::FENCE:
			if (cPlayer->GetState() != CPlayer::ePlayerState::SHADOW) {
				cPlayer->SetPos(CCOllisionManager::HitCheck(cPlayer->GetPos(), cPlayer->GetRad(), gimmick_itr->GetCollisionHndl()));
			}
			break;
		case CGimmickObj::eGimmickType::GOAL:
			break;
		case CGimmickObj::eGimmickType::NOSHADOW:
			break;
		case CGimmickObj::eGimmickType::TELEPORT:
			if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
				CCOllisionManager::CheckHitPlayerToShadow(gimmick_itr);
			}
			break;
		case CGimmickObj::eGimmickType::TRAP:
			CCOllisionManager::CheckHitPlayerToTrap(gimmick_itr);
			break;
		case CGimmickObj::eGimmickType::WALL:
			if (cPlayer->GetGround() == false) {
				cPlayer->SetGround(CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), gimmick_itr->GetHndl()));
			}
			cPlayer->SetPos(CCOllisionManager::HitCheck(cPlayer->GetPos(), cPlayer->GetRad(), gimmick_itr->GetHndl()));
			cPlayer->SetTeleportPos(CCOllisionManager::HitCheck(cPlayer->GetTeleportPos(), cPlayer->GetRad(), gimmick_itr->GetHndl()));
			break;
		case CGimmickObj::eGimmickType::CROSS:
			if (cPlayer->GetGround() == false) {
				cPlayer->SetGround(CCOllisionManager::CheckCollision(cPlayer->GetPos(), cPlayer->GetRad(), gimmick_itr->GetCollisionHndl()));
			}
			cPlayer->SetPos(CCOllisionManager::HitCheck(cPlayer->GetPos(), cPlayer->GetRad(), gimmick_itr->GetCollisionHndl()));
			cPlayer->SetTeleportPos(CCOllisionManager::HitCheck(cPlayer->GetTeleportPos(), cPlayer->GetRad(), gimmick_itr->GetCollisionHndl()));
			break;
		}
	}

	if (cPlayer->GetState() != CPlayer::ePlayerState::SHADOW) {
		cSwitchManager->Collision();
	}
}

//�`��
void CGimmickManager::Draw() {
	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Draw();
	}
	cSwitchManager->Draw();
}

//�I��
void CGimmickManager::Fin() {
	for (auto gimmick_itr = _GimmickList.begin(); gimmick_itr != _GimmickList.end();) {
		(*gimmick_itr)->Fin();
		delete* gimmick_itr;
		gimmick_itr = _GimmickList.erase(gimmick_itr);
	}
	cSwitchManager->Fin();

	_GimmickData.clear();

	_GimmickID = 0;
	_GimmickNum = 0;
}

//�X�V����
void CGimmickManager::Update() {
	for (auto gimmick_itr : _GimmickList) {
		gimmick_itr->Update();
	}
}
