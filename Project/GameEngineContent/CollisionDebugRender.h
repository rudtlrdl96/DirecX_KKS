#pragma once
#include "BaseContentActor.h"
#include <GameEngineCore/GameEngineCollision.h>

class CollisionDebugRender : public BaseContentActor
{
public:
	enum class DebugColor
	{
		Green,
		Blue,
		Red,		
	};

public:
	CollisionDebugRender();
	~CollisionDebugRender();

	CollisionDebugRender(const CollisionDebugRender& _Other) = delete;
	CollisionDebugRender(CollisionDebugRender&& _Other) noexcept = delete;
	CollisionDebugRender& operator=(const CollisionDebugRender& _Other) = delete;
	CollisionDebugRender& operator=(CollisionDebugRender&& _Other) noexcept = delete;

	inline void SetColor(DebugColor _Color)
	{
		Color = _Color;
	}

	inline void SetColorCallback(std::function<DebugColor()> _Callback)
	{
		UpdateColorCallback = _Callback;
	}

	void SetTargetCollision(std::shared_ptr<GameEngineCollision> _TargetCollision);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<ContentSpriteRenderer> DebugRender = nullptr;
	ColorBuffer DebugBuffer;

	std::weak_ptr<GameEngineCollision> TargetCollision;
	std::function<DebugColor()> UpdateColorCallback = nullptr;

	DebugColor Color = DebugColor::Green;
};
