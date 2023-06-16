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
	std::shared_ptr<GameEngineCollision> WaveSmokeCol  = nullptr;
	std::shared_ptr<GameEngineCollision> EventCol = nullptr;
	std::shared_ptr<GameEngineCollision> StingerAttackCol = nullptr;
	std::shared_ptr<GameEngineCollision> StingerSwordAttackCol = nullptr;

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

	// 에너지볼 패턴 변수
	bool IsEnergyBallShot = false;

	// 폭발 패턴 변수
	std::shared_ptr<EffectActor> ExplosionEffect = nullptr;

	bool IsExplosionAttackEnd = false;
	bool IsExplosion = false;
	bool IsExplosionEffect = false;
	bool IsExplosionChargeEffect = false;

	float4 ExplosionChargeScaleStart = float4::One;
	float4 ExplosionChargeScaleEnd = float4::One;
	float ExplosionChargeProgress = 0.0f;
	float ExplosionChargeDamageCoolTime = 0.0f;

	float PlayerChargeHitTime = 0.0f;
	float ExplosionTime = 0.0f;

	// 돌진패턴 변수
	float PrevRigdFricCoeff = 0.0f;
	std::shared_ptr<EffectActor> StingerEffect = nullptr;
	bool IsStingerReadyEnd = false;
	bool IsStingerEnd = false;
	bool IsStingerAttackEffect = false;

	bool IsStingerAttackHit = false;
	bool IsStingerSwordHit = false;

	// 점프공격 패턴 변수
	float PrevRigdGravity = 0.0f;

	bool IsJumpAttackStart = false;
	bool IsJumpAttackEnd = false;
	bool IsJumpAttackUp = false;

	// 스워드 웨이브 패턴 변수

	UINT SwordWaveCombo = 0;

	// 1차 각성기 패턴 변수
	std::shared_ptr<EffectActor> UltimateSmokeEffect = nullptr;
	float UltimateTime = 0.0f;
	bool IsUltimateCharge = false;
	bool IsSwordEnergyReadyStart = false;
	bool IsSwordEnergyReadyEnd = false;
	float SwordEnergyWaveTime = 0.0f;
	float SwordEnergyWaveEndTime = 0.0f;
	float4 SwordSmokePos = float4::Zero;
	ActorViewDir SmokeDir = ActorViewDir::Right;
	bool IsSwordWaveSmokeHit = false;

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

	void EnergyBallReady(float _Rot);
	void EnergyBallShot(float _Rot, float _LiveTime);

	void Explosion_Enter();
	void Explosion_Update(float _DeltaTime);
	void Explosion_End();

	void Stinger_Enter();
	void Stinger_Update(float _DeltaTime);
	void Stinger_End();
	
	void SwordWave_Enter();
	void SwordWave_Update(float _DeltaTime);
	void SwordWave_End();
	void SworWaveShot();

	void JumpAttack_Enter();
	void JumpAttack_Update(float _DeltaTime);
	void JumpAttack_End();

	void LandingAttack_Enter();
	void LandingAttack_Update(float _DeltaTime);
	void LandingAttack_End();

	void Ultimate_Enter();
	void Ultimate_Update(float _DeltaTime);
	void Ultimate_End();

	void UltimateLightOn();
	void UltimateLightOff();

	void UltimateFadeOn();
};

