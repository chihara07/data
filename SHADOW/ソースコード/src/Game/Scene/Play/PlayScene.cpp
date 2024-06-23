#include "PlayScene.h"
#include "../../Library/Input/Input.h"
#include "../SceneManager.h"
#include "../../CollisionManager/CollisionManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Common.h"
#include "../../Library/Effect/effekseer.h"
#include "../../Library/Loading/Loading.h"

constexpr int EFFECT_NUM = 20;		//�G�t�F�N�g����
constexpr int PARTICLE_NUM = 2000;	//�p�[�e�B�N������

//�R���X�g���N�^
CPlayScene::CPlayScene()
{
	_SceneID = eKind::SCENE_INIT;
}

//�f�X�g���N�^
CPlayScene::~CPlayScene()
{
	//�e�}�l�[�W���[�폜
	cPlayerManager.Delete();
	cCoinManager->DeleteInstance();
	cEnemyManager->DeleteInstance();
	cTutorial->DeleteInstance();
	cPlayerCamera->DeleteInstance();
	CEffekseerCtrl::Fin();
}

//�J��Ԃ��s������
int CPlayScene::Loop()
{
	int iRet = 0;
	
	//�V�[���؂�ւ��֐��|�C���^���s
	(this->*SceneSwitchFunc[static_cast<int>(_SceneID)])();

	//�v���C���[������ł���΃Q�[���I�[�o�[��
	if (_IsEnd == true && player_active == false){ 
		iRet = (int)CSceneManager::eScene::GAME_OVER;
		cPlayer->DeleteInstance();
	}
	//�N���A���Ă���Ȃ玟�̃X�e�[�W�܂��̓N���A��
	else if (_IsEnd == true) {
		if (StageID != eStageID::STAGE_4) {
			iRet = (int)CSceneManager::eScene::PLAY;
			StageID = static_cast<eStageID>(static_cast<int>(StageID) + 1);
		}
		else
			iRet = (int)CSceneManager::eScene::GAME_CLEAR;
	}
		
	player_active = false;

	return iRet;
}

//�`�揈��
void CPlayScene::Draw()
{
	if (_SceneID == eKind::SCENE_LOOP) {
		cBg.Draw();
		cCoinManager->Draw();
		cGimmickManager.Draw();
		cEnemyManager->Draw();
		cPlayerManager.Draw();
		cTutorial->Draw();
	}
}

//������
void CPlayScene::Init()
{
	cPlayerManager.Init();
	cPlayerCamera->Init();
	cPlayerCamera->SetNearFarPars();
	cEnemyManager->Init();
	cGimmickManager.Init();
	cTutorial->Init();
	cBg.Init();
	CEffekseerCtrl::Init(EFFECT_NUM, PARTICLE_NUM);
	CEffekseerCtrl::SetProjectionMtx(CAMERA_PARS, ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), CAMERA_NEAR, CAMERA_FAR);
	CLoading::LoadStart();

	_SceneID = eKind::SCENE_LOAD;

	_IsEnd = false;
}

//���[�h����
void CPlayScene::Load()
{
	//���[�h���̓��[�h��ʂɂ���
	if (CLoading::GetLoading() == true && CLoading::GetLoad() == false) {
		CLoading::SetLoad(true);
		cPlayerManager.Load();
		cEnemyManager->DataSet();
		cEnemyManager->Load();
		cCoinManager->Init();
		cCoinManager->Load();
		cGimmickManager.DataSet();
		cGimmickManager.Load();
		cBg.Load();
		CEffekseerCtrl::LoadData();
	}
	//���[�h�I������玟��
	if (CLoading::IsLoadEnd() == true) {
		cPlayerManager.Set();
		cEnemyManager->Set();
		cCoinManager->Set();
		cGimmickManager.Set();
		cBg.Set();
		CLoading::LoadEnd();
		CSoundManager::Play(CSoundManager::eSoundID::BGM, DX_PLAYTYPE_LOOP, true);
		CSoundManager::SetVolume(CSoundManager::eSoundID::BGM, BGM_VOLUME);

		_SceneID = eKind::SCENE_LOOP;
	}
}

//���t���[���Ăԏ���
void CPlayScene::Step()
{
	cTutorial->Step();

	if (cTutorial->GetTutorial() == false) {
		cEnemyManager->Step();
		cPlayerManager.Step();
		cBg.Step();
		cGimmickManager.Step();
		cCoinManager->Step();

		//�e�����蔻�菈��
		cPlayerManager.Collision(cBg.GetHndl());
		cGimmickManager.Collision();
		cEnemyManager->Collision(cBg.GetHndl());
		cCoinManager->Collision();

		//�J��������
		cPlayerCamera->Step();
		CCOllisionManager::HitCheckCamera(cBg.GetHndl());

		//�e�A�b�v�f�[�g����
		cPlayerCamera->Update();
		cPlayerManager.Update();
		cEnemyManager->Update();
		cGimmickManager.Update();
		cBg.Update();
		cCoinManager->Update();
		CEffekseerCtrl::SetCameraMtx(cPlayerCamera->GetcameraPos(), cPlayerCamera->GetTargetPos(), cPlayerCamera->GetCameraUp());
		CEffekseerCtrl::Update();

		//�N���A�܂��̓v���C���[���S�Ŏ���
		if (cPlayer->GetClear() == true || cPlayer->GetActive() == false)
			_SceneID = eKind::SCENE_EXIT;
	}
}

//�I������
void CPlayScene::Fin()
{
	CLoading::SetLoading(true);
	CLoading::Reset();
	_IsEnd = true;

	player_active = cPlayer->GetActive();

	cEnemyManager->Fin();
	cGimmickManager.Fin();
	cBg.Fin();
	cPlayerManager.Fin();
	cCoinManager->Fin();
	CEffekseerCtrl::Fin();

	CSoundManager::Stop(CSoundManager::eSoundID::BGM);

	_SceneID = eKind::SCENE_INIT;
}
