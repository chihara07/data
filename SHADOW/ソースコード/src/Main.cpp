#include "../Src/Game/GameSystem.h"

//プログラムはWinMainから始まる
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//ゲームの起動
	CGameSystem::Start();

	//ゲームのループ
	CGameSystem::MainLoop();

	//ゲームの終了
	CGameSystem::Fin();

	//プログラムの終了
	return 0;
}