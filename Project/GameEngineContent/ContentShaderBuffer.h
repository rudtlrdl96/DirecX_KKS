#pragma once

class ColorBuffer
{
public:
	float4 Color = float4::Zero;
};

class ObjectColorBuffer
{
public:
	float4 Color = float4::Zero;
	float4 LightColor = float4::One;
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
class ProgressCircleBuffer
{
public:
	float4 OutColor = float4::Zero;
	float Progress = 0.0f;
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
	float4 LightColor = float4::One;
	float4 Uv = float4::Zero;
};


class SliceBuffer
{
public:
	float4 BorderSize = float4::Zero;
	float4 RenderScale = float4::Zero;
	float4 TexturePer = float4::Zero;
};