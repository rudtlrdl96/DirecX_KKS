#pragma once
#include "BaseContentActor.h"


enum class EffectDeathTrigger
{
	Time,
	AnimEnd,
};

class EffectMetaData
{
public:
	std::string SpriteName;

	float4 RenderPivot = float4::Zero;
	float4 ScaleRatio = float4::Zero;

	UINT AnimStart = 0;
	UINT AnimEnd = 0;
};

class EffectActor : public BaseContentActor
{
private:
	friend class EffectManager;


public:
	EffectActor();
	~EffectActor();

	EffectActor(const EffectActor& _Other) = delete;
	EffectActor(EffectActor&& _Other) noexcept = delete;
	EffectActor& operator=(const EffectActor& _Other) = delete;
	EffectActor& operator=(EffectActor&& _Other) noexcept = delete;

protected:
	void Update(float _DeltaTime) override;

private:
	void Init(EffectMetaData _MetaData, EffectDeathTrigger _DeathTrigger);

	float DeathTime = 0.0f;

};

