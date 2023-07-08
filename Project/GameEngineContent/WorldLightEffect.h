#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

class WorldLightEffect : public GameEnginePostProcess
{
public:
	WorldLightEffect();
	~WorldLightEffect();

	WorldLightEffect(const WorldLightEffect& _Other) = delete;
	WorldLightEffect(WorldLightEffect&& _Other) noexcept = delete;
	WorldLightEffect& operator=(const WorldLightEffect& _Other) = delete;
	WorldLightEffect& operator=(WorldLightEffect&& _Other) noexcept = delete;

	float4 WorldLight = float4::One;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderUnit> LightUnit;

};

