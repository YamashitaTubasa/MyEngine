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
    // 色反転
    float4 col0 = 1 - tex0.Sample(smp, input.uv);

    // 平均ぼかし
    float4 col1 = tex1.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // 輝度
    float setU = 3.0f / 1280.0f;
    float setV = 3.0f / 720.0f;

    // 左上ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(-setU, -setV));
    // 中上ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(0.0f, -setV));
    // 右上ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(setU, -setV));
    // 左中ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(-setU, 0.0f));
    // 中央ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(0, 0));
    // 右上ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(setU, 0.0f));
    // 左下ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(-setU, setV));
    // 中下ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(0.0f, setV));
    // 右下ピクセルの色をサンプリングする
    col1 += tex1.Sample(smp, input.uv + float2(setU, setV));

    // 合計色を割る
    col1 /= 9.0f;
    
    float4 colortex0 = col0;
    float4 colortex1 = col1;

    float4 color = colortex0;
    if(fmod(input.uv.y, 0.1f) < 0.05f){
        color = colortex1;
    }

    return float4(color.rgb, 1);
}

