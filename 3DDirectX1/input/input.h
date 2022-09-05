#pragma once

#include <Windows.h>
#include <wrl.h>
#include "WinApp.h"
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include <DirectXMath.h>
enum ButtonKind
{
	LButtonUp,
	LButtonDown,
	LButtonLeft,
	LButtonRight,
	RButtonUp,
	RButtonDown,
	RButtonLeft,
	RButtonRight,
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	ButtonRB,
	ButtonLB,
	Select,
	Start,
	ButtonRT,
	ButtonLT,
	ButtonKindMax,
};
enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};


class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;

public: 

	static Input* GetInstance();

	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

	void Initialize(WinApp* winapp);
	void update();
private:
	/// <summary>
	/// �L�[�{�[�h�̏�����
	/// </summary>
	void InitializeKeybord(WinApp* winapp);
	/// <summary>
	/// �}�E�X�̏�����
	/// </summary>
	void InitializeMouse(WinApp* winapp);

	/// <summary>
	/// �Q�[���p�b�h�̏�����
	/// </summary>
	bool InitializePad();

	void ReleaseInput();
	/// <summary>
	/// �L�[�{�[�h�̍X�V
	/// </summary>
	void updateKeybord();
	/// <summary>
	/// �}�E�X�̍X�V
	/// </summary>
	void updateMouse();
	/// <summary>
	/// �Q�[���p�b�h�̍X�V
	/// </summary>
	void updatePad();
public:
	//�L�[�{�[�h����
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
	//�}�E�X����
	bool PushMouse(int MouseNumber);
	bool TriggerMouse(int MouseNumber);
	XMFLOAT2 GetMousePos() { return MousePos; }
	//�}�E�X�̈ړ���
	MouseMove GetMouseMove();
	//�{�^������
	bool IsButtonPush(ButtonKind button);
	bool IsButtonUp(ButtonKind button);
	bool IsButtonDown(ButtonKind button);
	
	bool ConRightInput();
	bool ConLeftInput();
	
	float GetLeftAngle();
	float GetRightAngle();



private: // �����o�ϐ�
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouse = { 0 };
	DIMOUSESTATE2 oldMouse = { 0 };

	// �Q�[���p�b�h�̓��͏��擾
	ComPtr<IDirectInputDevice8> devGamePad;
	DIJOYSTATE pad_data;
	DIJOYSTATE oldpad_data;
	LPDIRECTINPUTDEVICE8 g_GamePadDevice = nullptr;
	LPDIRECTINPUT8 g_InputInterface = nullptr;
	XMFLOAT2 MousePos = { 0,0 };
	WinApp* winapp = nullptr;
};
