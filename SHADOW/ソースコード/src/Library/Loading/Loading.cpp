#include "Loading.h"
#include "../../Game/Hndl/HndlManager.h"

//�ϐ��̏�����
Vector2D CLoading::_Pos(0.f);					//�摜���W
int CLoading::_Hndl[LOAD_HNDL_NUM] = { -1 };	//�摜�n���h��
int CLoading::_Cnt = 0;							//���[�h��ʃJ�E���g
int CLoading::_AnimCnt = 0;						//�A�j���[�V�����J�E���g
int CLoading::_HndlID = 0;						//�摜ID
bool CLoading::_IsLoading = false;				//���[�h���Ă��邩�t���O
bool CLoading::_IsLoad = false;					//���[�h�������t���O

constexpr int LOAD_LOWEST_TIME = 90;			//���[�h��ʕ`��Œ᎞��
//���[�h���
constexpr char BG_LOADING[] = "data/Image/load.png";
//���[�h��ʉ摜�p�X
static constexpr char LOADING_PATH[LOAD_HNDL_NUM][128] = {
	"data/Image/loading1.png",
	"data/Image/loading2.png",
	"data/Image/loading3.png",
	"data/Image/loading4.png",
	"data/Image/loading5.png",
	"data/Image/loading6.png",
	"data/Image/loading7.png",
	"data/Image/loading8.png",
	"data/Image/loading9.png",
	"data/Image/loading10.png",
	"data/Image/loading11.png",
	"data/Image/loading12.png",
};

//�R���X�g���N�^�E�f�X�g���N�^
CLoading::CLoading() {
	_Pos(0.f);
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		_Hndl[hndl_index] = -1;
	}
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = false;
	_IsLoad = false;
}
CLoading::~CLoading() {
	
}

//������
void CLoading::Init() {
	_Pos(0.f);
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		_Hndl[hndl_index] = -1;
	}
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = true;
	_IsLoad = false;
	//�O�̂��ߔ񓯊��ǂݍ��݃t���O�I�t
	SetUseASyncLoadFlag(FALSE);
}

//�ǂݍ���(�ق��̓ǂݍ��݂͂���̌�ɍs��)
void CLoading::Load() {
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		if (_Hndl[hndl_index] == -1) _Hndl[hndl_index] = LoadGraph(LOADING_PATH[hndl_index]);
	}
}

//���[�h�J�n
void CLoading::LoadStart() {
	_Cnt = 0;
	_AnimCnt = 0;
	_HndlID = 0;
	_IsLoading = true;
	_IsLoad = false;

	//�񓯊��ǂݍ��݃t���O�I��
	SetUseASyncLoadFlag(TRUE);
}

//�`��
void CLoading::Draw() {
	DrawGraphF(_Pos._X, _Pos._Y, _Hndl[_HndlID % LOAD_HNDL_NUM], TRUE);
}

//���C������
void CLoading::Step() {
	//�ŒჍ�[�h���Ԃ܂ŃJ�E���g����
	if(_Cnt < LOAD_LOWEST_TIME) _Cnt++;

	//�A�j���[�V�������Ԃ𒴂����玟�̉摜��
	if (_AnimCnt >= LOAD_ANIM_MAX_CNT) {
		_AnimCnt = 0;
		_HndlID++;
	}
	//�A�j���[�V�������Ԃ��J�E���g����
	_AnimCnt++;
}

//�I��
void CLoading::Fin() {
	for (int hndl_index = 0; hndl_index < LOAD_HNDL_NUM; hndl_index++) {
		if (_Hndl[hndl_index] != -1) _Hndl[hndl_index] = -1;
	}
}

//���[�h�I��
void CLoading::LoadEnd() {
	SetLoading(false);
	SetLoad(false);
	//�O�̂��ߔ񓯊��ǂݍ��݃t���O�I�t
	SetUseASyncLoadFlag(FALSE);
}

//���[�h��ʂ��I���ł��邩
bool CLoading::IsLoadEnd() {
	//�ǂݍ��݂��I�����Ă��邩�ŒჍ�[�h���Ԃ𒴂��Ă���Ȃ烍�[�h�I��
	if (GetASyncLoadNum() == 0 && _Cnt >= LOAD_LOWEST_TIME)
		return true;

	return false;
}

//���[�h���Ă��邩�t���O�擾
bool CLoading::GetLoading() { return _IsLoading; }

//���[�h���Ă��邩�t���O�Z�b�g
void CLoading::SetLoading(bool f) { _IsLoading = f; }

//���[�h�������t���O�擾
bool CLoading::GetLoad() { return _IsLoad; }

//���[�h�������t���O�Z�b�g
void CLoading::SetLoad(bool f) { _IsLoad = f; }

//�J�E���g���Z�b�g
void CLoading::Reset() { _Cnt = 0; }
