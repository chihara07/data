#pragma once

//			Effekseer使用クラス
// 使用時はプロパティの「C/C++」→「全般」→「追加のインクルードディレクトリ」に「Effekseer」内の「include」
// 「リンカー」→「全般」→「追加のライブラリディレクトリ」に「Effekseer」
// を追加してください。
// CEffekseerクラスはstaticなので使用する時だけプロジェクトに追加してください。
// また、デバッグ版は警告が出るので「リンカー」→「コマンドライン」→「追加のオプション」に
// 「/ignore:4099 」と記述してください。

//			使用時の注意事項
// CEffekseerCtrl::Draw()前に何かしらDxLibの2D描画関数(半透明処理)が呼ばれてないと
// 描画されない可能性があります。
// また、3Dの透明or半透明の物体の後ろにエフェクトを出してしまうとおかしな見た目になることもあります。

// 現在はVisualStudio2019と2022にのみ対応しています。

#include <DxLib.h>
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <EffekseerRendererDX11.h>
#include <vector>


class CEffekseer;


//		エフェクト管理クラス
//		こっち使って
class CEffekseerCtrl {
public:
	enum class eEffectID {
		CHANGE,			//CHANGE
		DEATH,			//DEATH

		NUM,
	};
	static int _ID[(int)eEffectID::NUM];
protected:
	static CEffekseer*							_Eff;			// エフェクト単品管理クラス
	static std::vector<::Effekseer::EffectRef>	_Effect;		// エフェクトクラス
	static ::Effekseer::ManagerRef				_Manager;		// エフェクトマネージャ
	static ::EffekseerRendererDX9::RendererRef	_Renderer9;	// レンダラー(DirectX9用)
	static ::EffekseerRendererDX11::RendererRef	_Renderer11;	// レンダラー(DirectX11用)
	static int									_AllNum;		// 使用エフェクト総数
	static int									_UseID;		// 次に使用予定のID
	static int									_DxVersion;	// DirectXのバージョン
public:
	//	コンストラクタ・デストラクタ
	CEffekseerCtrl();
	~CEffekseerCtrl();

	//	初期化
	//	eff_num		:	エフェクト総数
	//	particle_num	:	パーティクル総数
	static void Init(int eff_num, int particle_num);
	//	終了処理
	static void Fin(void);

	//	エフェクトデータロード
	static void	LoadData();
	//	投影行列設定
	//	pers		:	カメラのパース
	//	aspect		:	アスペクト比
	//	near_length	:	カメラのニアー
	//	far_length	:	カメラのファー
	//	@memo		:	設定が変わるたびに呼んでください
	static void SetProjectionMtx(float pers, float aspect, float near_length, float far_length);
	//	投影行列自動設定
	//	@memo	:	DxLibの関数で自動設定(なるべく使わない)
	//				画面分割などには対応不可
	static void SetAutoProjectionMtx(void);
	//	カメラ行列設定
	//	eye_pos		:	カメラの視点	
	//	focus_pos	:	カメラの注視点
	//	up			:	カメラの上方向
	//	@memo		:	設定が変わるたびに呼んでください
	static void SetCameraMtx(VECTOR eye_pos, VECTOR focus_pos, VECTOR up);
	//	カメラ行列自動設定
	//	@memo	:	DxLibの関数で自動設定(なるべく使わない)
	static void SetAutoCameraMtx();
	//	カメラ行列設定
	//	eye_pos		:	カメラの視点	
	//	rot			:	カメラの角度
	//	up			:	カメラの上方向
	//	@memo		:	設定が変わるたびに呼んでください
	static void SetCameraRotMtx(VECTOR eye_pos, VECTOR rot, VECTOR up);
	//	更新処理
	static void Update(void);
	//	更新処理
	//	@memo	: カメラ設定も自動(なるべく使わない)
	//			  ProjectionMtx,CameraMtxの設定も不要
	static void UpdateAutoCamera(void);
	//	描画処理
	static void Draw(void);


	//	エフェクト呼び出し
	//	id		:	エフェクトID
	//	pos		:	初期位置
	//	f	:	エフェクトがループするか
	static int Request(int id, VECTOR pos, bool f);
	//	指定エフェクト停止
	static void Stop(int hndl);
	//	全エフェクト停止
	static void StopAll(void);

	//	座標変更
	static void SetPosition(int hndl, VECTOR pos);
	//	拡大縮小率変更
	static void SetScale(int hndl, VECTOR scale);
	//	回転角度変更
	static void SetRot(int hndl, VECTOR rot);
	//	エフェクトアクティブ判定
	static bool IsActive(int hndl);

private:
	//	デバイスロスト時のコールバック関数
	static void DeviceLostFunction(void* data);
	//	デバイス復帰時のコールバック関数
	static void DeviceRestoreFunction(void* data);
};



//		エフェクト単品管理クラス
//		こちらは基本使わない
class CEffekseer {
protected:
	VECTOR				_Pos;			// エフェクトの再生位置
	VECTOR				_Scale;			// エフェクトの倍率
	VECTOR				_Rot;			// エフェクトの回転
	int					_Hndl;			// エフェクトハンドル
	int					_ID;			// 再生中のエフェクトID
	bool				_IsLoop;		// ループフラグ

public:
	//	コンストラクタ・デストラクタ
	CEffekseer();
	~CEffekseer();

	void Reset(void);

	//	座標設定
	inline void	SetTrans(VECTOR pos) { _Pos = pos; }
	//	座標取得
	inline VECTOR	GetTrans(void) { return _Pos; }
	//	拡大縮小率設定
	inline void	SetScale(VECTOR scale) { _Scale = scale; }
	//	拡大縮小率取得
	inline VECTOR	GetScale(void) { return _Scale; }
	//	角度設定
	inline void	SetRot(VECTOR rot) { _Rot = rot; }
	//	角度取得
	inline VECTOR	GetRot(void) { return _Rot; }
	//	エフェクトハンドル設定
	inline void	SetHndl(int hndl) { _Hndl = hndl; }
	//	エフェクトハンドル取得
	inline int	GetHndl(void) { return _Hndl; }
	//	エフェクトID設定
	inline void	SetID(int id) { _ID = id; }
	//	エフェクトID取得
	inline int	GetID(void) { return _ID; }
	//	ループ情報設定
	inline void	SetLoop(bool f) { _IsLoop = f; }
	//	ループ情報取得
	inline bool	IsLoop(void) { return _IsLoop; }
};