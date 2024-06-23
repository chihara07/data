#pragma once

//�t�F�[�h�C���E�t�F�[�h�A�E�g�N���X
class CFade {
public:
	//�t�F�[�h�̏�ԗp��
	enum class eFadeState{
		NON,
		FADE_IN,
		FADE_OUT,
	};
private:
	static CFade* _Instance;		//�C���X�^���X

	float _AlphaValue;				//�t�F�[�h�̃A���t�@�l
	float _Spd;						//�t�F�[�h���x
	eFadeState _State;			//�t�F�[�h�̏��
	int _WindowX;					//�E�B���h�E�T�C�Y��
	int _WindowY;					//�E�B���h�E�T�C�Y�c

public:
	//�C���X�^���X�擾
	static CFade* GetInstance();
	//�C���X�^���X�j��
	static void DeleteInstance();

	/// <summary>
	/// �t�F�[�h���N�G�X�g
	/// </summary>
	/// <param name="spd">�t�F�[�h���x0�`255</param>
	/// <param name="is_in">true = �t�F�[�h�C�� false = �t�F�[�h�A�E�g</param>
	void RequestFade(float spd, bool is_in = true);
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�I������
	bool IsEnd();
	//�t�F�[�h�̏�Ԏ擾
	const eFadeState GetState() { return _State; }
	//�E�B���h�E�T�C�Y�ݒ�
	void SetWindowSize(int x, int y) { _WindowX = x; _WindowY = y; }
	//���Z�b�g
	void Reset() { _State = eFadeState::NON; }
private:

	//�R���X�g���N�^�E�f�X�g���N�^
	CFade();
	~CFade();

	//�V���O���g���Ȃ̂ő��ł̐������֎~
	CFade(const CFade& other);
	CFade operator= (const CFade& other) {}
};