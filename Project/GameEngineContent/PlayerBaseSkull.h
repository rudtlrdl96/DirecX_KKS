#pragma once
#include "BaseContentActor.h"
#include "ClassFSM.h"
#include "Rigidbody2D.h"
#include "SkullData.h"

class PlayerBaseSkull : public BaseContentActor
{
	friend class Player;

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

	void SetPlayer(std::shared_ptr<class Player> _ParentPlayer);

protected:	
	GameEngineTransform* PlayerTrans = nullptr;

	std::shared_ptr<ContentSpriteRenderer> SkullRenderer = nullptr;

	ColorBuffer Buffer;

	std::vector<AnimationAttackMetaData> AnimColMeta_Attack;
	std::vector<AnimationAttackMetaData> AnimColMeta_JumpAttack;
	std::vector<AnimationAttackMetaData> AnimColMeta_SkillA;
	std::vector<AnimationAttackMetaData> AnimColMeta_SkillB;
	std::vector<AnimationAttackMetaData> AnimColMeta_Switch;

	ClassFSM<PlayerBaseSkull> PlayerFSM;

	std::shared_ptr<class CaptureTrail> DashTrail = nullptr;
	std::shared_ptr<class CaptureTrail> EffectCaptureTrail = nullptr;

	std::shared_ptr<class GameEngineCollision> WalkCol = nullptr;
	std::shared_ptr<class GameEngineCollision> GroundCol = nullptr;
	std::shared_ptr<class GameEngineCollision> JumpCol = nullptr;

	Rigidbody2D DashRigidbody;
	Rigidbody2D AttackRigidbody;

	SkullData Data = SkullData();

	std::string AnimNamePlusText = "";
	float4 JumpDir = float4::Zero;

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

	virtual void DataLoad() = 0;
	virtual void TextureLoad() = 0;
	virtual void CreateAnimation() = 0;
	virtual void AnimationColLoad() = 0;

	std::shared_ptr<class GameEngineCollision> PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf = false);

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

private:	
	ActorViewDir ViewDir = ActorViewDir::Right;

	float JumpPower = 700.0f;
	bool CanJump = false;
	bool DoubleJump = false;

	float FallCooldown = 0.0f;

	bool CanDash = false;
	float DashCoolTime = 1000.0f;
	float DashTrailCoolTime = 0.0f;

	float DashVelocity = 3000.0f;
	bool DashCombo = false;

	float WalkSpeed = 350.0f;
	float MaxFallSpeed = 1400.0f;

	UINT AttackComboCount = 0;
	bool IsAttackCombo = false;

	UINT JumpAttackCombo = 0;
	bool IsJumpAttackCombo = false;

	UINT SkillACombo = 0;
	UINT SkillBCombo = 0;
	UINT SwitchCombo = 0;
	
	bool IsSwitchValue = false;

	float RenderEffectProgress = 0.0f;
	float RenderEffectSpeed = 0.0f;

	float4 RenderEffectStartColor = float4::Zero;
	float4 RenderEffectEndColor = float4::Zero;


	void CreateColDebugRender();
	void CreateAttackAnim(const AnimationAttackMetaData& _AnimData, float _InterTime);
	void RendererEffect(const float4& _StartColor, const float4& _EndColor, float _Speed);
	void CaptureRenderTex(const float4& _StartColor, const float4& _EndColor, float _Speed);
};

