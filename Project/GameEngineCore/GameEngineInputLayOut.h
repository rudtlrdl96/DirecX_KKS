#pragma once
#include "GameEngineResource.h"

class GameEngineInputLayOut : public GameEngineResource<GameEngineInputLayOut>
{
public:
	GameEngineInputLayOut();
	~GameEngineInputLayOut();

	GameEngineInputLayOut(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut(GameEngineInputLayOut&& _Other) noexcept = delete;
	GameEngineInputLayOut& operator=(const GameEngineInputLayOut& _Other) = delete;
	GameEngineInputLayOut& operator=(GameEngineInputLayOut&& _Other) noexcept = delete;

	void Relase();
	void ResCreate(std::shared_ptr<class GameEngineVertexBuffer> _Info, std::shared_ptr<class GameEngineVertexShader> _Shader);
	void Setting() override;

	bool IsCreate() 
	{
		return nullptr != InputLayOut;
	}

protected:

private:
	ID3D11InputLayout* InputLayOut = nullptr;

};

