cbuffer cbuff0 : register(b0)
{
	float4 color; // �F
	matrix mat;   // �s��
	bool isBlur;  // �t���O
	float alpha;  // �A���t�@�l
};

// ���_�V�F�[�_�[����̏o�͍\����
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};