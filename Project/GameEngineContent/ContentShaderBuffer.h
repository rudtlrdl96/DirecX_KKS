#pragma once

class ColorBuffer
{
public:
	float4 Color = float4::Zero;
};

class OutlineColorBuffer
{
public:
	float4 Color = float4::Zero;
	float4 OutlineColor = float4::Null;
};

class ProgressBuffer
{
public:
	float4 OutColor = float4::Zero;
	float4 ColorProgress = float4(0, 0, 1, 1);
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

