#pragma once

#include "../Enemy/EnemyManager.h"
#include "../Gimmick/Teleport/Teleport.h"
#include "../Gimmick/Switch/Switch.h"
#include "../Gimmick/Trap/Trap.h"
#include "../Gimmick/GimmickManager.h"
#include "../../Library/Vector/Vector3D.h"
#include "../Camera/Camera.h"
#include <list>

using std::list;

//�����蔻��}�l�[�W���[�N���X
class CCOllisionManager {
public:
	//�v���C���[�ƓG�̓����蔻��
	static void CheckHitPlayerToEnemy(CEnemyObj* cEnemy);
	//�v���C���[�ƃt���b�V���U���̓����蔻��
	static void CheckHitPlayerToFlash(CEnemyObj* cEnemy);
	//�v���C���[�ƓG�̒e�̓����蔻��
	static void CheckHitPlayerToEnemyBullet(CEnemyObj* cEnemy);
	//�v���C���[�̍U���ƓG�̓����蔻��
	static void CheckHitPlayerAttackToEnemy(CEnemyObj* cEnemy);
	//�v���C���[�Ɖe�G���A����
	static void CheckHitPlayerToArea();
	//�G�̍U���Ɖe�G���A����
	static void CheckHitFlashToArea(CEnemyObj* cEnemy);
	/// <summary>
	/// �v���C���[�ƓG�̃R�C�������蔻��
	/// </summary>
	/// <param name="coin_pos">�R�C�����W</param>
	/// <param name="coin_rad">�R�C�����a</param>
	/// <param name="coin_active">�R�C�������t���O</param>
	/// <returns></returns>
	static bool CheckHitPlayerToCoin(Vector3D coin_pos,float coin_rad, bool coin_active);
	//�v���C���[�Ɖe�̓����蔻��
	static void CheckHitPlayerToShadow(CGimmickObj* cGimmick);
	//�v���C���[�ƃg���b�v�̓����蔻��
	static void CheckHitPlayerToTrap(CGimmickObj* cGimmick);
	//�v���C���[�ƃX�C�b�`�̓����蔻��
	static void CheckHitPlayerToSwitch(CSwitch* cSwitch);

	/// <summary>
	/// �v���C���[�ƃ}�b�v�����蔻��
	/// </summary>
	/// <param name="pos">�Ώۂ̍��W</param>
	/// <param name="rad">�Ώۂ̔��a</param>
	/// <param name="hndl">�}�b�v�n���h��</param>
	/// <returns>true : �n�ʂɐG��Ă���</returns>
	static bool CheckCollision(Vector3D pos, float rad, const int hndl);
	
	/// <summary>
	/// ���f���Ƃ̓����蔻��
	/// </summary>
	/// <param name="pos">�Ώۂ̍��W</param>
	/// <param name="rad">�Ώۂ̔��a</param>
	/// <param name="hndl">�}�b�v�n���h��</param>
	/// <returns>�����o����̍��W</returns>
	static Vector3D HitCheck(Vector3D pos, float rad, const int hndl);
	//�J�������߂荞�܂Ȃ��悤�ɂ���
	static void HitCheckCamera(const int hndl);

	//�����蔻��f�[�^
	struct CollData{
		Vector3D _Normal;
		
		Vector3D _Distance;
	};
};
