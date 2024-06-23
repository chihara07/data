#include "DxLib.h"
#include "effekseer.h"
#include <locale.h>
#include <uchar.h>


//	new・deleteはちゃんとSAFE_RELEASEなどで開放したほうがよい
//	むしろスマートポインタなどを使ってもよい
//	慣れてきたらstaticクラスにしなくてもよい

#ifdef _DEBUG
#ifdef _WIN64
#if _MSC_VER >= 1930
// vs2022 64ビットデバッグ
#pragma comment(lib,"install_msvc2022_x64/Effekseer_vs2022_x64_d.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX9_vs2022_x64_d.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX11_vs2022_x64_d.lib")
#else
// vs2019 64ビットデバッグ
#pragma comment(lib,"install_msvc2019_x64/Effekseer_vs2019_x64_d.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX9_vs2019_x64_d.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX11_vs2019_x64_d.lib")
#endif
#else
#if _MSC_VER >= 1930
// vs2022 32ビットデバッグ
#pragma comment(lib,"install_msvc2022_x86/Effekseer_vs2022_x86_d.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX9_vs2022_x86_d.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX11_vs2022_x86_d.lib")
#else
// vs2019 32ビットデバッグ
#pragma comment(lib,"install_msvc2019_x86/Effekseer_vs2019_x86_d.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX9_vs2019_x86_d.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX11_vs2019_x86_d.lib")
#endif
#endif
#else
#ifdef _WIN64
#if _MSC_VER >= 1930
// vs2022 64ビットリリース
#pragma comment(lib,"install_msvc2022_x64/Effekseer_vs2022_x64.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX9_vs2022_x64.lib")
#pragma comment(lib,"install_msvc2022_x64/EffekseerRendererDX11_vs2022_x64.lib")
#else
// vs2019 64ビットリリース
#pragma comment(lib,"install_msvc2019_x64/Effekseer_vs2019_x64.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX9_vs2019_x64.lib")
#pragma comment(lib,"install_msvc2019_x64/EffekseerRendererDX11_vs2019_x64.lib")
#endif
#else
#if _MSC_VER >= 1930
// vs2022 32ビットリリース
#pragma comment(lib,"install_msvc2022_x86/Effekseer_vs2022_x86.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX9_vs2022_x86.lib")
#pragma comment(lib,"install_msvc2022_x86/EffekseerRendererDX11_vs2022_x86.lib")
#else
// vs2019 32ビットリリース
#pragma comment(lib,"install_msvc2019_x86/Effekseer_vs2019_x86.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX9_vs2019_x86.lib")
#pragma comment(lib,"install_msvc2019_x86/EffekseerRendererDX11_vs2019_x86.lib")
#endif
#endif
#endif

//---------------------------------
//		コンストラクタ
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
//		デストラクタ
//---------------------------------
CEffekseer::~CEffekseer()
{
}


//---------------------------------
//		リセット
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
//		コンストラクタ
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
//		デストラクタ
//---------------------------------
CEffekseerCtrl::~CEffekseerCtrl()
{
	Fin();
}


//---------------------------------
//		初期化
//---------------------------------
void	CEffekseerCtrl::Init(int eff_num, int particle_num)
{
	Fin();

	// 描画用インスタンスの生成
	EffekseerRenderer::RendererRef renderer;
	ID3D11Device* device = (ID3D11Device*)GetUseDirect3D11Device();
	ID3D11DeviceContext* context = (ID3D11DeviceContext*)GetUseDirect3D11DeviceContext();
	if (device == nullptr || context == nullptr)
	{
		SetUseDirect3D9Ex(FALSE);	// LPDIRECT3DDEVICE9を取得できるように念のため設定
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


	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// エフェクト管理用インスタンスの生成
	_Manager = ::Effekseer::Manager::Create(particle_num);

	// 描画用インスタンスから描画機能を設定
	_Manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
	_Manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
	_Manager->SetRingRenderer(renderer->CreateRingRenderer());
	_Manager->SetModelRenderer(renderer->CreateModelRenderer());
	_Manager->SetTrackRenderer(renderer->CreateTrackRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	_Manager->SetTextureLoader(renderer->CreateTextureLoader());
	_Manager->SetModelLoader(renderer->CreateModelLoader());
	_Manager->SetMaterialLoader(renderer->CreateMaterialLoader());
	_Manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());

	// デバイスロスト時のコールバック設定(フルスクリーンウインドウ切り替えのために必要)
	SetGraphicsDeviceLostCallbackFunction(DeviceLostFunction, NULL);
	SetGraphicsDeviceRestoreCallbackFunction(DeviceRestoreFunction, NULL);

	// 座標は左手座標系に
	_Manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);

	// 投影行列を設定(これは仮)
	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(90.0f / 180.0f * 3.14f, 640.0f / 480.0f, 1.0f, 1000.0f));
	// カメラ行列を設定(これも仮)
	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(0.0f, 0.0f, -20.0f), ::Effekseer::Vector3D(0.0f, 0.0f, 0.0f), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

	// 個別エフェクトのメモリ確保
	_Eff = new CEffekseer[eff_num];
	_AllNum = eff_num;

	// 初期化
	_Effect.clear();
	_UseID = 0;
}


//---------------------------------
//		終了処理
//---------------------------------
void	CEffekseerCtrl::Fin(void)
{
	// ちょっと不安な破棄作業達
	if (_Eff != nullptr)
	{
		delete[]_Eff;
		_Eff = nullptr;
		_AllNum = 0;
	}
	// レンダラー関連初期化
	_Renderer9.Reset();
	_Renderer11.Reset();
	_DxVersion = -1;
	// マネージャ初期化
	_Manager.Reset();

	_Effect.clear();
}


//---------------------------------
//		エフェクトデータロード
//---------------------------------
void	CEffekseerCtrl::LoadData()
{
	const char pFileName[(int)eEffectID::NUM][128] =
	{
		"data/Effect/change.efkefc",
		"data/Effect/death.efkefc",
	};

	// エフェクトの読込
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
//		投影行列設定
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
//		投影行列自動設定
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

	// 解像度取得
	RECT rect;
	GetWindowCRect(&rect);
	renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(GetCameraFov(), static_cast<float>(rect.right - rect.left) / static_cast<float>(rect.bottom - rect.top), GetCameraNear(), GetCameraFar()));
}


//---------------------------------
//		カメラ行列設定
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
//		カメラ行列自動設定
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
//		カメラ行列設定
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

	// ( 0, 0, 1 )のベクトルをXYZ軸の順番で回転させる方法で注視点を出す
	VECTOR focusPos, temp;
	// X軸回転
	temp.x = 0.0f;
	temp.y = -1.0f * sinf(rot.x);
	temp.z = 1.0f * cosf(rot.x);
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// Y軸回転
	temp.x = focusPos.x * cosf(rot.y) + focusPos.z * sinf(rot.y);
	temp.y = focusPos.y;
	temp.z = focusPos.z * cosf(rot.y) - focusPos.x * sinf(rot.y);
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// Z軸回転
	temp.x = focusPos.x * cosf(rot.z) - focusPos.y * sinf(rot.z);
	temp.y = focusPos.x * sinf(rot.z) + focusPos.y * cosf(rot.z);
	temp.z = focusPos.z;
	memcpy(&focusPos, &temp, sizeof(VECTOR));
	// 視点に加算
	focusPos = VAdd(eye_pos, focusPos);

	renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(::Effekseer::Vector3D(eye_pos.x, eye_pos.y, eye_pos.z),
			::Effekseer::Vector3D(focusPos.x, focusPos.y, focusPos.z),
			::Effekseer::Vector3D(up.x, up.y, up.z)));
}


//---------------------------------
//		更新処理
//---------------------------------
void	CEffekseerCtrl::Update(void)
{
	if (_Eff == nullptr) return;

	// エフェクトの更新処理を行う
	_Manager->Update();

	for (int i = 0; i < _AllNum; i++)
	{
		int hndl = _Eff[i].GetHndl();
		if (hndl == -1 || _Manager->Exists(hndl))
		{
			continue;
		}

		// ループ設定のものは終了後再度発生させる
		if (_Eff[i].IsLoop())
		{
			VECTOR	pos = _Eff[i].GetTrans();
			_Eff[i].SetHndl(_Manager->Play(_Effect[_Eff[i].GetID()], pos.x, pos.y, pos.z));
			VECTOR scale = _Eff[i].GetScale();
			_Manager->SetScale(_Eff[i].GetHndl(), scale.x, scale.y, scale.z);
			VECTOR rot = _Eff[i].GetRot();
			_Manager->SetRotation(_Eff[i].GetHndl(), rot.x, rot.y, rot.z);
		}
		// ループ以外は再利用の準備
		else
		{
			_Eff[i].SetHndl(-1);
		}
	}
}


//---------------------------------
//		更新処理
//---------------------------------
void	CEffekseerCtrl::UpdateAutoCamera(void)
{
	SetAutoProjectionMtx();
	SetAutoCameraMtx();
	Update();
}


//---------------------------------
//		描画処理
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

	// 頂点バッファに溜まった頂点データを吐き出す
	RenderVertex();

	// エフェクトの描画開始処理を行う。
	renderer->BeginRendering();

	// エフェクトの描画を行う。
	_Manager->Draw();

	// エフェクトの描画終了処理を行う。
	renderer->EndRendering();

	// DXライブラリの設定を戻す。
	RefreshDxLibDirect3DSetting();
}


//---------------------------------
//		エフェクト呼び出し
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
//		指定エフェクト停止
//---------------------------------
void	CEffekseerCtrl::Stop(int hndl)
{
	if (_Manager == nullptr) return;
	_Manager->StopEffect(_Eff[hndl].GetHndl());
	_Eff[hndl].Reset();
}


//---------------------------------
//		全エフェクト停止
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
//		座標変更
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
//		拡大縮小率変更
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
//		回転角度変更
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
//		回転角度変更
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
//		デバイスロスト時のコールバック関数
//---------------------------------
void	CEffekseerCtrl::DeviceLostFunction(void* data)
{
	// DirectX9のみ対応とする
	if (_DxVersion != DX_VERSION_9) return;

	// デバイスロストが発生した時に呼ぶ
	if (_Renderer9 != NULL) _Renderer9->OnLostDevice();

	// 読み込んだエフェクトのリソースは全て破棄する
	if (_Eff != NULL)
	{
		for (int i = 0; i < _AllNum; i++)
		{
			_Effect[i]->UnloadResources();
		}
	}

	// DXライブラリは内部でデバイス自体を消去しているのでNULLを設定する
	if (_Renderer9 != NULL) _Renderer9->ChangeDevice(NULL);
}


//---------------------------------
//		デバイス復帰時のコールバック関数
//---------------------------------
void	CEffekseerCtrl::DeviceRestoreFunction(void* data)
{
	// DirectX9のみ対応とする
	if (_DxVersion != DX_VERSION_9) return;

	// DXライブラリは回復時に内部でデバイスを再生成するので新しく設定する
	if (_Renderer9 != NULL)
	{
		LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)GetUseDirect3DDevice9();
		_Renderer9->ChangeDevice(device);
	}

	// エフェクトのリソースを再読み込みする
	if (_Eff != NULL)
	{
		for (int i = 0; i < _AllNum; i++)
		{
			_Effect[i]->ReloadResources();
		}
	}

	// デバイスが復帰するときに呼ぶ
	if (_Renderer9 != NULL) _Renderer9->OnResetDevice();
}