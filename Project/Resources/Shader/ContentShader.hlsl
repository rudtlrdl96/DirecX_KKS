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
    float4 Color : COLOR;
};

struct OutPut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.Color = _Value.Color;
	
    return OutPutValue;
}

struct OutPixelData
{
    float4 OutColor;
};

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    OutPixelData PixelData = (OutPixelData)0;
    PixelData.OutColor = (float4)0;
    
    PixelData.OutColor.x = abs(sin(_Value.Pos.x * 0.1f));
    PixelData.OutColor.y = abs(cos(_Value.Pos.y * 0.1f));
    //PixelData.OutColor.z = abs(cos(_Value.Pos.x * 0.1f));
    
    return PixelData.OutColor;
}