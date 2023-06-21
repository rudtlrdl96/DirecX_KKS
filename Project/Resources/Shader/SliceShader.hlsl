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
    float4 UV : TEXCOORD;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    return OutPutValue;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

cbuffer SliceBuffer : register(b1)
{
    float4 TextureScale;
    float4 Clip;
}

cbuffer PixelScaleBuffer : register(b2)
{
    float4 BufferWorldScale;
}

float map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}

float process_axis(float coord, float pixel, float texture_pixel, float start, float end)
{
    if (coord > 1.0 - end * pixel)
    {
        return map(coord, 1.0 - end * pixel, 1.0, 1.0 - texture_pixel * end, 1.0);
    }
    else if (coord > start * pixel)
    {
        return map(coord, start * pixel, 1.0 - end * pixel, start * texture_pixel, 1.0 - end * texture_pixel);
    }
    else
    {
        return map(coord, 0.0, start * pixel, 0.0, start * texture_pixel);
    }
}

float4 Texture_PS(OutPut _Value) : SV_Target0
{         
    float2 pixel_size = TextureScale.xy / BufferWorldScale.xy;    
    float2 mappedUV = float2(
		process_axis(_Value.UV.x, pixel_size.x, TextureScale.x, float(Clip.x), float(Clip.y)),
		process_axis(_Value.UV.y, pixel_size.y, TextureScale.y, float(Clip.z), float(Clip.w))
	);
    
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, mappedUV);
    return Color;
}