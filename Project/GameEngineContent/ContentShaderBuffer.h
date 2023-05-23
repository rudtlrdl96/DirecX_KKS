#pragma once

class ColorBuffer
{
public:
	float4 Color = float4::Zero;
	float4 OutlineColor = float4::Null;
};

class CaptureBuffer
{
public:
	float4 Color = float4::Zero;
};

class FadeBuffer
{
public:
	float4 Color = float4::Zero;
};

class TextureMoveBuffer
{
public:    
	float4 OutColor = float4::Zero;
	float4 Uv = float4::Zero;
};

