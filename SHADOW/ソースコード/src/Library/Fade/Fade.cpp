#include "Fade.h"
#include <DxLib.h>
#include <crtdbg.h>
#include "../../Library/Common.h"
#include "../../Library/Color.h"

constexpr float MAX_ALPHA_VALUE = 255.f;		//アルファ最大値

CFade* CFade::_Instance = nullptr;

//インスタンス取得
CFade* CFade::GetInstance() {
	if (_Instance == nullptr) {
		_Instance = New CFade;
		_Instance->_State = eFadeState::NON;
	}
	return _Instance;
}
//インスタンス破棄
void CFade::DeleteInstance() {
	if (_Instance != nullptr) {
		delete _Instance;
		_Instance = nullptr;
	}
}

//コンストラクタ・デストラクタ
CFade::CFade() : _AlphaValue(0.f), _Spd(0.f),_State(eFadeState::NON),
	_WindowX(WINDOW_WIDTH), _WindowY(WINDOW_HEIGHT) {

}

CFade::~CFade() {

}

//フェードリクエスト
void CFade::RequestFade(float spd, bool is_in) {
	_Spd = spd;
	_State = is_in ? eFadeState::FADE_IN : eFadeState::FADE_OUT;
	_AlphaValue = is_in ? MAX_ALPHA_VALUE : 0.f;
}
//更新
void CFade::Update() {
	switch (_State)
	{
	case eFadeState::FADE_IN:
		_AlphaValue -= _Spd;
		if (_AlphaValue < 0.f) _AlphaValue = 0.f;
		break;
	case eFadeState::FADE_OUT:
		_AlphaValue += _Spd;
		if (_AlphaValue > MAX_ALPHA_VALUE) _AlphaValue = MAX_ALPHA_VALUE;
		break;
	}
}
//描画
void CFade::Draw() {
	if (_State == eFadeState::NON) return;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)_AlphaValue);
	DrawBox(0, 0, _WindowX, _WindowY, COLOR::BLACK, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
//終了判定
bool CFade::IsEnd() {
	bool isRet = true;

	switch (_State)
	{
	case eFadeState::FADE_IN:
		if (_AlphaValue > 0.f) isRet = false;
		break;
	case eFadeState::FADE_OUT:
		if (_AlphaValue < MAX_ALPHA_VALUE) isRet = false;
		break;
	}

	return isRet;
}
