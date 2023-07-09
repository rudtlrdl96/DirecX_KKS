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

cbuffer RenderBaseValue : register(b11)
{
    float4 Time;
    float4 ScreenSize;
    float4 Mouse;
}

cbuffer ColorData : register(b1)
{
    float4 LightPos;
    float4 LightColor;
        
    /// <param name="x"> Brightness 라이트의 밝기를 설정합니다</param>
    /// <param name="y"> Distance 라이트의 길이를 설정합니다</param>
    float4 LightOption;
}

Texture2D DiffuseTex : register(t0);
SamplerState SAMPLER : register(s0);

float map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float2 Uv = _Value.UV.xy;
    float4 Color = DiffuseTex.Sample(SAMPLER, Uv);
    
    float2 UvScreenPos;
    
    UvScreenPos.x = ScreenSize.x * Uv.x;
    UvScreenPos.y = ScreenSize.y * Uv.y;
        
    float2 LightDir = UvScreenPos - LightPos.xy;       
    float Distance = sqrt((LightDir.x * LightDir.x) + (LightDir.y * LightDir.y));
            
    
    if (Distance < LightOption.y)
    {
        float2 DotDir = float2(0, -1);    
                
        if (LightDir.x < 0)
        {
            LightDir.y = -LightDir.y;
        }
        
        float DotCos = acos(dot(DotDir, normalize(LightDir)));
        
        if (LightDir.x < 0)
        {
            DotCos += 3.14f;
        }      
        
        if (LightOption.z <= DotCos && LightOption.w >= DotCos)
        {
            float LightValue = map(DotCos, LightOption.z, LightOption.w, -1.0f, 1.0f);
            
            float4 DistanceColor = float4(1, 1, 1, 1) + (LightColor * LightOption.x * (1.0f - abs(LightValue)));
            DistanceColor.a = 1.0f;        
            Color *= DistanceColor;
        }
    }
    
    return Color;
}