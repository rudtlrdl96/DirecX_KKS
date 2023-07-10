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


cbuffer RenderBaseValue : register(b11)
{
    float4 Time;
    float4 ScreenSize;
    float4 Mouse;
}

cbuffer AtlasData : register(b1)
{
    float2 FramePos;
    float2 FrameScale;
}


OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    OutPutValue.UV.x = (_Value.UV.x * FrameScale.x) + FramePos.x;
    OutPutValue.UV.y = (_Value.UV.y * FrameScale.y) + FramePos.y;
        
    return OutPutValue;
}

cbuffer OutlineColorBuffer : register(b1)
{
    float4 OutColor;
    float4 OutlineColor;
}

Texture2D DiffuseTex : register(t0);
SamplerState SAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    
    float2 Uv = _Value.UV.xy;
    float4 Color = DiffuseTex.Sample(SAMPLER, Uv);
    
    Color.xyz += OutColor.xyz;
    Color *= OutColor.a;
    
    float2 OnePixelUV;    
    float2 TextureScale;
    DiffuseTex.GetDimensions(TextureScale.x, TextureScale.y);
    
    OnePixelUV.x = 1.0f / TextureScale.x;
    OnePixelUV.y = 1.0f / TextureScale.y;
    
    if (Color.a == 0)
    {
        float4 pixelUp = DiffuseTex.Sample(SAMPLER, Uv + float2(0, OnePixelUV.y));
        float4 pixelDown = DiffuseTex.Sample(SAMPLER, Uv - float2(0, OnePixelUV.y));
        float4 pixelRight = DiffuseTex.Sample(SAMPLER, Uv + float2(OnePixelUV.x, 0));
        float4 pixelLeft = DiffuseTex.Sample(SAMPLER, Uv - float2(OnePixelUV.x, 0));
                		 
        if (pixelUp.a != 0 || pixelDown.a != 0 || pixelRight.a != 0 || pixelLeft.a != 0)
        {
            Color = OutlineColor;
        }
    }
    
    return Color;
}