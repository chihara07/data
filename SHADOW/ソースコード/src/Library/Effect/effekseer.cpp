#include "DxLib.h"
#include "effekseer.h"
#include <locale.h>
#include <uchar.h>


//	new�Edelete�͂�����SAFE_RELEASE�ȂǂŊJ�������ق����悢
//	�ނ���X�}�[�g�|�C���^�Ȃǂ��g���Ă��悢
//	����Ă�����static�N���X�ɂ��Ȃ��Ă��悢

#ifdef _DEBUG
#ifdef _WIN64
#if _MSC_VER >= 1930
// vs2022 64�r�b�g�f�o�b�O
#pragma comment(lib,"install_msvc2022_x64/Effekseer_vs2022_x64_d.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX9_vs2022_x64_d.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX11_vs2022_x64_d.lib")
#else
// vs2019 64�r�b�g�f�o�b�O
#pragma comment(lib,"install_msvc2019_x64/Effekseer_vs2019_x64_d.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX9_vs2019_x64_d.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX11_vs2019_x64_d.lib")
#endif
#else
#if _MSC_VER >= 1930
// vs2022 32�r�b�g�f�o�b�O
#pragma comment(lib,"install_msvc2022_x86/Effekseer_vs2022_x86_d.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX9_vs2022_x86_d.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX11_vs2022_x86_d.lib")
#else
// vs2019 32�r�b�g�f�o�b�O
#pragma comment(lib,"install_msvc2019_x86/Effekseer_vs2019_x86_d.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX9_vs2019_x86_d.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX11_vs2019_x86_d.lib")
#endif
#endif
#else
#ifdef _WIN64
#if _MSC_VER >= 1930
// vs2022 64�r�b�g�����[�X
#pragma comment(lib,"install_msvc2022_x64/Effekseer_vs2022_x64.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX9_vs2022_x64.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX11_vs2022_x64.lib")
#else
// vs2019 64�r�b�g�����[�X
#pragma comment(lib,"install_msvc2019_x64/Effekseer_vs2019_x64.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX9_vs2019_x64.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX11_vs2019_x64.lib")
#endif
#else
#if _MSC_VER >= 1930
// vs2022 32�r�b�g�����[�X
#pragma comment(lib,"install_msvc2022_x86/Effekseer_vs2022_x86.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX9_vs2022_x86.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX11_vs2022_x86.lib")
#else
// vs2019 32�r�b�g�����[�X
#pragma comment(lib,"install_msvc2019_x86/Effekseer_vs2019_x86.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX9_vs2019_x86.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX11_vs2019_x86.lib")
#endif
#endif
#endif

//---------------------------------
//		�R���X�g���N�^
//---------------------------------
CEffekseer::CEffekseer()
{
	ZeroMemory(&_Pos, sizeof(_Pos));
	ZeroMemory(&_Rot, sizeof(_Rot));
	_Scale = VGet(1.0f, 1.0f, 1.0f);
	_Hndl = -1;
	_ID = -1;
	_IsLoop = false;
}


//---------------------------------
//		�f�X�g���N�^
//---------------------------------
CEffekseer::~CEffekseer()
{
}


//---------------------------------
//		���Z�b�g
//---------------------------------
void	CEffekseer::Reset(void)
{
	ZeroMemory(&_Pos, sizeof(_Pos));
	ZeroMemory(&_Rot, sizeof(_Rot));
	_Scale = VGet(1.0f, 1.0f, 1.0f);
	_Hndl = -1;
	_IsLoop = false;
}








CEffekseer* CEffekseerCtrl::_Eff;
std::vector<::Effekseer::EffectRef>	CEffekseerCtrl::_Effect;
::EffekseerRendererDX9::RendererRef CEffekseerCtrl::_Renderer9;
::EffekseerRendererDX11::RendererRef CEffekseerCtrl::_Renderer11;
::Effekseer::ManagerRef CEffekseerCtrl::_Manager;
int			CEffekseerCtrl::_AllNum;
int			CEffekseerCtrl::_UseID;
int			CEffekseerCtrl::_DxVersion;
int			CEffekseerCtrl::_ID[(int)CEffekseerCtrl::eEffectID::NUM];


#define DX_VERSION_9	(9)
#define DX_VERSION_11	(11)


//---------------------------------
//		�R���X�g���N�^
//---------------------------------
CEffekseerCtrl::CEffekseerCtrl()
{
	_Eff = nullptr;
	_Renderer9 = nullptr;
	_Renderer11 = nullptr;
	_Manager = nullptr;
	_AllNum = 0;
	_DxVersion = -1;
	_UseID = 0;
}


//---------------------------------
//		�f�X�g���N�^
//---------------------------------
CEffekseerCtrl::~CEffekseerCtrl()
{
	Fin();
}


//---------------------------------
//		������
//---------------------------------
void	CEffekseerCtrl::Init(int eff_num, int particle_num)
{
	Fin();

	// �`��p�C���X�^���X�̐���
	EffekseerRenderer::RendererRef renderer;
	ID3D11Device* device = (ID3D11Device*)GetUseDirect3D11Device();
	ID3D11DeviceContext* context = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	if (device == nullptr || context == nullptr)
	{
		SetUseDirect3D9Ex(FALSE);	// LPDIRECT3DDEVICE9���擾�ł���悤�ɔO�̂��ߐݒ�
		LPDIRECT3DDEVICE9 device9 = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
		_Renderer9 = ::EffekseerRendererDX9::Renderer::Create(device9, particle_num);
		_DxVersion = DX_VERSION_9;
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	}
	else
	{
		_Renderer11 = ::EffekseerRendererDX11::Renderer::Create(device, context, particle_num);
		_DxVersion = DX_VERSION_11;
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	}


	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	_Manager = ::Effekseer::Manager::Create(particle_num);

	// �`��p�C���X�^���X����`��@�\��ݒ�
	_Manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	_Manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	_Manager->SetRingRenderer(renderer->CreateRingRenderer());
	_Manager->SetModelRenderer(renderer->CreateModelRenderer());
	_Manager->SetTrackRenderer(renderer->CreateTrackRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	_Manager->SetTextureLoader(renderer->CreateTextureLoader());
	_Manager->SetModelLoader(renderer->CreateModelLoader());
	_Manager->SetMaterialLoader(renderer->CreateMaterialLoader());
	_Manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// �f�o�C�X���X�g���̃R�[���o�b�N�ݒ�(�t���X�N���[���E�C���h�E�؂�ւ��̂��߂ɕK�v)
	SetGraphicsDeviceLostCallbackFunction(DeviceLostFunction, NULL);
	SetGraphicsDeviceRestoreCallbackFunction(DeviceRestoreFunction, NULL);

	// ���W�͍�����W�n��
	_Manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);

	// ���e�s���ݒ�(����͉�)
	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(90.0f / 180.0f * 3.14f, 640.0f / 480.0f, 1.0f, 1000.0f));
	// �J�����s���ݒ�(�������)
	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(0.0f, 0.0f, -20.0f), ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

	// �ʃG�t�F�N�g�̃������m��
	_Eff = new CEffekseer[eff_num];
	_AllNum = eff_num;

	// ������
	_Effect.clear();
	_UseID = 0;
}


//---------------------------------
//		�I������
//---------------------------------
void	CEffekseerCtrl::Fin(void)
{
	// ������ƕs���Ȕj����ƒB
	if (_Eff != nullptr)
	{
		delete[]_Eff;
		_Eff = nullptr;
		_AllNum = 0;
	}
	// �����_���[�֘A������
	_Renderer9.Reset();
	_Renderer11.Reset();
	_DxVersion = -1;
	// �}�l�[�W��������
	_Manager.Reset();

	_Effect.clear();
}


//---------------------------------
//		�G�t�F�N�g�f�[�^���[�h
//---------------------------------
void	CEffekseerCtrl::LoadData()
{
	const char pFileName[(int)eEffectID::NUM][128] =
	{
		"data/Effect/change.efkefc",
		"data/Effect/death.efkefc",
	};

	// �G�t�F�N�g�̓Ǎ�
	for (int j = 0; j < (int)eEffectID::NUM; j++) {
		EFK_CHAR rename[256] = {};
		for (int i = 0; i < 256; i++)
		{
			mbstate_t mbstate = { 0 };
			size_t s = mbrtoc16(&rename[i], &pFileName[j][i], 1, &mbstate);
			if (s <= 0) break;
		}
		::Effekseer::EffectRef temp = nullptr;
		temp = ::Effekseer::Effect::Create(_Manager, rename);
		if (temp != nullptr)
		{
			_Effect.push_back(temp);
			_ID[j] = static_cast<int>(_Effect.size()) - 1;
		}

	}
}


//---------------------------------
//		���e�s��ݒ�
//---------------------------------
void	CEffekseerCtrl::SetProjectionMtx(float pers, float aspect, float near_length, float far_length)
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(pers, aspect, near_length, far_length));
}


//---------------------------------
//		���e�s�񎩓��ݒ�
//---------------------------------
void	CEffekseerCtrl::SetAutoProjectionMtx()
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	// �𑜓x�擾
	RECT rect;
	GetWindowCRect(&rect);
	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(GetCameraFov(), static_cast<float>(rect.right - rect.left) / static_cast<float>(rect.bottom - rect.top), GetCameraNear(), GetCameraFar()));
}


//---------------------------------
//		�J�����s��ݒ�
//---------------------------------
void	CEffekseerCtrl::SetCameraMtx(VECTOR eye_pos, VECTOR focus_pos, VECTOR up)
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye_pos.x, eye_pos.y, eye_pos.z),
			::Effekseer::Vector3D(focus_pos.x, focus_pos.y, focus_pos.z),
			::Effekseer::Vector3D(up.x, up.y, up.z)));
}


//---------------------------------
//		�J�����s�񎩓��ݒ�
//---------------------------------
void	CEffekseerCtrl::SetAutoCameraMtx()
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	VECTOR pos = GetCameraPosition();
	VECTOR target = GetCameraTarget();
	VECTOR up = GetCameraUpVector();

	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(pos.x, pos.y, pos.z),
			::Effekseer::Vector3D(target.x, target.y, target.z),
			::Effekseer::Vector3D(up.x, up.y, up.z)));
}


//---------------------------------
//		�J�����s��ݒ�
//---------------------------------
void	CEffekseerCtrl::SetCameraRotMtx(VECTOR eye_pos, VECTOR rot, VECTOR up)
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	// ( 0, 0, 1 )�̃x�N�g����XYZ���̏��Ԃŉ�]��������@�Œ����_���o��
	VECTOR focusPos, temp;
	// X����]
	temp.x = 0.0f;
	temp.y = -1.0f * sinf(rot.x);
	temp.z = 1.0f * cosf(rot.x);
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// Y����]
	temp.x = focusPos.x * cosf(rot.y) + focusPos.z * sinf(rot.y);
	temp.y = focusPos.y;
	temp.z = focusPos.z * cosf(rot.y) - focusPos.x * sinf(rot.y);
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// Z����]
	temp.x = focusPos.x * cosf(rot.z) - focusPos.y * sinf(rot.z);
	temp.y = focusPos.x * sinf(rot.z) + focusPos.y * cosf(rot.z);
	temp.z = focusPos.z;
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// ���_�ɉ��Z
	focusPos = VAdd(eye_pos, focusPos);

	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye_pos.x, eye_pos.y, eye_pos.z),
			::Effekseer::Vector3D(focusPos.x, focusPos.y, focusPos.z),
			::Effekseer::Vector3D(up.x, up.y, up.z)));
}


//---------------------------------
//		�X�V����
//---------------------------------
void	CEffekseerCtrl::Update(void)
{
	if (_Eff == nullptr) return;

	// �G�t�F�N�g�̍X�V�������s��
	_Manager->Update();

	for (int i = 0; i < _AllNum; i++)
	{
		int hndl = _Eff[i].GetHndl();
		if (hndl == -1 || _Manager->Exists(hndl))
		{
			continue;
		}

		// ���[�v�ݒ�̂��̂͏I����ēx����������
		if (_Eff[i].IsLoop())
		{
			VECTOR	pos = _Eff[i].GetTrans();
			_Eff[i].SetHndl(_Manager->Play(_Effect[_Eff[i].GetID()], pos.x, pos.y, pos.z));
			VECTOR scale = _Eff[i].GetScale();
			_Manager->SetScale(_Eff[i].GetHndl(), scale.x, scale.y, scale.z);
			VECTOR rot = _Eff[i].GetRot();
			_Manager->SetRotation(_Eff[i].GetHndl(), rot.x, rot.y, rot.z);
		}
		// ���[�v�ȊO�͍ė��p�̏���
		else
		{
			_Eff[i].SetHndl(-1);
		}
	}
}


//---------------------------------
//		�X�V����
//---------------------------------
void	CEffekseerCtrl::UpdateAutoCamera(void)
{
	SetAutoProjectionMtx();
	SetAutoCameraMtx();
	Update();
}


//---------------------------------
//		�`�揈��
//---------------------------------
void	CEffekseerCtrl::Draw(void)
{
	EffekseerRenderer::RendererRef renderer;
	if (_DxVersion == DX_VERSION_9)
		renderer = (EffekseerRenderer::RendererRef)_Renderer9;
	else if (_DxVersion == DX_VERSION_11)
		renderer = (EffekseerRenderer::RendererRef)_Renderer11;
	else
		return;

	// ���_�o�b�t�@�ɗ��܂������_�f�[�^��f���o��
	RenderVertex();

	// �G�t�F�N�g�̕`��J�n�������s���B
	renderer->BeginRendering();

	// �G�t�F�N�g�̕`����s���B
	_Manager->Draw();

	// �G�t�F�N�g�̕`��I���������s���B
	renderer->EndRendering();

	// DX���C�u�����̐ݒ��߂��B
	RefreshDxLibDirect3DSetting();
}


//---------------------------------
//		�G�t�F�N�g�Ăяo��
//---------------------------------
int	CEffekseerCtrl::Request(int ID, VECTOR pos, bool f)
{
	if (_Eff == nullptr || ID < 0) return -1;

	for (int i = 0; i < _AllNum; i++)
	{
		int number = (_UseID + i) % _AllNum;
		if (_Eff[number].GetHndl() == -1)
		{
			_Eff[number].SetHndl(_Manager->Play(_Effect[ID], pos.x, pos.y, pos.z));
			_Eff[number].SetLoop(f);
			_Eff[number].SetID(ID);
			_Eff[number].SetTrans(pos);
			_Eff[number].SetScale(VGet(1.0f, 1.0f, 1.0f));
			_UseID = (number + 1) % _AllNum;
			return number;
		}
	}

	return -1;
}


//---------------------------------
//		�w��G�t�F�N�g��~
//---------------------------------
void	CEffekseerCtrl::Stop(int hndl)
{
	if (_Manager == nullptr) return;
	_Manager->StopEffect(_Eff[hndl].GetHndl());
	_Eff[hndl].Reset();
}


//---------------------------------
//		�S�G�t�F�N�g��~
//---------------------------------
void	CEffekseerCtrl::StopAll(void)
{
	if (_Manager == nullptr) return;

	_Manager->StopAllEffects();

	for (int i = 0; i < _AllNum; i++)
	{
		if (_Eff[i].GetHndl() != -1)
		{
			_Eff[i].Reset();
		}
	}
}


//---------------------------------
//		���W�ύX
//---------------------------------
void	CEffekseerCtrl::SetPosition(int hndl, VECTOR pos)
{
	if (_Manager != nullptr && _Eff != nullptr)
	{
		_Manager->SetLocation(_Eff[hndl].GetHndl(), pos.x, pos.y, pos.z);
		_Eff[hndl].SetTrans(pos);
	}
}


//---------------------------------
//		�g��k�����ύX
//---------------------------------
void	CEffekseerCtrl::SetScale(int hndl, VECTOR scale)
{
	if (_Manager != nullptr && _Eff != nullptr)
	{
		_Manager->SetScale(_Eff[hndl].GetHndl(), scale.x, scale.y, scale.z);
		_Eff[hndl].SetScale(scale);
	}
}


//---------------------------------
//		��]�p�x�ύX
//---------------------------------
void	CEffekseerCtrl::SetRot(int hndl, VECTOR rot)
{
	if (_Manager != nullptr && _Eff != nullptr)
	{
		_Manager->SetRotation(_Eff[hndl].GetHndl(), rot.x, rot.y, rot.z);
		_Eff[hndl].SetRot(rot);
	}
}


//---------------------------------
//		��]�p�x�ύX
//---------------------------------
bool	CEffekseerCtrl::IsActive(int hndl)
{
	int localHndl = _Eff[hndl].GetHndl();
	if (localHndl == -1)
	{
		return false;
	}
	return true;
}


//---------------------------------
//		�f�o�C�X���X�g���̃R�[���o�b�N�֐�
//---------------------------------
void	CEffekseerCtrl::DeviceLostFunction(void* data)
{
	// DirectX9�̂ݑΉ��Ƃ���
	if (_DxVersion != DX_VERSION_9) return;

	// �f�o�C�X���X�g�������������ɌĂ�
	if (_Renderer9 != NULL) _Renderer9->OnLostDevice();

	// �ǂݍ��񂾃G�t�F�N�g�̃��\�[�X�͑S�Ĕj������
	if (_Eff != NULL)
	{
		for (int i = 0; i < _AllNum; i++)
		{
			_Effect[i]->UnloadResources();
		}
	}

	// DX���C�u�����͓����Ńf�o�C�X���̂��������Ă���̂�NULL��ݒ肷��
	if (_Renderer9 != NULL) _Renderer9->ChangeDevice(NULL);
}


//---------------------------------
//		�f�o�C�X���A���̃R�[���o�b�N�֐�
//---------------------------------
void	CEffekseerCtrl::DeviceRestoreFunction(void* data)
{
	// DirectX9�̂ݑΉ��Ƃ���
	if (_DxVersion != DX_VERSION_9) return;

	// DX���C�u�����͉񕜎��ɓ����Ńf�o�C�X���Đ�������̂ŐV�����ݒ肷��
	if (_Renderer9 != NULL)
	{
		LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
		_Renderer9->ChangeDevice(device);
	}

	// �G�t�F�N�g�̃��\�[�X���ēǂݍ��݂���
	if (_Eff != NULL)
	{
		for (int i = 0; i < _AllNum; i++)
		{
			_Effect[i]->ReloadResources();
		}
	}

	// �f�o�C�X�����A����Ƃ��ɌĂ�
	if (_Renderer9 != NULL) _Renderer9->OnResetDevice();
}