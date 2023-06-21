// 쉐이더를 짜게되면 다음의 규칙을 지켜야 한다.

// 0~ 16번 슬롯 
// 선언해 놨다고 쓰는게 아니에요.
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
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
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

cbuffer Slice9Buffer : register(b1)
{ 
    float4 TextureScale;
    
    float Left;
    float Right;
    float Top;
    float Bottom;
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{         
    float2 Uv = _Value.UV;
    float2 pixel_size = TextureScale.xy / WorldScale.xy;
	
    float2 mappedUV = float2(
		process_axis(Uv.x, pixel_size.x, TextureScale.x, Left, Right),
		process_axis(Uv.y, pixel_size.y, TextureScale.y, Top, Bottom));
        
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, Uv);
    return Color;
}

