#pragma once
#include "BaseContentActor.h"

enum class DeubgColType
{
	Box,
	Sphere
};

class DebugCollisionRender : public BaseContentActor
{
public:
	DebugCollisionRender();
	~DebugCollisionRender();

	DebugCollisionRender(const DebugCollisionRender& _Other) = delete;
	DebugCollisionRender(DebugCollisionRender&& _Other) noexcept = delete;
	DebugCollisionRender& operator=(const DebugCollisionRender& _Other) = delete;
	DebugCollisionRender& operator=(DebugCollisionRender&& _Other) noexcept = delete;

	inline void SetColType(DeubgColType _Type)
	{
		Type = _Type;
	}

	inline void SetSize(const float4& _Size)
	{
		Size = _Size;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	DeubgColType Type = DeubgColType::Box;
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	float4 Size = float4::One;
};

