#pragma once
#include "GameEngineResource.h"

class GameEngineBlend : public GameEngineResource<GameEngineBlend>
{
public:
	GameEngineBlend();
	~GameEngineBlend();

	GameEngineBlend(const GameEngineBlend& _Other) = delete;
	GameEngineBlend(GameEngineBlend&& _Other) noexcept = delete;
	GameEngineBlend& operator=(const GameEngineBlend& _Other) = delete;
	GameEngineBlend& operator=(GameEngineBlend&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(const std::string_view& _Name, const D3D11_BLEND_DESC& _Desc)
	{
		std::shared_ptr<GameEngineBlend> Res = GameEngineResource::Create(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting() override;

protected:
	void ResCreate(const D3D11_BLEND_DESC& _Value);

private:
	D3D11_BLEND_DESC Desc = {};

	ID3D11BlendState* State = nullptr;

	UINT Mask = 0xFFFFFFFF;

};

