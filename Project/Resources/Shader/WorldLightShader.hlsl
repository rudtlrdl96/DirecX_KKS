struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    return OutPutValue;
}


cbuffer ColorData : register(b1)
{
    float4 LightColor;
}


Texture2D DiffuseTex : register(t0);
SamplerState SAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(SAMPLER, _Value.UV.xy);
    Color *= LightColor;
    
    return Color;
}