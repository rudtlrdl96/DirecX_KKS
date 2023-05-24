#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class BattleActor : public BaseContentActor
{
public:
	BattleActor();
	~BattleActor();

	BattleActor(const BattleActor& _Other) = delete;
	BattleActor(BattleActor&& _Other) noexcept = delete;
	BattleActor& operator=(const BattleActor& _Other) = delete;
	BattleActor& operator=(BattleActor&& _Other) noexcept = delete;

protected:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	OutlineColorBuffer Buffer = OutlineColorBuffer();

	ActorViewDir HitDir = ActorViewDir::Right;
	Rigidbody2D HitRigidbody;

	bool IsHit = false;
	bool IsHitEffectOn = false;
	bool IsPush = false;

	float HitEffectProgress = 0.0f;
	float HitEffectSpeed = 7.5f;
	float HitParticleCoolTime = 0.0f;

	void Start() override;
	void Update(float _DeltaTime) override;

	void HitEffect();
	void HitStiffen();
private:

};

