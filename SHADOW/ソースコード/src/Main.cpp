#include "../Src/Game/GameSystem.h"

//�v���O������WinMain����n�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//�Q�[���̋N��
	CGameSystem::Start();

	//�Q�[���̃��[�v
	CGameSystem::MainLoop();

	//�Q�[���̏I��
	CGameSystem::Fin();

	//�v���O�����̏I��
	return 0;
}