#pragma once

//			Effekseer�g�p�N���X
// �g�p���̓v���p�e�B�́uC/C++�v���u�S�ʁv���u�ǉ��̃C���N���[�h�f�B���N�g���v�ɁuEffekseer�v���́uinclude�v
// �u�����J�[�v���u�S�ʁv���u�ǉ��̃��C�u�����f�B���N�g���v�ɁuEffekseer�v
// ��ǉ����Ă��������B
// CEffekseer�N���X��static�Ȃ̂Ŏg�p���鎞�����v���W�F�N�g�ɒǉ����Ă��������B
// �܂��A�f�o�b�O�ł͌x�����o��̂Łu�����J�[�v���u�R�}���h���C���v���u�ǉ��̃I�v�V�����v��
// �u/ignore:4099 �v�ƋL�q���Ă��������B

//			�g�p���̒��ӎ���
// CEffekseerCtrl::Draw()�O�ɉ�������DxLib��2D�`��֐�(����������)���Ă΂�ĂȂ���
// �`�悳��Ȃ��\��������܂��B
// �܂��A3D�̓���or�������̕��̂̌��ɃG�t�F�N�g���o���Ă��܂��Ƃ������Ȍ����ڂɂȂ邱�Ƃ�����܂��B

// ���݂�VisualStudio2019��2022�ɂ̂ݑΉ����Ă��܂��B

#include <DxLib.h>
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerRendererDX11.h>
#include <vector>


class CEffekseer;


//		�G�t�F�N�g�Ǘ��N���X
//		�������g����
class CEffekseerCtrl {
public:
	enum class eEffectID {
		CHANGE,			//CHANGE
		DEATH,			//DEATH

		NUM,
	};
	static int _ID[(int)eEffectID::NUM];
protected:
	static CEffekseer*							_Eff;			// �G�t�F�N�g�P�i�Ǘ��N���X
	static std::vector<::Effekseer::EffectRef>	_Effect;		// �G�t�F�N�g�N���X
	static ::Effekseer::ManagerRef				_Manager;		// �G�t�F�N�g�}�l�[�W��
	static ::EffekseerRendererDX9::RendererRef	_Renderer9;	// �����_���[(DirectX9�p)
	static ::EffekseerRendererDX11::RendererRef	_Renderer11;	// �����_���[(DirectX11�p)
	static int									_AllNum;		// �g�p�G�t�F�N�g����
	static int									_UseID;		// ���Ɏg�p�\���ID
	static int									_DxVersion;	// DirectX�̃o�[�W����
public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CEffekseerCtrl();
	~CEffekseerCtrl();

	//	������
	//	eff_num		:	�G�t�F�N�g����
	//	particle_num	:	�p�[�e�B�N������
	static void Init(int eff_num, int particle_num);
	//	�I������
	static void Fin(void);

	//	�G�t�F�N�g�f�[�^���[�h
	static void	LoadData();
	//	���e�s��ݒ�
	//	pers		:	�J�����̃p�[�X
	//	aspect		:	�A�X�y�N�g��
	//	near_length	:	�J�����̃j�A�[
	//	far_length	:	�J�����̃t�@�[
	//	@memo		:	�ݒ肪�ς�邽�тɌĂ�ł�������
	static void SetProjectionMtx(float pers, float aspect, float near_length, float far_length);
	//	���e�s�񎩓��ݒ�
	//	@memo	:	DxLib�̊֐��Ŏ����ݒ�(�Ȃ�ׂ��g��Ȃ�)
	//				��ʕ����Ȃǂɂ͑Ή��s��
	static void SetAutoProjectionMtx(void);
	//	�J�����s��ݒ�
	//	eye_pos		:	�J�����̎��_	
	//	focus_pos	:	�J�����̒����_
	//	up			:	�J�����̏����
	//	@memo		:	�ݒ肪�ς�邽�тɌĂ�ł�������
	static void SetCameraMtx(VECTOR eye_pos, VECTOR focus_pos, VECTOR up);
	//	�J�����s�񎩓��ݒ�
	//	@memo	:	DxLib�̊֐��Ŏ����ݒ�(�Ȃ�ׂ��g��Ȃ�)
	static void SetAutoCameraMtx();
	//	�J�����s��ݒ�
	//	eye_pos		:	�J�����̎��_	
	//	rot			:	�J�����̊p�x
	//	up			:	�J�����̏����
	//	@memo		:	�ݒ肪�ς�邽�тɌĂ�ł�������
	static void SetCameraRotMtx(VECTOR eye_pos, VECTOR rot, VECTOR up);
	//	�X�V����
	static void Update(void);
	//	�X�V����
	//	@memo	: �J�����ݒ������(�Ȃ�ׂ��g��Ȃ�)
	//			  ProjectionMtx,CameraMtx�̐ݒ���s�v
	static void UpdateAutoCamera(void);
	//	�`�揈��
	static void Draw(void);


	//	�G�t�F�N�g�Ăяo��
	//	id		:	�G�t�F�N�gID
	//	pos		:	�����ʒu
	//	f	:	�G�t�F�N�g�����[�v���邩
	static int Request(int id, VECTOR pos, bool f);
	//	�w��G�t�F�N�g��~
	static void Stop(int hndl);
	//	�S�G�t�F�N�g��~
	static void StopAll(void);

	//	���W�ύX
	static void SetPosition(int hndl, VECTOR pos);
	//	�g��k�����ύX
	static void SetScale(int hndl, VECTOR scale);
	//	��]�p�x�ύX
	static void SetRot(int hndl, VECTOR rot);
	//	�G�t�F�N�g�A�N�e�B�u����
	static bool IsActive(int hndl);

private:
	//	�f�o�C�X���X�g���̃R�[���o�b�N�֐�
	static void DeviceLostFunction(void* data);
	//	�f�o�C�X���A���̃R�[���o�b�N�֐�
	static void DeviceRestoreFunction(void* data);
};



//		�G�t�F�N�g�P�i�Ǘ��N���X
//		������͊�{�g��Ȃ�
class CEffekseer {
protected:
	VECTOR				_Pos;			// �G�t�F�N�g�̍Đ��ʒu
	VECTOR				_Scale;			// �G�t�F�N�g�̔{��
	VECTOR				_Rot;			// �G�t�F�N�g�̉�]
	int					_Hndl;			// �G�t�F�N�g�n���h��
	int					_ID;			// �Đ����̃G�t�F�N�gID
	bool				_IsLoop;		// ���[�v�t���O

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CEffekseer();
	~CEffekseer();

	void Reset(void);

	//	���W�ݒ�
	inline void	SetTrans(VECTOR pos) { _Pos = pos; }
	//	���W�擾
	inline VECTOR	GetTrans(void) { return _Pos; }
	//	�g��k�����ݒ�
	inline void	SetScale(VECTOR scale) { _Scale = scale; }
	//	�g��k�����擾
	inline VECTOR	GetScale(void) { return _Scale; }
	//	�p�x�ݒ�
	inline void	SetRot(VECTOR rot) { _Rot = rot; }
	//	�p�x�擾
	inline VECTOR	GetRot(void) { return _Rot; }
	//	�G�t�F�N�g�n���h���ݒ�
	inline void	SetHndl(int hndl) { _Hndl = hndl; }
	//	�G�t�F�N�g�n���h���擾
	inline int	GetHndl(void) { return _Hndl; }
	//	�G�t�F�N�gID�ݒ�
	inline void	SetID(int id) { _ID = id; }
	//	�G�t�F�N�gID�擾
	inline int	GetID(void) { return _ID; }
	//	���[�v���ݒ�
	inline void	SetLoop(bool f) { _IsLoop = f; }
	//	���[�v���擾
	inline bool	IsLoop(void) { return _IsLoop; }
};