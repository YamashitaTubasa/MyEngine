//float4 main() : SV_TARGET
//{
//	return float4(0.5f, 0.55f, 0.5f, 1.0f);
//}
//cbuffer ConstBufferDataMaterial : register(b0)
//{
//    float4 color; // êF(RGBA)
//};
//float4 main() : SV_TARGET
//{
//    return color;
//}
#include "Basic.hlsli"

float4 main(VSOutput input) : SV_TARGET
{
    return float4(input.uv, 0, 1);
}