#pragma once
#include "BaseMonster.h"

class NormalMonster : public BaseMonster
{
public:
	NormalMonster();
	~NormalMonster();

	NormalMonster(const NormalMonster& _Other) = delete;
	NormalMonster(NormalMonster&& _Other) noexcept = delete;
	NormalMonster& operator=(const NormalMonster& _Other) = delete;
	NormalMonster& operator=(NormalMonster&& _Other) noexcept = delete;

	void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush) override;
protected:
	std::shared_ptr<EffectActor> AppearEffect = nullptr;
	bool IsAppear = false;

	std::shared_ptr<class HealthBar> HealthBarPtr = nullptr;
	float4 HealthBarScale = float4(1.0f, 1.5f, 1.5f, 1.0f);

	float HealthBarActiveTime = 0.0f;

	void Start() override;
	void Update(float _DeltaTime) override;

private:


};

