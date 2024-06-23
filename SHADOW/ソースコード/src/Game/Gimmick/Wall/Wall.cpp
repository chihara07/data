#include "Wall.h"
#include "../../Library/Collision/Collision.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"
#include "../../Library/Math/Math.h"
#include "../../Player/Player.h"
#include "../../Game/Camera/Camera.h"
#include "../../Game/Hndl/HndlManager.h"

//�R���X�g���N�^�E�f�X�g���N�^
CWall::CWall() {
	_Hndl = -1;
}
CWall::~CWall() {
	Fin();
}

//������
void CWall::Init() {
	_Pos = Vector3D::ZeroVec();
	_Rot = Vector3D::ZeroVec();
	_Scale = Vector3D::ZeroVec();
	_Hndl = -1;
}

//���[�h
void CWall::Load() {
	if (_Hndl == -1) { _Hndl = MV1DuplicateModel(CHndlManager::GetInstance()->GetModelHndl(MODEL_PATH_TYPE::WALL)); }
}

//�Z�b�g
void CWall::Set() {
	//�g�嗦�Z�b�g�A��]�p�x�A���W�Z�b�g
	MV1SetScale(_Hndl, _Scale);
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);

	// �����蔻��p���f���̃|���S�������Z�b�g�A�b�v
	MV1SetupReferenceMesh(_Hndl, -1, TRUE);

	//�R���W�������\�z
	MV1SetupCollInfo(_Hndl);
}

//���C������
void CWall::Step() {
	//�v���C���[�擾
	CPlayer* cPlayer = CPlayer::GetInstance();
	//�v���C���[�J�����擾
	CPlayerCamera* cPlayerCamera = CPlayerCamera::GetInstance();

	// �|���S�������擾
	MV1_REF_POLYGONLIST polygons = MV1GetReferenceMesh(_Hndl, -1, TRUE);
	Vector3D playerPos = cPlayer->GetPos();
	float playerRad = cPlayer->GetRad();
	float playerRotY = 0;
	float cameraRotY = 0;

	// �|���S���̐������J��Ԃ�
	for (int i = 0; i < polygons.PolygonNum; i++) {
		// �|���S�������擾����
		MV1_REF_POLYGON polygon = polygons.Polygons[i];
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
			if (CCollision::IsHitTriangleXZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕��������珰�̍������v�Z
				float floor_height = GetTriangleHeightXZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̑����̍��W���v�Z
				float player_bottom = playerPos._Y - playerRad;
				// �����瑫���܂ł̋������v�Z
				float dist = player_bottom - floor_height;
				// �����̕����Ⴂ ���� �����Ə��Ƃ̋��������ꂷ���Ă��Ȃ���Ή����グ��
				if (dist < 0.0f && MyLib::Abs(dist) <= playerRad) {
				}
			}
		}
		else if (norm._Y <= MAP_CEIL_NORM_Y) {
			// �V��̏ꍇ
			// �O�p�`�̓����蔻��
			if (CCollision::IsHitTriangleXZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
				// �ʂ̕���������V��̍������v�Z
				float ceil_height = GetTriangleHeightXZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
				// �v���C���[�̔]�V�̍��W���v�Z
				float player_top = playerPos._Y + playerRad;
				// �V�䂩��]�V�܂ł̋������v�Z
				float dist = player_top - ceil_height;
				// �]�V�̕������� ���� �]�V�ƓV��Ƃ̋��������ꂷ���Ă��Ȃ���Ή���������
				if (dist > 0.0f && MyLib::Abs(dist) <= playerRad) {

				}
			}
		}
		else {
			// �����łȂ���Ε�
			if (MyLib::Abs(norm._Z) >= MAP_WALL_NORM_Z_MIN) {
				// XY���ʂ̕�
				if (CCollision::IsHitTriangleXY(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = GetTriangleHeightXY(playerPos, vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm._Z < 0.0f ? playerPos._Z + playerRad : playerPos._Z - playerRad;
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (MyLib::Abs(dist) <= playerRad) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm._Z <= 0.0f && dist >= 0.0f)) {
							//�ǂɐG��Ă���Ȃ�v���C���[�̕ǂ̂ڂ�t���O�I���A
							//�ڐG�t���O�I���A�v���C���[Y����]�p�x�A�J����Y����]�p�x���
							cPlayer->SetClimb(true);
							playerRotY = MyLib::STRAIGHT_ANGLE;
							cameraRotY = MyLib::STRAIGHT_ANGLE;
						}
						else if ((norm._Z >= 0.0f && dist <= 0.0f)) {
							//�ǂɐG��Ă���Ȃ�v���C���[�̕ǂ̂ڂ�t���O�I���A
							//�ڐG�t���O�I���A�v���C���[Y����]�p�x�A�J����Y����]�p�x���
							cPlayer->SetClimb(true);
							playerRotY = 0.f;
							cameraRotY = 0.f;
						}
					}
				}
			}
			else {
				// YZ���ʂ̕�
				if (CCollision::IsHitTriangleYZ(playerPos, vertexs[0], vertexs[1], vertexs[2])) {
					// ���ʏ�̕ǂ̍������Z�o
					float wall_height = GetTriangleHeightYZ(playerPos, vertexs[0], vertexs[1], vertexs[2]);
					// �Փ˓_�܂ł̋������Z�o
					float player_front = norm._X < 0.0f ? playerPos._X + playerRad : playerPos._X - playerRad;
					float dist = player_front - wall_height;
					// �ǂ��痣�ꂷ���Ă��Ȃ����`�F�b�N
					if (MyLib::Abs(dist) <= playerRad) {
						// �@���̌����ɋC��t���Ă߂荞��ł��邩�`�F�b�N����
						if ((norm._X <= 0.0f && dist >= 0.0f)) {
							//�ǂɐG��Ă���Ȃ�v���C���[�̕ǂ̂ڂ�t���O�I���A
							//�ڐG�t���O�I���A�v���C���[Y����]�p�x�A�J����Y����]�p�x���
							cPlayer->SetClimb(true);
							playerRotY = -MyLib::RIGHT_ANGLE;
							cameraRotY = -MyLib::RIGHT_ANGLE;
						}
						else if ((norm._X >= 0.0f && dist <= 0.0f)) {
							//�ǂɐG��Ă���Ȃ�v���C���[�̕ǂ̂ڂ�t���O�I���A
							//�ڐG�t���O�I���A�v���C���[Y����]�p�x�A�J����Y����]�p�x���
							cPlayer->SetClimb(true);
							playerRotY = MyLib::RIGHT_ANGLE;
							cameraRotY = MyLib::RIGHT_ANGLE;
						}
					}
				}
			}
		}
	}
	//�v���C���[���ǂ̂ڂ��Ԃŕǂ̂ڂ�t���O�I���Ȃ�
	if (cPlayer->GetState() == CPlayer::ePlayerState::CLIMB
		&& cPlayer->GetClimb() == true) {
		//��]�p�x�Z�b�g
		cPlayer->SetRotX(MyLib::RIGHT_ANGLE);
		cPlayer->SetRotY(playerRotY);
		cPlayerCamera->SetRotY(cameraRotY);
	}
}

//�`��
void CWall::Draw() {
	//�v���C���[���擾
	CPlayer* cPlayer = CPlayer::GetInstance();

	MV1DrawModel(_Hndl);
}

//�X�V����
void CWall::Update() {
	MV1SetRotationXYZ(_Hndl, _Rot);
	MV1SetPosition(_Hndl, _Pos);
	// �|���S�������X�V����
	MV1RefreshReferenceMesh(_Hndl, -1, TRUE);
}

//�I��
void CWall::Fin() {
	//�R���W�������j��
	MV1TerminateCollInfo(_Hndl);

	if (_Hndl != -1) { MV1DeleteModel(_Hndl); _Hndl = -1; }
}

//�q�b�g�֐�
void CWall::HitCalc() {
}
