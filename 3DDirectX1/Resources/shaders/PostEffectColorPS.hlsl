#include "PostEffectColor.hlsli"

Texture2D<float4> tex0 : register(t0);	//0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1);	//1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);		//0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{
	/*float Speed = 0.2;
	float Width = 0.3;
	float power = 0.5;
	float time = 0;
	time += 1;
	float sbTime = frac(time * Speed);
	float seTime = sbTime + Width;
	float2 uv = float2(input.uv.x + sin(smoothstep(sbTime, seTime, input.uv.y) * 2 * 3.14159) * power
		, input.uv.y);*/
	float4 texcolor = tex0.Sample(smp, input.uv);
	float shift = 0.005;
	float r = tex0.Sample(smp, input.uv + float2(-shift, 0)).r;
	float g = tex0.Sample(smp, input.uv + float2(0, 0)).g;
	float b = tex0.Sample(smp, input.uv + float2(shift, 0)).b;
	float4 color = float4(r, g, b, 1);
	//float4 color = tex0.Sample(smp, uv);
	return color;
}

