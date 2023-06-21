#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class BattleActorDamageFontParameter
{
public:
	float Damage = 0.0f;

	float FontSize = 16.0f;
	float4 FontColor = float4::Zero;

	const float4& Pos = float4::Zero;
	const float4& Dir = float4::Zero;

	float MoveSpeed = 0.0f;

	float RandX = 0.0f;
	float RandY = 0.0f;

	float LiveTime = 1.0f;
};


class BattleActorDamageFont : public BaseContentActor
{
public:
	BattleActorDamageFont();
	~BattleActorDamageFont();

	BattleActorDamageFont(const BattleActorDamageFont& _Other) = delete;
	BattleActorDamageFont(BattleActorDamageFont&& _Other) noexcept = delete;
	BattleActorDamageFont& operator=(const BattleActorDamageFont& _Other) = delete;
	BattleActorDamageFont& operator=(BattleActorDamageFont&& _Other) noexcept = delete;

	void InitFont(const BattleActorDamageFontParameter& _Parameter);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineFontRenderer> DamageFont = nullptr;

	Rigidbody2D FontRigid;

	float LiveTime = -1.0f;
};

