#include <crtdbg.h>
#include <math.h>
#include "GameSystem.h"
#include "../Library/Common.h"
#include "../Library/FrameRate/FrameRate.h"
#include "../Library/Input/InputManager.h"
#include "../../Game/Draw/DrawManager.h"
#include "../Game/Scene/SceneManager.h"
#include "../../Library/Effect/effekseer.h"

//静的変数の実態宣言
bool CGameSystem::_IsGemeEnd = false;
//シーン
CSceneManager cSceneManager;

void CGameSystem::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// メモリリークチェック用
	//ウィンドウの設定
	ChangeWindowMode(true);
}

void CGameSystem::Start()
{
	//DxLibを起動する前に行う処理
	Init();

	//DXライブラリ初期化処理
	if (DxLib_Init() == -1) {
		RequestGameEnd();
	}

	//ウィンドウサイズを設定
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

	//描画するスクリーンを設定
	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 0, 255);	// 透過色指定

	//入力初期化
	CInputManager::Init();

}

void CGameSystem::MainLoop()
{
	//ゲームメインループ
	while (ProcessMessage() != -1)
	{
		//ESCキーかゲーム終了フラグが立っていれば終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) || IsGameEnd()) break;

		//通常処理
		Step();
	}
}

void CGameSystem::Step()
{
	//システムに処理を返す
	Sleep(1);
	//=====================

	//フレームレート通常処理
	CFrameRate::Step();

	//実行可能ならメインの処理に通る
	if (CFrameRate::IsExecutable())
	{
		//フレームレート更新処理
		CFrameRate::Update();

		//画面に表示されたものを初期化(1ループの1度だけ行う)
		ClearDrawScreen();

		//入力ステップ
		CInputManager::Step();

		//↓ここにゲームのメイン処理とか書く
		cSceneManager.Loop();

		cSceneManager.Draw();

		//フリップ関数(ループの終わりに1度だけ行う)
		ScreenFlip();
	}
}

void CGameSystem::Fin()
{
	//描画マネージャー破棄
	CDrawManager::GetInstance()->DeleteInstance();
	//エフェクト破棄
	CEffekseerCtrl::Fin();

	//使用したすべての画像を破棄
	InitGraph();

	//DXライブラリの終了処理
	DxLib_End();
}
