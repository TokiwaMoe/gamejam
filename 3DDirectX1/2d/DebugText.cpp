#include "DebugText.h"


//DebugText::~DebugText()
//{
//	for (int i = 0; i < _countof(sprite); i++) {
//		delete sprite[i];
//	}
//}


DebugText* DebugText::GetInstance()
{
	static DebugText instance;

	return &instance;
}

void DebugText::Initialize(UINT texnumber)
{
	// �S�ẴX�v���C�g�f�[�^�ɂ���
	for (int i = 0; i < _countof(sprite); i++)
	{
		// �X�v���C�g�𐶐�����
		sprite[i] = Sprite::CreateSprite(texnumber, { 0,0 });
	}
}

void DebugText::Print(int len, const std::string& text, float x, float y, float scale = 1.0f)
{
	// �S�Ă̕����ɂ���
	for (int i = 0; i < len; i++)
	{
		// �ő啶��������
		if (spriteIndex >= maxCharCount) {
			break;
		}

		// 1�������o��(��ASCII�R�[�h�ł������藧���Ȃ�)
		const unsigned char& character = text[i];

		// ASCII�R�[�h��2�i����΂����ԍ����v�Z
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		// ���W�v�Z
		sprite[spriteIndex]->SetPosition({ x + fontWidth * scale * i, y });
		sprite[spriteIndex]->SetTextureRect({ (float)fontIndexX * fontWidth, (float)fontIndexY * fontHeight }

		, { (float)fontWidth ,(float)fontHeight });
		sprite[spriteIndex]->SetSize({ fontWidth * scale, fontHeight * scale });
		// �������P�i�߂�
		spriteIndex++;
	}
}


void DebugText::Printf(float x, float y, float scale, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int w = vsnprintf(buffer, bufferSize - 1, fmt, args);
	Print(w, buffer, x, y, scale);
	va_end(args);
}

// �܂Ƃ߂ĕ`��
void DebugText::DrawAll(ID3D12GraphicsCommandList* cmdList)
{
	// �S�Ă̕����̃X�v���C�g�ɂ���
	for (int i = 0; i < spriteIndex; i++)
	{
		// �X�v���C�g�`��
		sprite[i]->Draw();
	}

	spriteIndex = 0;
}
