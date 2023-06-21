//マテリアル
cbuffer ConstBufferDataMaterial : register(b0)
{
    float4 color;// 色(RGBA)
};
cbuffer ConstBufferDataMaterial : register(b1)
{
    matrix mat;// 3D変換行列
};
// 頂点シェーダーの出力構造体
// (頂点シェーダーからピクセルシェーダーへのやり取りに使用する）
struct VSOutput
{
    float4 svpos : SV_POSITION; // システム用頂点座標
    float3 normal : NORMAL;     // 法線ベクトル
    float2 uv  :TEXCOORD;       // uv値
};