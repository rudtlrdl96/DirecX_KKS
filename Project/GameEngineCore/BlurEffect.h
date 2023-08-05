#pragma once
#include "GameEngineRenderTarget.h"

class BlurEffect : public GameEnginePostProcess
{
public:
	BlurEffect();
	~BlurEffect();

	BlurEffect(const BlurEffect& _Other) = delete;
	BlurEffect(BlurEffect&& _Other) noexcept = delete;
	BlurEffect& operator=(const BlurEffect& _Other) = delete;
	BlurEffect& operator=(BlurEffect&& _Other) noexcept = delete;

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineRenderUnit> BlurUnit;
};

