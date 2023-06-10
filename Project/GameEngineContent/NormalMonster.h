#pragma once
#include "BaseMonster.h"

class NormalMonster : public BaseMonster
{
	friend class FlameWizard;
public:
	NormalMonster();
	~NormalMonster();

	NormalMonster(const NormalMonster& _Other) = delete;
	NormalMonster(NormalMonster&& _Other) noexcept = delete;
	NormalMonster& operator=(const NormalMonster& _Other) = delete;
	NormalMonster& operator=(NormalMonster&& _Other) noexcept = delete;

	void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush) override;

	void ChangeFSM(const std::string_view& _FsmName)
	{
		MonsterFsm.ChangeState(_FsmName);
	}

protected:
	std::shared_ptr<EffectActor> AppearEffect = nullptr;
	bool IsAppear = false;

	std::shared_ptr<class HealthBar> HealthBarPtr = nullptr;
	float4 HealthBarScale = float4(1.0f, 1.5f, 1.5f, 1.0f);

	float HealthBarActiveTime = 0.0f;

	std::vector<std::string> DeadPartNames;

	std::shared_ptr<GameEngineActor> PlayerActor = nullptr;

	std::shared_ptr<class GameEngineCollision> HitFindCol = nullptr;
	std::shared_ptr<class GameEngineCollision> BodyCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<class GameEngineCollision> BackCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkFallCol = nullptr;
	std::shared_ptr<class GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<class GameEngineCollision> FindCol = nullptr;
	std::shared_ptr<class GameEngineCollision> ChasingCol = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCol = nullptr;

	Rigidbody2D AttackRigidbody;

	AnimAttackCheck AttackCheck;

	ClassFSM<NormalMonster> MonsterFsm;
	AnimationAttackMetaData AnimColMeta_Attack;

	size_t AttackCheckFrame = 0;
	std::map<size_t, float> AnimPauseTimes;

	float CurPauseTime = 0.0f;
	float AttackWaitTime = 1000.0f;
	float AttackWaitEndTime = 0.0f;
	float AttakPushRatio = 1.0f;

	float TurnCoolTime = 0.0f;
	float4 FallDir = float4::Zero;

	float IdleToWalkTime = 0.0f;
	float WalkToIdleTime = 0.0f;
	float WalkTurnTime = 0.0f;

	bool IsChasingWait = false;
	float ChasingWaitTime = 0.0f;

	float RandIdleTime = 0.0f;
	float RandWalkTime = 0.0f;

	float4 DeathEffectLocalPos = float4::Zero;
	float DeathPartScale = 2.0f;

	float4 LocalWalkColPos = float4::Zero;
	float4 LocalBackColPos = float4::Zero;

	float4 LocalWalkFallColPos = float4::Zero;
	float4 LocalFindColPos = float4::Zero;
	float4 LocalChasingColPos = float4::Zero;

	float4 LoadFindEffectPos = float4::Zero;

	UINT HitAnimIndex = 0;

	bool IsUnWalkable = false;

	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void Idle_Enter();
	virtual void Idle_Update(float _DeltaTime);
	virtual void Idle_End();

	virtual void Walk_Enter();
	virtual void Walk_Update(float _DeltaTime);
	virtual void Walk_End();

	virtual void Chasing_Enter();
	virtual void Chasing_Update(float _DeltaTime);
	virtual void Chasing_End();

	virtual void Attack_Enter();
	virtual void Attack_Update(float _DeltaTime);
	virtual void Attack_End();

	virtual void Hit_Enter();
	virtual void Hit_Update(float _DeltaTime);
	virtual void Hit_End();

	virtual void TextureLoad() = 0;
	virtual void LoadAnimation() = 0;
	virtual void AnimationAttackMetaDataLoad() = 0;
	virtual void SetColData() = 0;
	virtual void DeathPartLoad() {}

	bool Walk(float _DeltaTime);
	bool Fall(float _DeltaTime);
	void Turn(bool _Force = false);
	void CreateColDebugRender(bool _IsActive);
	void EffectLoadCheck();
	void SetViewDir(ActorViewDir _Dir, bool _Force = false) override;

	bool HitCheck();
	virtual void MonsterDeath();



private:


};

