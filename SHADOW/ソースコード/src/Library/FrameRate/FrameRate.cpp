#include "FrameRate.h"
#include "../Color.h"

//�ϐ��̏�����
int CFrameRate::_CurrentTime = 0;				//���݂̎���
int CFrameRate::_LastFrameTime = 0;				//�O��̃t���[�����s���̎���
int CFrameRate::_FrameCnt = 0;					//�t���[���J�E���g�p
int CFrameRate::_UpdateFrameRateTime = 0;		//�t���[�����[�g���X�V��������
float CFrameRate::_FrameRate = 0.0f;			//�t���[�����[�g�i�\���p�j

//�t���[�����[�g�̖��O���
namespace FrameRate
{
	constexpr float		GAME_FRAME_RATE			= 60.0f;					//�Q�[���̃t���[�����[�g
	constexpr float		ONE_SECOND_MILI_TIME	= 1000.0f;					//1�b(�~���b)
	constexpr float		FRAME_TIME				= ONE_SECOND_MILI_TIME / GAME_FRAME_RATE;				//1�t���[���̎���
	constexpr VECTOR	DRAW_FRAMERATE_POSITION	= { 10.0f, 10.0f, 0.0f };	//�t���[�����[�g�̕`��ʒu
	constexpr int		DRAW_FRAMERATE_COLOR	= 0x000000;					//�t���[�����[�g�̕`��F(��)
}
//���O��ԏȗ�
using namespace FrameRate;

CFrameRate::CFrameRate()
{
	_CurrentTime = 0;
	_LastFrameTime = 0;
	_FrameCnt = 0;
	_UpdateFrameRateTime = 0;
	_FrameRate = 0.0f;
}

CFrameRate::~CFrameRate()
{
}

//������
void CFrameRate::Init()
{
	_CurrentTime = 0;
	_LastFrameTime = 0;
	_FrameCnt = 0;
	_UpdateFrameRateTime = 0;
	_FrameRate = 0.0f;
}

//�ʏ�
void CFrameRate::Step()
{
	//���݂̎������擾
	_CurrentTime = GetNowCount();

	//�ŏ��̃��[�v�Ȃ�
	//���݂̎��Ԃ��AFPS�̌v�Z���������Ԃɐݒ�
	if (_UpdateFrameRateTime == 0.0f)
	{
		_UpdateFrameRateTime = _CurrentTime;
		_FrameRate = GAME_FRAME_RATE;
	}
}

//�X�V
void CFrameRate::Update()
{
	//�t���[�����s���̎��Ԃ��X�V
	_LastFrameTime = _CurrentTime;

	//�t���[�������J�E���g
	_FrameCnt++;

	//�t���[�����[�g�̌v�Z
	CalcFrameRate();
}

//�`��
void CFrameRate::Draw()
{
	DrawFrameRate();
}

//���s�\�����ׂ�
bool CFrameRate::IsExecutable()
{
	// ���݂̎������A�O��̃t���[�������
	// 1/60�b�o�߂��Ă����珈�������s����
	if (_CurrentTime - _LastFrameTime >= (int)FRAME_TIME) {
		return true;
	}
	else
	return false;
}


//�t���[�����[�g�̌v�Z
void CFrameRate::CalcFrameRate()
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int nDifTime = _CurrentTime - _UpdateFrameRateTime;

	//�O��̃t���[�����[�g�X�V����
	//�P�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if (nDifTime > ONE_SECOND_MILI_TIME)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		float fFrameCnt = ((float)_FrameCnt * ONE_SECOND_MILI_TIME);

		//�t���[�����[�g�����߂�
		//���z�ǂ���Ȃ� 60000 / 1000 �� 60 �ƂȂ�
		_FrameRate = fFrameCnt / nDifTime;

		//�t���[���J�E���g���N���A
		_FrameCnt = 0;

		//�t���[�����[�g�X�V���Ԃ��X�V
		_UpdateFrameRateTime = _CurrentTime;
	}
}

//�t���[�����[�g�̕`��
void CFrameRate::DrawFrameRate()
{
	DrawFormatString(static_cast<int>(DRAW_FRAMERATE_POSITION.x), static_cast<int>(DRAW_FRAMERATE_POSITION.y),
		COLOR::RED, "FPS[%.2f]", _FrameRate);
}
