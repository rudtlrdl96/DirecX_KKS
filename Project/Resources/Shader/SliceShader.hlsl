cbuffer TransformData : register(b0)
{
    float4 Scale;
    float4 Rotation;
    float4 Quaternion;
    float4 Position;

    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;

    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;

    float4x4 ScaleMatrix;
    float4x4 RotationMatrix;
    float4x4 PositionMatrix;
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
    float4 TexCoord : TEXCOORD;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.TexCoord = _Value.UV;
    
    return OutPutValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}


cbuffer SliceBuffer : register(b1)
{
    float4 BorderSize; 
    float4 RenderScale;
    float4 TexturePer;
}

float4 Texture_PS(OutPut input) : SV_Target
{        
    float2 TextureScale;
    DiffuseTex.GetDimensions(TextureScale.x, TextureScale.y);
    
    TextureScale *= TexturePer.xy;
    
    float2 UVScale = (RenderScale.xy / TextureScale);
    float2 WorldUV = input.TexCoord.xy * UVScale;
    
    if (BorderSize.x >= WorldUV.x)
    {
        WorldUV.x = WorldUV.x;
    }
    else if (UVScale.x - BorderSize.y <= WorldUV.x)
    {
        WorldUV.x = 1.0f - (UVScale.x - WorldUV.x);
    }
    else
    {
        WorldUV.x = map(WorldUV.x, BorderSize.x, UVScale.x - BorderSize.y, BorderSize.x, 1.0f - BorderSize.y);
    }
    
    if (BorderSize.z >= WorldUV.y)
    {
        WorldUV.y = WorldUV.y;
    }
    else if (UVScale.y - BorderSize.w <= WorldUV.y)
    {
        WorldUV.y = 1.0f - (UVScale.y - WorldUV.y);
    }
    else
    {
        WorldUV.y = map(WorldUV.y, BorderSize.z, UVScale.y - BorderSize.w, BorderSize.z, 1.0f - BorderSize.w);
    }
    
    
    float4 OutColor = DiffuseTex.Sample(WRAPSAMPLER, WorldUV);    
    return OutColor;
}