#pragma once
#include <vector>

using namespace std;

class  CInputManager{
private:
	static vector<int> _InputKey;		//�L�[���͗p�z��
	static vector<int> _InputPad;		//�p�b�h���͗p�z��
public:
	//���͔��ʗp�񋓌^
	enum class eInputType{
		MOVE_UP,		//��ړ�
		MOVE_DOWN,		//���ړ�
		MOVE_R,			//�E�ړ�
		MOVE_L,			//���ړ�
		SHADOW,			//�e
		JUMP,			//�W�����v
		FALL,			//���~
		TELEPORT,		//�e���|�[�g
		SELECT,			//�I��

		NUM
	};

	//���͐��䏉����
	static void Init();

	//���͐���X�e�b�v
	static void Step();

	//�������ꂽ
	static bool IsPush(eInputType input_code);

	//�����������Ă��邩
	static bool IsKeep(eInputType input_code);

	//�������������ꂽ��
	static bool IsRelease(eInputType input_code);

	//�P���ɉ�����Ă��邩
	static bool IsDown(eInputType input_code);

	//X�����͒l(�E�X�e�B�b�N�A�����L�[)
	static float GetRInputX();

	//Y�����͒l(�E�X�e�B�b�N�A�����L�[)
	static float GetRInputY();

	//X�����͒l(���X�e�B�b�N�A�����{�^���AA.D�L�[)
	static float GetLInputX();

	//Y�����͒l(���X�e�B�b�N�A�����{�^���AW.S�L�[)
	static float GetLInputY();
};
