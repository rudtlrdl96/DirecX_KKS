#pragma once
#include <GameEngineCore/GameEngineVertex.h>

class ContentVertex
{
public:
	static GameEngineInputLayOutInfo LayOut;

public:
	float4 POSITION; // 0 16
	float4 UV;    // 16 32
	float4 NORMAL; // 0 16
};