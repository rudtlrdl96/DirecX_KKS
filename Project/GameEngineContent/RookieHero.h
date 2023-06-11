#pragma once
#include "BossMonster.h"
#include "AnimAttackCheck.h"

class RookieHero : public BossMonster
{
public:
	RookieHero();
	~RookieHero();

	RookieHero(const RookieHero& _Other) = delete;
	RookieHero(RookieHero&& _Other) noexcept = delete;
	RookieHero& operator=(const RookieHero& _Other) = delete;
	RookieHero& operator=(RookieHero&& _Other) noexcept = delete;

	void Death() override;
	void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush) override;
protected:
	std::shared_ptr<ContentSpriteRenderer> UltimateLight = nullptr;
	ColorBuffer UltimateLightBuffer = ColorBuffer();

	std::shared_ptr<ContentSpriteRenderer> UltimateFade = nullptr;
	ColorBuffer UltimateFadeBuffer = ColorBuffer();

	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> ExplosionCol = nullptr;
	std::shared_ptr<GameEngineCollision> EventCol = nullptr;
	std::shared_ptr<GameEngineCollision> Battle_Platform_Left = nullptr;
	std::shared_ptr<GameEngineCollision> Battle_Platform_Right = nullptr;

	bool IsPlayerEnter = false;	
	UINT PatternIndex = 0;

	bool ComboDashCheck = false;
	AnimAttackCheck AttackCheck;
	AnimationAttackMetaData AttackA_Data;
	AnimationAttackMetaData AttackB_Data;
	AnimationAttackMetaData AttackD_Data;

	UINT ComboAttackIndex = 0;

	std::shared_ptr<class RookieHero_HealthBar> HeroHealthBar = nullptr;
	std::shared_ptr<class HealthBar> HealthBarPtr = nullptr;
	float4 HealthBarScale = float4(1.3f, 1.3f, 1.0f, 1.0f);

	float HealthBarActiveTime = 0.0f;

	// 패턴 변수

	float PotionTime = 0.0f;
	float PotionHealTime = 0.0f;
	float UltimateTime = 0.0f;

	bool IsEnergyBallShot = false;

	std::shared_ptr<EffectActor> ExplosionEffect = nullptr;

	bool IsExplosionAttackEnd = false;
	bool IsExplosion = false;
	bool IsExplosionEffect = false;
	float ExplosionTime = 0.0f;

	bool IsUltimateShotReady = false;
	bool IsUltimateShot = false;
	float UltimateLiveTime = 0.0f;

	float UltimateLightProgress = 0.0f;
	float UltimateFadeProgress = 0.0f;

	bool IsUltimateLightOn = false;
	bool IsUltimateLightOff = false;
	bool IsUltimateFadeOn = false;

	void Start() override;
	void Update(float _DeltaTime) override;
	 
	void DataLoad() override;
	void CreateAnimation() override;

	void SelectPattern() override;

	void ComboAttack_Enter();
	void ComboAttack_Update(float _DeltaTime);
	void ComboAttack_End();

	void EnergyBall_Enter();
	void EnergyBall_Update(float _DeltaTime);
	void EnergyBall_End();

	void Potion_Enter();
	void Potion_Update(float _DeltaTime);
	void Potion_End();

	void Explosion_Enter();
	void Explosion_Update(float _DeltaTime);
	void Explosion_End();

	void Ultimate_Enter();
	void Ultimate_Update(float _DeltaTime);
	void Ultimate_End();

	void UltimateLightOn();
	void UltimateLightOff();

	void UltimateFadeOn();
};

