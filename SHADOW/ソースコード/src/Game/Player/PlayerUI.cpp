#include "PlayerUI.h"
#include "Player.h"
#include "PlayerAttack.h"
#include "PlayerParameter.h"
#include "../../Game/Draw/DrawManager.h"
#include "../../Library/Common.h"
#include "../../Library/Color.h"

constexpr int AREA_GRAPH_POS_X = 350;					//�e�G���A�摜X���W
constexpr int AREA_GRAPH_POS_Y = 520;					//�e�G���A�摜Y���W
constexpr int AREA_GRAPH_DISTANCE = 50;					//�e�G���A�摜����
constexpr int AREA_GAUGE_TOP_LEFT_X = 320;				//�e�G���A�Q�[�W����X���W
constexpr int AREA_GAUGE_TOP_LEFT_Y = 560;				//�e�G���A�Q�[�W����Y���W
constexpr int AREA_GAUGE_BOTTOM_RIGHT_Y = 590;			//�e�G���A�Q�[�W�E��Y���W
constexpr int AREA_GAUGE_MAX_LENGTH = 160;				//�e�G���A�Q�[�W�ő咷��

using namespace PLAYER;

//�R���X�g���N�^�E�f�X�g���N�^
CPlayerUI::CPlayerUI() {

}
CPlayerUI::~CPlayerUI() {

}

//�`��
void CPlayerUI::Draw() {
	CPlayer* cPlayer = CPlayer::GetInstance();
	CPlayerAttack* cPlayerAttack =  CPlayerAttack::GetInstance();

	//CDrawManager::GetInstance()->Draw(PATH_TYPE::PLAYER_LIFE,LIFE_GRAPH_POS._X, LIFE_GRAPH_POS._Y, 1.f, 0.f);
	//DrawFormatStringF(LIFE_TEXT_POS._X, LIFE_TEXT_POS._Y, COLOR::WHITE, "�~%d", _Life);
	CDrawManager::GetInstance()->Draw(PATH_TYPE::PLAYER_HAVECOIN, COIN_GRAPH_POS._X, COIN_GRAPH_POS._Y, 1.f, 0.f);
	DrawFormatStringF(COIN_TEXT_POS._X, COIN_TEXT_POS._Y, COLOR::WHITE, "�~%d", cPlayer->GetCoin());

	for (int area_index = 0; area_index < AREA_NUM; area_index++) {
		if (cPlayerAttack->GetAreaActive(area_index) == true) {
			CDrawManager::GetInstance()->Draw(PATH_TYPE::AREAENERGY2, AREA_GRAPH_POS_X + (AREA_GRAPH_DISTANCE * area_index), AREA_GRAPH_POS_Y, 1.f, 0.f);
		}
		else {
			CDrawManager::GetInstance()->Draw(PATH_TYPE::AREAENERGY1, AREA_GRAPH_POS_X + (AREA_GRAPH_DISTANCE * area_index), AREA_GRAPH_POS_Y, 1.f, 0.f);
		}
	}

	int energyEnd = (int)(AREA_GAUGE_TOP_LEFT_X + (cPlayerAttack->GetEnergyCnt() / AREA_ENERGY_MAX) * AREA_GAUGE_MAX_LENGTH);
	int energyStart = (int)(energyEnd - (cPlayerAttack->GetEnergy() * cPlayerAttack->GetHoldCnt() / AREA_ENERGY_MAX * AREA_GAUGE_MAX_LENGTH));

	CDrawManager::GetInstance()->Draw(PATH_TYPE::ENERGY, AREA_GAUGE_TOP_LEFT_X, AREA_GAUGE_TOP_LEFT_Y, energyEnd, AREA_GAUGE_BOTTOM_RIGHT_Y);
	if (cPlayerAttack->GetHold() == true && (cPlayerAttack->GetAreaActive(0) == false || cPlayerAttack->GetAreaActive(1) == false || cPlayerAttack->GetAreaActive(2) == false)) {
		if (cPlayerAttack->GetEnergy() * cPlayerAttack->GetHoldCnt() > cPlayerAttack->GetEnergyCnt())
			CDrawManager::GetInstance()->Draw(PATH_TYPE::CONSUMPTION, AREA_GAUGE_TOP_LEFT_X, AREA_GAUGE_TOP_LEFT_Y, energyEnd, AREA_GAUGE_BOTTOM_RIGHT_Y);
		else
			CDrawManager::GetInstance()->Draw(PATH_TYPE::CONSUMPTION, energyStart, AREA_GAUGE_TOP_LEFT_Y, energyEnd, AREA_GAUGE_BOTTOM_RIGHT_Y);
	}
}