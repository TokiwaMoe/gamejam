#pragma once
#include <Windows.h>

/// <summary>
/// �E�B���h�E�Y�A�v���P�[�V����
/// </summary>
class WinApp
{
public: 
	// �E�B���h�E�T�C�Y
	static const int window_width = 1280;	// ����
	static const int window_height = 720;	// �c��
	static const wchar_t windowClassName[];

	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void CreateGameWindow();


	void TerminateGameWindow();

	bool ProcessMessage();


	HWND GetHwnd() { return hwnd; }

	HINSTANCE GetInstance() { return w.hInstance; }

private: 
	// Window�֘A
	HWND hwnd = nullptr;	// �E�B���h�E�n���h��
	WNDCLASSEX w{};			// �E�B���h�E�N���X
};

