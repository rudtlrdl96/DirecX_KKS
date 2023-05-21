#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"
#include "MonsterData.h"

class BaseMonster : public BaseContentActor
{
public:
	BaseMonster();
	~BaseMonster();

	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	inline void HitMonster(ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush)
	{
		HitDir = _HitDir;
		IsHit = true;
		IsStiffen = _IsStiffen;
		IsPush = _IsPush;
	}

protected:
	std::shared_ptr<GameEngineActor> PlayerActor = nullptr;
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;

	ColorBuffer Buffer = ColorBuffer();

	std::shared_ptr<class GameEngineCollision> BodyCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkFallCol = nullptr;
	std::shared_ptr<class GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<class GameEngineCollision> FindCol = nullptr;
	std::shared_ptr<class GameEngineCollision> ChasingCol = nullptr;

	ActorViewDir Dir = ActorViewDir::Right;

	Rigidbody2D AttackRigidbody;
	Rigidbody2D HitRigidbody;
	MonsterData Data = MonsterData();

	ClassFSM<BaseMonster> MonsterFsm;
	AnimationAttackMetaData AnimColMeta_Attack;

	size_t AttackCheckFrame = 0;
	float CurPauseTime = 0.0f;
	std::map<size_t, float> AnimPauseTimes;

	float TurnCoolTime = 0.0f;
	float4 FallDir = float4::Zero;

	float IdleToWalkTime = 0.0f;
	float WalkToIdleTime = 0.0f;
	float WalkTurnTime = 0.0f;

	bool IsChasingWait = false;
	float ChasingWaitTime = 0.0f;

	float RandIdleTime = 0.0f;
	float RandWalkTime = 0.0f;


	float4 LocalWalkColPos = float4::Zero;
	float4 LocalWalkFallColPos = float4::Zero;
	float4 LocalFindColPos = float4::Zero;
	float4 LocalChasingColPos = float4::Zero;

	float4 LoadFindEffectPos = float4::Zero;

	UINT HitAnimIndex = 0;

	ActorViewDir HitDir = ActorViewDir::Right;

	bool IsHit = false;
	bool IsStiffen = false;
	bool IsPush = false;

	bool IsSpuerArmor = false;
	float HitWaitTime = 0.0f;

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

	virtual void DataLoad() = 0;
	virtual void TextureLoad() = 0;
	virtual void LoadAnimation() = 0;
	virtual void AnimationAttackMetaDataLoad() = 0;
	virtual void SetColData() = 0;

	void SetViewDir(ActorViewDir _Dir, bool _Force = false);
	std::shared_ptr<class GameEngineCollision> PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf = false);
private:
	bool Walk(float _DeltaTime);
	bool Fall(float _DeltaTime);
	void Turn(bool _Force = false);
	void CreateColDebugRender();
	void EffectLoadCheck();

	bool HitCheck();
	void HitEffect();
	void HitStiffen();
};

