#pragma once
#include "BaseMonster.h"

class BossMonster : public BaseMonster
{
public:
	BossMonster();
	~BossMonster();

	BossMonster(const BossMonster& _Other) = delete;
	BossMonster(BossMonster&& _Other) noexcept = delete;
	BossMonster& operator=(const BossMonster& _Other) = delete;
	BossMonster& operator=(BossMonster&& _Other) noexcept = delete;

protected:
	std::weak_ptr<class Player> FindPlayer;
	std::map<std::string, std::map<UINT, float>> PauseTimes;
	std::map<UINT, float>& CurAnimPause;

	UINT CurFrameIndex = static_cast<UINT>(-1);
	float CurFramePauseTime = 0.0f;

	float PatternWaitTime = 2.0f;
	float CurWaitTime = 0.0f;
	
	float GroggyTime = 4.0f;
	float CurGroggyTime = 0.0f;

	ClassFSM<BossMonster> BossFsm;
	Rigidbody2D BossRigidbody;

	std::shared_ptr<GameEngineCollision> BodyCol = nullptr;
	std::shared_ptr<GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<GameEngineCollision> BackCol = nullptr;
	std::shared_ptr<GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<GameEngineCollision> PlayerFindCol = nullptr;

	float AttackDistance = 200.0f;
	float DashPower = 1300.0f;
	float BackDashPower = 1000.0f;
	float HitPower = 400.0f;

	std::function<void()> Cur_Pattern_Enter = nullptr;
	std::function<void(float)> Cur_Pattern_Update = nullptr;
	std::function<void()> Cur_Pattern_End = nullptr;
	
	std::string PlayBehaviorAnim = "";
	std::function<void()> BehaviorEndCallback = nullptr;

	bool IsBehaviorLoop = false;
	bool IsIntro = true;

	void Start() override;
	void Update(float _DeltaTime) override;

	virtual void Idle_Enter();
	virtual void Idle_Update(float _DeltaTime);
	virtual void Idle_End();

	virtual void Dash_Enter();
	virtual void Dash_Update(float _DeltaTime);
	virtual void Dash_End();

	virtual void BackDash_Enter();
	virtual void BackDash_Update(float _DeltaTime);
	virtual void BackDash_End();

	virtual void Pattern_Enter();
	virtual void Pattern_Update(float _DeltaTime);
	virtual void Pattern_End();

	virtual void Hit_Enter();
	virtual void Hit_Update(float _DeltaTime);
	virtual void Hit_End();

	virtual void Groggy_Enter();
	virtual void Groggy_Update(float _DeltaTime);
	virtual void Groggy_End();

	virtual void Behavior_Enter();
	virtual void Behavior_Update(float _DeltaTime);
	virtual void Behavior_End();


	virtual void SelectPattern() {}

	bool HitCheck();
	void LookPlayer();
	void RigidbodyMovePlatformCheck(float4& _Dir);
	void PlayAnimation(const std::string_view& _AnimationName, bool _IsForce = true, size_t Frame = 0);

	virtual void CreateAnimation() = 0;

};

