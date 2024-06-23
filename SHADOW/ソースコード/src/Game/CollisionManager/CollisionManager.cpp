#include "CollisionManager.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Color.h"
#include "../../Library/Common.h"
#include "../../Library/Sound/SoundManager.h"
#include "../Player/Player.h"
#include "../Player/PlayerAttack.h"
#include "../../Library/Effect/effekseer.h"

//�@�����ׂ�Ƃ��̌덷
constexpr float NORMAL_ERROR = 0.01f;

//�v���C���[�ƓG�̓����蔻��
void  CCOllisionManager::CheckHitPlayerToEnemy(CEnemyObj* cEnemy) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cPlayer->GetDeath() == true || cEnemy->GetActive() == false)
		return;

	//�v���C���[�ƓG���������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetPos(), cEnemy->GetRad())) {
		//�v���C���[���S�֐����s
		cPlayer->DeathCalc();
	}
}

//�v���C���[�ƃt���b�V���U���̓����蔻��
void CCOllisionManager::CheckHitPlayerToFlash(CEnemyObj* cEnemy) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cEnemy->GetFlashActive() == false || cPlayer->GetDeath() == true || cEnemy->GetActive() == false ||
		(cPlayer->GetState() != CPlayer::ePlayerState::SHADOW && cPlayer->GetState() != CPlayer::ePlayerState::CLIMB))
		return;

	//�v���C���[�ƃt���b�V���U�����������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetPos(), cEnemy->GetFlashRad())) {
		//�v���C���[���S�֐����s
		cPlayer->DeathCalc();
	}

}

//�v���C���[�ƓG�̒e�̓����蔻��
void  CCOllisionManager::CheckHitPlayerToEnemyBullet(CEnemyObj* cEnemy) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	if (cPlayer->GetState() == CPlayer::ePlayerState::SHADOW || cPlayer->GetState() == CPlayer::ePlayerState::CLIMB ||
		cEnemy->GetActive() == false || cEnemy->GetBulletActive() == false || cPlayer->GetDeath() == true)
		return;

	//�v���C���[�ƓG�̒e���������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cEnemy->GetBulletPos(), cEnemy->GetBulletRad())) {
		//�v���C���[���S�֐����s
		cPlayer->DeathCalc();
	}
}

//�v���C���[�̍U���ƓG�̓����蔻��
void CCOllisionManager::CheckHitPlayerAttackToEnemy(CEnemyObj* cEnemy) {
	//�v���C���[�擾�A�v���C���[�U���擾
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();


	if (cEnemy->GetActive() == false || cPlayer->GetDeath() == true || cPlayerAttack->GetActive() == false
		|| cEnemy->GetState() == CEnemy::eEnemyState::KNOCKBACK)
		return;

	for (int attack_index = 0; attack_index < ATTACK_NUM; attack_index++) {

		//�v���C���[�̍U���ƓG���������Ă��邩
		if (CCollision::IsHitSphere(cPlayerAttack->GetPos(attack_index), cPlayerAttack->GetRad(), cEnemy->GetPos(), cEnemy->GetRad()))
		{
			if (cEnemy->GetType() != CEnemyObj::eEnemyType::WALL) {
				if (cEnemy->GetForward() || cEnemy->GetState() == CEnemy::eEnemyState::DISCOVERY) {
					cEnemy->SubLife();
					cEnemy->SetState(CEnemy::eEnemyState::KNOCKBACK);
					cEnemy->SetMoveVec(cPlayer->GetPos().Create(cEnemy->GetPos()));
					break;
				}
				else
					//�G���S�֐����s
					cEnemy->DeathCalc();
			}
			else {
				if (cEnemy->GetForward() == false) {
					//�G���S�֐����s
					cEnemy->DeathCalc();
				}
			}
		}
	}
}

//�v���C���[�̉e�G���A�ƃv���C���[�̓����蔻��
void CCOllisionManager::CheckHitPlayerToArea() {
	//�v���C���[�擾�A�v���C���[�U���擾
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();
	CPlayer* cPlayer = CPlayer::GetInstance();


	if (cPlayer->GetDeath() == true)
		return;

	//�Ƃ肠�����ڐG�t���O�I�t
	cPlayer->SetHitArea(false);
	
	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;
		//�v���C���[�̉e�G���A�ƃv���C���[���������Ă��邩
		if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), cPlayer->GetPos(), cPlayer->GetRad()))
		{
			cPlayer->SetHitArea(true);
		}
	}
}

//�G�̍U���Ɖe�G���A����
void CCOllisionManager::CheckHitFlashToArea(CEnemyObj* cEnemy) {
	if (cEnemy->GetFlashActive() == false || cEnemy->GetActive() == false)
		return;

	//�v���C���[�擾�A�v���C���[�U���擾
	CPlayerAttack* cPlayerAttack = CPlayerAttack::GetInstance();

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (cPlayerAttack->GetAreaActive(area_index) == false)
			continue;
		//�e�G���A�ƓG�̍U�����������Ă��邩
		if (CCollision::IsHitSphere(cPlayerAttack->GetAreaPos(area_index), cPlayerAttack->GetAreaRad(area_index), cEnemy->GetPos(), cEnemy->GetFlashRad())){
			//�������Ă���Ȃ炻�̉e�G���A�ƓG�̐ڐG�t���O���I�t
			cPlayerAttack->AreaReset(area_index);
			cEnemy->SetHitArea(area_index, false);
		}
	}
}

//�v���C���[�ƓG�̃R�C�������蔻��
bool CCOllisionManager::CheckHitPlayerToCoin(Vector3D coin_pos, float coin_rad, bool coin_active) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cPlayer->GetDeath() == true || coin_active == false)
		return false;

	//�v���C���[�ƓG�̃R�C�����������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), coin_pos, coin_rad))
	{
		//�������Ă���Ȃ�v���C���[�̏��������𑝂₵�A�R�C���̃t���O��false��Ԃ�
		cPlayer->AddCoin();
		return false;
	}
	else
		return true;
}

//�v���C���[�Ɖe�̓����蔻��
void CCOllisionManager::CheckHitPlayerToShadow(CGimmickObj* cGimmick) {
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cGimmick->GetActive() == true) {
		//�v���C���[�Ɖe���������Ă��邩
		if (CCollision::IsHitSphere(cPlayer->GetTeleportPos(), cPlayer->GetRad(), cGimmick->GetPos(), cGimmick->GetRad()))
		{
			//�������Ă���Ȃ�v���C���[�̃e���|�[�g�֐��ƃM�~�b�N�̃q�b�g�֐����s
			cPlayer->TeleportCalc(cGimmick->GetPos());
			cGimmick->HitCalc();
		}
	}
}

//�v���C���[�ƃX�C�b�`�̓����蔻��
void CCOllisionManager::CheckHitPlayerToSwitch(CSwitch* cSwitch) {
	CPlayer* cPlayer = CPlayer::GetInstance();

	if (cSwitch->GetPressed() == true)
		return;

	//�v���C���[�ƃX�C�b�`���������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cSwitch->GetPos(), cSwitch->GetRad()))
	{
		//�������Ă���Ȃ�X�C�b�`�̃q�b�g�֐����s
		cSwitch->HitCalc();

		//�v���C���[�̏����������K�v�������邩
		if (cPlayer->GetCoin() >= cSwitch->GetNeedCoinNum()) {
			//�K�v��������Ȃ�X�C�b�`������
			CSoundManager::Play(CSoundManager::eSoundID::SE_SWITCH);
			cSwitch->PressedCalc();
			cPlayer->SubCoin(cSwitch->GetNeedCoinNum());
		}
	}
}

//�v���C���[�ƃg���b�v�̓����蔻��
void CCOllisionManager::CheckHitPlayerToTrap(CGimmickObj* cGimmick) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	//�v���C���[�ƃg���b�v���������Ă��邩
	if (CCollision::IsHitSphere(cPlayer->GetPos(), cPlayer->GetRad(), cGimmick->GetPos(), cGimmick->GetRad())
		&& cPlayer->GetDeath() == false) {
		//�v���C���[���S�֐����s
		cPlayer->DeathCalc();
	}
}

//�}�b�v�Ƃ̓����蔻��
bool CCOllisionManager::CheckCollision(Vector3D pos, float rad, const int hndl) {
	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(hndl, -1, TRUE);

	// �|���S���̐������J��Ԃ�
	for (int pol_index = 0; pol_index < polygons.PolygonNum; pol_index++) {
		// �|���S�������擾����
		MV1_REF_POLYGON polygon = polygons.Polygons[pol_index];
		// �|���S�����`������O�p�`��3���_���擾����
		Vector3D vertexs[3];
		int index = polygon.VIndex[0];
		vertexs[0] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[1];
		vertexs[1] = polygons.Vertexs[index].Position;
		index = polygon.VIndex[2];
		vertexs[2] = polygons.Vertexs[index].Position;

		// �|���S���@�����Z�o����
		Vector3D norm = GetPolygonNormalVec(vertexs[0], vertexs[1], vertexs[2]);
		// �@����Y������MAP_FLOOR_NORM_Y_MIN�ȏ�ł���Ώ�
		if (norm._Y >= MAP_FLOOR_NORM_Y_MIN) {
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(pos, vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕��������珰�̍������v�Z
				float floor_height = GetTriangleHeightXZ(pos, vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = pos._Y - rad;
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ ���� �����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && MyLib::Abs(dist) <= rad) {
					return  true;
				}
			}
		}
	}

	return false;
}

//���f���Ƃ̓����蔻��
Vector3D CCOllisionManager::HitCheck(Vector3D pos, float rad, const int hndl) {
	//�����o���x�N�g��
	Vector3D pushVec(Vector3D::ZeroVec());
	//���������Ƃ���Ƃ̋����x�N�g��
	Vector3D distance(Vector3D::ZeroVec());
	//���������Ƃ���Ƃ̋���
	float length = 0.f;
	CollData data;
	list<CollData> List;
	//�����蔻�茋��
	MV1_COLL_RESULT_POLY_DIM res;
	//�����蔻�茋�ʊi�[
	res = MV1CollCheck_Sphere(hndl, -1, pos, rad);

	//�q�b�g���Ă���Ȃ�
	if (res.HitNum > 0) {
		for (int pol_index = 0; pol_index < res.HitNum; pol_index++) {
			//���������̖@�������邩�t���O
			bool check = true;

			distance = VSub(res.Dim[pol_index].HitPosition, pos);
			length = distance.Long();
			//�߂荞�݋������v�Z
			length = rad - length;
			//���������|���S���̖@���̌����ɂ߂荞�񂾒�����������
			distance = VScale(res.Dim[pol_index].Normal, length);
			data._Normal = res.Dim[pol_index].Normal;
			data._Distance = distance;

			//�@�������������Ȃ烊�X�g�Ɋi�[���Ȃ�
			if (pol_index == 0) {
				List.emplace_back(data);
			}
			else {
				for (auto itr = List.begin(); itr != List.end(); ++itr) {
					if (MyLib::Abs(itr->_Normal._X - res.Dim[pol_index].Normal.x) <= NORMAL_ERROR &&
						MyLib::Abs(itr->_Normal._Y - res.Dim[pol_index].Normal.y) <= NORMAL_ERROR &&
						MyLib::Abs(itr->_Normal._Z - res.Dim[pol_index].Normal.z) <= NORMAL_ERROR) {
						check = false;
						if (itr->_Distance.Long() < distance.Long())
							itr->_Distance = distance;
						break;
					}
				}
				if (check == true) {
					List.emplace_back(data);
				}
			}
		}

		//���X�g�Ɋi�[���Ă���x�N�g�������v����
		for (auto itr = List.begin(); itr != List.end(); ++itr) {
			pushVec += itr->_Distance;
		}
	}

	//�R���W�����f�[�^�j��
	MV1CollResultPolyDimTerminate(res);

	List.clear();

	//���v�����x�N�g�������Z���Ԃ�
	return (pos + pushVec);
}

//�J�������߂荞�܂Ȃ��悤�ɂ���
void CCOllisionManager::HitCheckCamera(const int hndl) {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	MV1_COLL_RESULT_POLY res;
	//�����蔻�茋�ʊi�[
	if (cPlayer->GetState() == CPlayer::ePlayerState::TELEPORT) {
		res = MV1CollCheck_Line(hndl, -1, cPlayer->GetTeleportPos(), cPlayerCamera->GetcameraPos());
	}
	else
		res = MV1CollCheck_Line(hndl, -1, cPlayer->GetPos(), cPlayerCamera->GetcameraPos());

	//�߂荞��ł���Ȃ牟���o��
	if (res.HitFlag != 0) {
		cPlayerCamera->SetCameraPos(res.HitPosition);
	}
}
