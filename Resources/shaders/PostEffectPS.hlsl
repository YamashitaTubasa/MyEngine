#include "PostEffect.hlsli"

Texture2D<float4> tex0 : register(t0);
Texture2D<float4> tex1 : register(t1);
SamplerState smp : register(s0);

float Gaussian(float2 drawUV, float2 pickUV, float sigma)
{
    float d = distance(drawUV, pickUV);
  
    return exp(-(d * d) / (2 * sigma * sigma));
}

float4 main(VSOutput input) : SV_TARGET
{
    // �F���]
    float4 col0 = 1 - tex0.Sample(smp, input.uv);

    // ���ςڂ���
    float4 col1 = tex1.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // �P�x
    float setU = 3.0f / 1280.0f;
    float setV = 3.0f / 720.0f;

    // ����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(-setU, -setV));
    // ����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(0.0f, -setV));
    // �E��s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(setU, -setV));
    // �����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(-setU, 0.0f));
    // �����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(0, 0));
    // �E��s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(setU, 0.0f));
    // �����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(-setU, setV));
    // �����s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(0.0f, setV));
    // �E���s�N�Z���̐F���T���v�����O����
    col1 += tex1.Sample(smp, input.uv + float2(setU, setV));

    // ���v�F������
    col1 /= 9.0f;
    
    float4 colortex0 = col0;
    float4 colortex1 = col1;

    float4 color = colortex0;
    if(fmod(input.uv.y, 0.1f) < 0.05f){
        color = colortex1;
    }

    return float4(color.rgb, 1);
}

