#pragma once
#include "BattleActor.h"
#include "Rigidbody2D.h"
#include "MonsterData.h"

class BaseMonster : public BattleActor
{
public:
	BaseMonster();
	~BaseMonster();

	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	void HitMonster(ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush);

	std::shared_ptr<ContentSpriteRenderer> GetRender()
	{
		return Render;
	}

	void ChangeFSM(const std::string_view& _FsmName)
	{
		MonsterFsm.ChangeState(_FsmName);
	}

	inline void FadeOn()
	{
		Buffer.Color.a = 0.0f;
	}

	inline void FadeOff()
	{
		Buffer.Color.a = 1.0f;
	}

protected:
	std::shared_ptr<GameEngineActor> PlayerActor = nullptr;

	std::shared_ptr<class GameEngineCollision> BodyCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<class GameEngineCollision> BackCol = nullptr;
	std::shared_ptr<class GameEngineCollision> WalkFallCol = nullptr;
	std::shared_ptr<class GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<class GameEngineCollision> FindCol = nullptr;
	std::shared_ptr<class GameEngineCollision> ChasingCol = nullptr;

	ActorViewDir Dir = ActorViewDir::Right;

	Rigidbody2D AttackRigidbody;
	MonsterData Data = MonsterData();

	float HP = 0;

	ClassFSM<BaseMonster> MonsterFsm;
	AnimationAttackMetaData AnimColMeta_Attack;

	size_t AttackCheckFrame = 0;
	std::map<size_t, float> AnimPauseTimes;

	float CurPauseTime = 0.0f;
	float AttackWaitTime = 1000.0f;
	float AttackWaitEndTime = 0.0f;

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
	float4 LocalBackColPos = float4::Zero;

	float4 LocalWalkFallColPos = float4::Zero;
	float4 LocalFindColPos = float4::Zero;
	float4 LocalChasingColPos = float4::Zero;

	float4 LoadFindEffectPos = float4::Zero;

	UINT HitAnimIndex = 0;

	bool IsSuperArmor = false;
	bool IsStiffen = false;

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
	
	bool Walk(float _DeltaTime);
	bool Fall(float _DeltaTime);
	void Turn(bool _Force = false);
	void CreateColDebugRender();
	void EffectLoadCheck();

	bool HitCheck();
};

