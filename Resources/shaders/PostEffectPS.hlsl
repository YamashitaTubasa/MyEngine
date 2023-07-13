#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
  
    return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(VSOutput input) : SV_TARGET
{
    //float luminance = 1.0f; // �P�x
    //float totalWeight = 0;
    //float _Sigma = 0.005;
    //float _StepWidth = 0.001;

    //float4 col = tex.Sample(smp, input.uv) * color;

    //if (isBlur == true)
    //{
    //    for (float py = -_Sigma * 2; py <= _Sigma * 2; py += _StepWidth)
    //    {
    //        for (float px = -_Sigma * 2; px <= _Sigma * 2; px += _StepWidth)
    //        {
    //            float2 pickUV = input.uv + float2(px, py);
    //            float weight = Gaussian(input.uv, pickUV, _Sigma);
    //            col += tex.Sample(smp, pickUV) * weight;
    //            totalWeight += weight;
    //        }
    //    }
    //    col.rgb /= totalWeight;
    //    col.a = 1;
    //}

    //return float4(col.rgb * luminance, alpha);

    // �F���]
    //float4 col = tex.Sample(smp, input.uv);

    //return float4(1 - col.rgb, 1);

    // ���ςڂ���
    float4 texcolor = tex.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // �P�x
    float setU = 4.0f / 1280.0f;
    float setV = 4.0f / 720.0f;

    // ����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(-setU, -setV));
    // ����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, -setV));
    // �E��s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(setU, -setV));
    // �����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(-setU, 0.0f));
    // �����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(0, 0));
    // �E��s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(setU, 0.0f));
    // �����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(-setU, setV));
    // �����s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, setV));
    // �E���s�N�Z���̐F���T���v�����O����
    texcolor += tex.Sample(smp, input.uv + float2(setU, setV));

    // ���v�F������
    texcolor /= 9.0f;
    
	// �A���t�@��1�����ďo��
	return float4(texcolor.rgb * luminance, 1);
}

