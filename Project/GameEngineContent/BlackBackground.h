#pragma once
#include "BaseContentActor.h"

class BlackBackground : public BaseContentActor
{
public:
	BlackBackground();
	~BlackBackground();

	BlackBackground(const BlackBackground& _Other) = delete;
	BlackBackground(BlackBackground&& _Other) noexcept = delete;
	BlackBackground& operator=(const BlackBackground& _Other) = delete;
	BlackBackground& operator=(BlackBackground&& _Other) noexcept = delete;

	void SetRenderSize(const float4& _Size);

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> TextureRenderer = nullptr;

};

