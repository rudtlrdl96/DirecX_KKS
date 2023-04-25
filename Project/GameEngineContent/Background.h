#pragma once
#include "BaseContentActor.h"

class Background : public BaseContentActor
{
public:
	Background();
	~Background();

	Background(const Background& _Other) = delete;
	Background(Background&& _Other) noexcept = delete;
	Background& operator=(const Background& _Other) = delete;
	Background& operator=(Background&& _Other) noexcept = delete;
	
protected:
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> BackImage = nullptr;

	float4 Center = float4::Zero;
	float DistanceRatio = 1.0f;
};