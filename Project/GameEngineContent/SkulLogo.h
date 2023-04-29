#pragma once
#include "BaseContentActor.h"

class SkulLogo : public BaseContentActor
{
public:
	SkulLogo();
	~SkulLogo();

	SkulLogo(const SkulLogo& _Other) = delete;
	SkulLogo(SkulLogo&& _Other) noexcept = delete;
	SkulLogo& operator=(const SkulLogo& _Other) = delete;
	SkulLogo& operator=(SkulLogo&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> TextureRenderer = nullptr;


};

