#pragma once
#include "BattleActor.h"
#include "ClassFSM.h"
#include "AnimAttackCheck.h"
#include "Rigidbody2D.h"
#include "SkullData.h"

class PlayerBaseSkull : public BattleActor
{
protected:
	enum class SearchColMode
	{
		Left,
		Right
	};
public:
	friend class Player;

	enum class PlayerFSM_State
	{
		Idle,
		Walk,
		Fall,
		Jump,
		JumpAttack,
		Attack,
		SkillA,
		SkillB,
		Switch,
		Dash,
	};

	enum class AttackType
	{
		MeleeAttack,
		MagicAttack,
	};


public:
	PlayerBaseSkull();
	~PlayerBaseSkull();

	PlayerBaseSkull(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull(PlayerBaseSkull&& _Other) noexcept = delete;
	PlayerBaseSkull& operator=(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull& operator=(PlayerBaseSkull&& _Other) noexcept = delete;

	inline Rigidbody2D* GetDashRigidbody()
	{
		return &DashRigidbody;
	}

	float GetMeleeAttackDamage() const;
	float GetMagicAttackDamage() const;


	void SetPlayer(std::shared_ptr<class Player> _ParentPlayer);

	inline std::string GetTexName_MainSkullUI() const
	{
		return Data.IconName_MainSkull;
	}

	inline std::string GetTexName_SubSkullUI() const
	{
		return Data.IconName_SubSkull;
	}

	inline std::string GetTexName_InventoryUI() const
	{
		return Data.IconName_Inventory;
	}	

	inline std::string GetTexName_SkillA() const
	{
		return Data.IconName_SkillA;
	}

	inline std::string GetTexName_SkillB() const
	{
		return Data.IconName_SkillB;
	}

	inline bool IsActiveSkillA() const
	{
		return IsActiveSkillA_Value;
	}

	inline bool IsActiveSkillB() const
	{
		return IsActiveSkillB_Value;
	}

	inline float GetCurSkillATime() const
	{
		return CurSkillATime;
	}

	inline float GetCurSkillBTime() const
	{
		return CurSkillBTime;
	}

	inline float GetSkillAEndTime() const
	{
		return SkillACoolTime;
	}

	inline float GetSkillBEndTime() const
	{
		return SkillBCoolTime;
	}

	std::shared_ptr<GameEngineActor> SkullDeath();

	inline bool IsSkillALock() const
	{
		return IsLockSkillA;
	}

	inline bool IsSkillBLock() const
	{
		return IsLockSkillB;
	}

	inline SkullType GetSkullType() const
	{
		return Type;
	}

	void PlayStoryMove(const float4& _MovePos, std::function<void()> _EndCallback = nullptr);

protected:
	SkullType Type = SkullType::Balance;

	HitEffectType AttackEffectType = HitEffectType::Normal;
	std::vector<std::string> DeadPartNames;

	class Player* ParentPlayer = nullptr;
	GameEngineTransform* PlayerTrans = nullptr;

	PlayerFSM_State FsmState = PlayerFSM_State::Idle;

	std::vector<AnimationAttackMetaData> AnimColMeta_Attack;
	std::vector<AnimationAttackMetaData> AnimColMeta_JumpAttack;
	std::vector<AnimationAttackMetaData> AnimColMeta_SkillA;
	std::vector<AnimationAttackMetaData> AnimColMeta_SkillB;
	std::vector<AnimationAttackMetaData> AnimColMeta_Switch;

	ClassFSM<PlayerBaseSkull> PlayerFSM;

	std::shared_ptr<class CaptureTrail> DashTrail = nullptr;
	std::shared_ptr<class CaptureTrail> EffectCaptureTrail = nullptr;

	std::shared_ptr<class GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<class GameEngineCollision> BackCol = nullptr;
	std::shared_ptr<class GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<class GameEngineCollision> JumpCol = nullptr;
	std::shared_ptr<class GameEngineCollision> AttackCol = nullptr;
	std::shared_ptr<class GameEngineCollision> RayCol = nullptr;

	Rigidbody2D DashRigidbody;
	Rigidbody2D AttackRigidbody;

	SkullData Data = SkullData();

	std::string AnimNamePlusText = "";

	AttackType AttackTypeValue = AttackType::MeleeAttack;

	bool IsFallEnd = false;
	bool IsDownPlatformCheckOff = false;

	bool IsLockAttack = false;
	bool IsLockSkillA = false;
	bool IsLockSkillB = false;

	bool IsActiveSkillA_Value = true;
	bool IsActiveSkillB_Value = true;

	float CurSkillATime = 1000.0f;
	float SkillACoolTime = 5.0f;
	float CurSkillBTime = 1000.0f;
	float SkillBCoolTime = 5.0f;
	float DashVelocity = 3000.0f;

	UINT AttackComboCount = 0;
	bool IsAttackCombo = false;
	float AttackMoveDis = 700.0f;

	UINT JumpAttackCombo = 0;
	bool IsJumpAttackCombo = false;

	UINT SkillACombo = 0;
	UINT SkillBCombo = 0;
	UINT SwitchCombo = 0;

	float CurDamageRatio = 1.0f;
	float Attack_DamageRatio = 1.0f;
	float SkillA_DamageRatio = 1.0f;
	float SkillB_DamageRatio = 1.0f;
	float Switch_DamageRatio = 1.0f;

	std::string BehaviorAnimationName = "";
	std::function<void()> BehaviorEndCallback = nullptr;
	std::function<void()> PauseEndCallback = nullptr;

	bool DashAvoidance = false;
	bool IsBehaviorAnimPause = false;
	UINT PauseFrame = 0;
	float PauseTime = 1.0f;
	float CurPauseTime = 0.0f;

	float4 StoryMovePos = float4::Zero;
	std::function<void()> StoryMoveEndCallback = nullptr;
	std::function<void()> HitEvent = nullptr;
	std::function<void()> KillEvent = nullptr;

	std::string DashSound = "Default_Dash.wav";

	void Start() override;
	void Update(float _DeltaTime) override;
	
	// FSM Functions
	virtual void Idle_Enter();
	virtual void Idle_Update(float _DeltaTime);
	virtual void Idle_End();

	virtual void Walk_Enter();
	virtual void Walk_Update(float _DeltaTime);
	virtual void Walk_End();

	virtual void Attack_Enter();
	virtual void Attack_Update(float _DeltaTime);
	virtual void Attack_End();

	virtual void JumpAttack_Enter();
	virtual void JumpAttack_Update(float _DeltaTime);
	virtual void JumpAttack_End();

	virtual void Jump_Enter();
	virtual void Jump_Update(float _DeltaTime);
	virtual void Jump_End() {}

	virtual void Fall_Enter();
	virtual void Fall_Update(float _DeltaTime);
	virtual void Fall_End();

	virtual void Dash_Enter();
	virtual void Dash_Update(float _DeltaTime);
	virtual void Dash_End();

	virtual void Switch_Enter();
	virtual void Switch_Update(float _DeltaTime);
	virtual void Switch_End();

	virtual void Skill_SlotA_Enter();
	virtual void Skill_SlotA_Update(float _DeltaTime);
	virtual void Skill_SlotA_End();

	virtual void Skill_SlotB_Enter();
	virtual void Skill_SlotB_Update(float _DeltaTime);
	virtual void Skill_SlotB_End();

	virtual void Behavior_Enter();
	virtual void Behavior_Update(float _DeltaTime);
	virtual void Behavior_End();

	virtual void StoryMove_Enter();
	virtual void StoryMove_Update(float _DeltaTime);
	virtual void StoryMove_End();

	virtual void DataLoad() = 0;
	virtual void TextureLoad() = 0;
	virtual void CreateAnimation() = 0;
	virtual void AnimationColLoad() = 0;

	void Pushback_Attack(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void Pushback_JumpAttack(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void Pushback_SkillA(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void Pushback_SkillB(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void Pushback_Switch(const AnimationAttackMetaData& _AnimData, float _InterTime);


	virtual void SetViewDir(ActorViewDir _ViewDir);

	inline ActorViewDir GetViewDir() const
	{
		return ViewDir;
	}

	inline bool IsSwitch() const
	{
		return IsSwitchValue;
	}

	virtual void CoolTimeCheck(float _DeltaTime);

	void Jump();
	virtual void Dash();

	float SearchPositionX(const float4& _Pos, const float4& _ColScale, float _Inter, SearchColMode _Mode);

	virtual void ChangeSwitchStart() {}
	virtual void ChangeSwitchEnd() {}


private:	
	AnimAttackCheck AttackEnterCheck;
	ActorViewDir ViewDir = ActorViewDir::Right;

	float JumpPower = 1100.0f;
	bool CanJump = false;
	bool DoubleJump = false;

	float FallCooldown = 0.0f;

	bool CanDash = false;
	float DashCoolTime = 1000.0f;
	float DashTrailCoolTime = 0.0f;

	bool DashCombo = false;

	float WalkSpeed = 350.0f;
	float MaxFallSpeed = 1400.0f;
		
	bool IsSwitchValue = false;

	float RenderEffectProgress = 0.0f;
	float RenderEffectSpeed = 0.0f;

	float4 RenderEffectStartColor = float4::Zero;
	float4 RenderEffectEndColor = float4::Zero;

	void CreateColDebugRender();
	void CreateAttackAnim(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void RendererEffect(const float4& _StartColor, const float4& _EndColor, float _Speed);
	void CaptureRenderTex(const float4& _StartColor, const float4& _EndColor, float _Speed);
	void EffectCaptureAnimation(const class CaptureAnimParameter& _Parameter);
};

