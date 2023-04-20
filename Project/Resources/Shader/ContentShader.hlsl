cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

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
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV = _Value.UV;
    	
    return OutPutValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 PixelData = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    float2 CenterUv = _Value.UV.xy;
    
    CenterUv.x -= 0.5f;
    CenterUv.y -= 0.5f;
    CenterUv *= 2.0f;
        
    float CenterDis = 1.0f - sqrt(CenterUv.x * CenterUv.x + CenterUv.y * CenterUv.y);
    float TestLight = CenterDis;
    
    if (TestLight <= 0.0f)
    {
        clip(-1);
    }
    
    PixelData *= TestLight;
    
    return PixelData;
}