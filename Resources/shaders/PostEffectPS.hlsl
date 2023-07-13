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
    //float luminance = 1.0f; // 輝度
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

    // 色反転
    //float4 col = tex.Sample(smp, input.uv);

    //return float4(1 - col.rgb, 1);

    // 平均ぼかし
    float4 texcolor = tex.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // 輝度
    float setU = 4.0f / 1280.0f;
    float setV = 4.0f / 720.0f;

    // 左上ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(-setU, -setV));
    // 中上ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, -setV));
    // 右上ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(setU, -setV));
    // 左中ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(-setU, 0.0f));
    // 中央ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(0, 0));
    // 右上ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(setU, 0.0f));
    // 左下ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(-setU, setV));
    // 中下ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(0.0f, setV));
    // 右下ピクセルの色をサンプリングする
    texcolor += tex.Sample(smp, input.uv + float2(setU, setV));

    // 合計色を割る
    texcolor /= 9.0f;
    
	// アルファに1を入れて出力
	return float4(texcolor.rgb * luminance, 1);
}

