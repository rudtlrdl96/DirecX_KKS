#pragma once
#include "BossMonster.h"
#include "AnimAttackCheck.h"

class VeteranHero : public BossMonster
{
public:
	VeteranHero();
	~VeteranHero();

	VeteranHero(const VeteranHero& _Other) = delete;
	VeteranHero(VeteranHero&& _Other) noexcept = delete;
	VeteranHero& operator=(const VeteranHero& _Other) = delete;
	VeteranHero& operator=(VeteranHero&& _Other) noexcept = delete;

	void Destroy() override;
	void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush) override;
protected:
	std::shared_ptr<ContentSpriteRenderer> UltimateLight = nullptr;
	ColorBuffer UltimateLightBuffer = ColorBuffer();

	std::shared_ptr<ContentSpriteRenderer> UltimateFade = nullptr;
	ColorBuffer UltimateFadeBuffer = ColorBuffer();

	std::shared_ptr<GameEngineCollision> AttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> ExplosionCol = nullptr;
	std::shared_ptr<GameEngineCollision> ExplosionChargeCol = nullptr;
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

	std::shared_ptr<class VeteranHero_HealthBar> HeroHealthBar = nullptr;
	std::shared_ptr<class HealthBar> HealthBarPtr = nullptr;
	float4 HealthBarScale = float4(1.3f, 1.3f, 1.0f, 1.0f);

	float HealthBarActiveTime = 0.0f;

	// 인트로 변수
	bool IsIntroJump = false;
	bool IsSwordThrowing = false;

	Rigidbody2D SwordRigidbody;
	std::shared_ptr<ContentSpriteRenderer> SwordRender = nullptr;
	ColorBuffer SwordBuffer;

	// 패턴 변수
	float UltimateTime = 0.0f;

	bool IsEnergyBallShot = false;

	std::shared_ptr<EffectActor> ExplosionEffect = nullptr;

	bool IsExplosionAttackEnd = false;
	bool IsExplosion = false;
	bool IsExplosionEffect = false;
	bool IsExplosionChargeEffect = false;

	float4 ExplosionChargeScaleStart = float4::One;
	float4 ExplosionChargeScaleEnd = float4::One;
	float ExplosionChargeProgress = 0.0f;

	float PlayerChargeHitTime = 0.0f;
	float ExplosionTime = 0.0f;

	bool IsUltimateComplete = false;
	bool IsUltimateShotReady = false;
	bool IsUltimateShot = false;
	float UltimateLiveTime = 0.0f;

	float UltimateLightProgress = 0.0f;
	float UltimateFadeProgress = 0.0f;

	bool IsUltimateLightOn = false;
	bool IsUltimateLightOff = false;
	bool IsUltimateFadeOn = false;

	std::shared_ptr<EffectActor> UltimateSmokeEffect = nullptr;
	std::shared_ptr<EffectActor> UltimateAuraEffect = nullptr;

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

	void EnergyBallReady(float _Rot);
	void EnergyBallShot(float _Rot, float _LiveTime);

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

