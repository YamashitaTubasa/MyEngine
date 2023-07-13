cbuffer cbuff0 : register(b0)
{
	float4 color; // 色
	matrix mat;   // 行列
	bool isBlur;  // フラグ
	float alpha;  // アルファ値
};

// 頂点シェーダーからの出力構造体
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};