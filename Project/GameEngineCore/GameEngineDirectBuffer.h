#pragma once
#include "GameEngineResource.h"

class GameEngineDirectBuffer
{
public:
	GameEngineDirectBuffer();
	~GameEngineDirectBuffer();

	GameEngineDirectBuffer(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&& _Other) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer& _Other) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&& _Other) noexcept = delete;

public:
	UINT GetBufferSize() 
	{
		return BufferInfo.ByteWidth;
	}

protected:
	D3D11_BUFFER_DESC BufferInfo = {0,};
	ID3D11Buffer* Buffer = nullptr;

private:
};

