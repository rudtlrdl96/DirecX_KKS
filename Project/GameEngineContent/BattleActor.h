#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"


enum class HitEffectType
{
	None,
	Normal,
	Skull,
	Sword,
	MinoTaurus
};

class BattleActor : public BaseContentActor
{
public:
	BattleActor();
	~BattleActor();

	BattleActor(const BattleActor& _Other) = delete;
	BattleActor(BattleActor&& _Other) noexcept = delete;
	BattleActor& operator=(const BattleActor& _Other) = delete;
	BattleActor& operator=(BattleActor&& _Other) noexcept = delete;
	
	inline float GetThornHitCoolTime() const
	{
		return ThornWaitTime;
	}

	inline void SetThornHitCoolTime(float _CoolTime)
	{
		ThornWaitTime = _CoolTime;
	}

protected:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	OutlineColorBuffer Buffer = OutlineColorBuffer();

	ActorViewDir HitDir = ActorViewDir::Right;
	Rigidbody2D BattleActorRigidbody;

	bool IsHit = false;
	bool IsHitEffectOn = false;
	bool IsHitEffectOff = false;
	bool IsPush = false;
	bool IsSuperArmor = false;
	bool IsUnPushArmor = false;
	bool IsColorEffect = false;

	float ThornWaitTime = 0.0f;

	float HitEffectProgress = 0.0f;
	float HitEffectSpeed = 7.5f;
	float HitParticleCoolTime = 0.0f;

	float ColorEffectWaitTime = 0.0f;
	float ColorEffectProgress = 0.0f;
	float ColorEffectSpeed = 0.0f;

	float4 ColorEffectStart = float4::Zero;
	float4 ColorEffectEnd = float4::Zero;

	void Start() override;
	void Update(float _DeltaTime) override;

	void HitEffect(HitEffectType _Type, bool _IsCritical);
	void HitPush();

	void ColorEffectOn(float _Speed, float _WaitTime, const float4& _StartColor, const float4& _EndColor);

private:
};

