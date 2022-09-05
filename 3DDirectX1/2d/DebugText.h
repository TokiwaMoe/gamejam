#pragma once
#include "Sprite.h"
#include <Windows.h>
#include <string>
class DebugText
{
public: // �萔�̐錾    
	static const int maxCharCount = 256;    // �ő啶����
	static const int fontWidth = 9;         // �t�H���g�摜��1�������̉���
	static const int fontHeight = 18;       // �t�H���g�摜��1�������̏c��
	static const int fontLineCount = 14;    // �t�H���g�摜��1�s���̕�����
	static const int bufferSize = 256;	// �����t��������W�J�p�o�b�t�@�T�C�Y

public: // �����o�֐�

	static DebugText* GetInstance();

	void Initialize(UINT texnumber);
	void Print(int len, const std::string& text, float x, float y, float scale);
	//void NPrint(int len, const char* text);
	void Printf(float x, float y, float scale, const char* fmt, ...);
	void DrawAll(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�     
	DebugText() = default;
	DebugText(const DebugText&) = delete;
	~DebugText() = default;
	DebugText& operator=(const DebugText&) = delete;
	// �X�v���C�g�f�[�^�̔z��
	Sprite* sprite[maxCharCount] = {};
	// �X�v���C�g�f�[�^�z��̓Y�����ԍ�
	int spriteIndex = 0;

	char buffer[bufferSize];


	float posX = 0.0f;
	float posY = 0.0f;
	float size = 1.0f;
};