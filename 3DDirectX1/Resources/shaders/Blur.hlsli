cbuffer cbuff0 : register(b0)
{
	float4 color;
	matrix mat;
}

struct VSOutput {
	float4 svpos : SV_POSITION;	//�V�X�e���p���_���W
	float2 uv : TEXCOORD;	//uv�l
};
