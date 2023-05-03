#pragma once

class ColorBuffer
{
public:
	float4 Color = float4::Zero;
	float4 WorldLight = float4::Zero;
};

class CaptureBuffer
{
public:
	float4 Color = float4::Zero;
	float4 WorldLight = float4::Zero;
};

class TextureMoveBuffer
{
public:    
	float4 OutColor = float4::Zero;
	float4 WorldLight = float4::Zero;
	float4 Uv = float4::Zero;
};

