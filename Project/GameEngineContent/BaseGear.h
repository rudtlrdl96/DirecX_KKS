#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

enum class GearState
{
	Fixed,
	Wave,
	Drop,
	Bezier
};

class BaseGear : public BaseContentActor
{
public:
	BaseGear();
	~BaseGear();

	BaseGear(const BaseGear& _Other) = delete;
	BaseGear(BaseGear&& _Other) noexcept = delete;
	BaseGear& operator=(const BaseGear& _Other) = delete;
	BaseGear& operator=(BaseGear&& _Other) noexcept = delete;

	void DropGear(const float4& _WorldPos);
	void DropGear_Bezier(const float4& _Start, const float4& _End);
	
	void BlackAndWhiteEffectOn();
	void ColWaveOn();

	inline void SetEndCallback(std::function<void()> _Callback)
	{
		MoveEndCallback = _Callback;
	}

	inline void BlackAndWhiteColorOn()
	{
		Buffer.Color.a = 1.0f;
	}

	inline void BlackAndWhiteColorOff()
	{
		Buffer.Color.a = 0.0f;
	}

	inline void LegendaryGearEffectOn()
	{
		IsLegendaryGear = true;
	}

	inline void IsUseOn()
	{
		IsUse = true;
	}

	void CallUseEvent() override;

	inline std::shared_ptr<GameEngineCollision> GetBodyCol()
	{
		return GearBodyCol;
	}

	virtual int GetPrice();

protected:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	BlackAndWihteBuffer Buffer;

	std::shared_ptr<EffectActor> DeactiveEffect = nullptr;
	std::shared_ptr<EffectActor> ActiveStartEffect = nullptr;
	std::shared_ptr<EffectActor> ActiveLoopEffect = nullptr;

	std::shared_ptr<EffectActor> LegendaryFrontStartEffect = nullptr;
	std::shared_ptr<EffectActor> LegendaryFrontLoopEffect = nullptr;
	std::shared_ptr<EffectActor> LegendaryBehindStartEffect = nullptr;
	std::shared_ptr<EffectActor> LegendaryBehindLoopEffect = nullptr;

	std::shared_ptr<class Player> ColPlayer = nullptr;

	std::shared_ptr<GameEngineCollision> GearBodyCol = nullptr;
	std::shared_ptr<GameEngineCollision> GearGroundCol = nullptr;
	Rigidbody2D DropRigid;

	GearState State = GearState::Fixed;
	GearState PrevState = GearState::Fixed;

	bool IsEffectOff = false;
	bool IsBlackAndWhite = false;
	bool IsColWave = false;
	bool IsLegendaryGear = false;
	bool IsUse = false;
	bool IsEnterCheck = false;

	float4 WaveCenter = float4::Zero;
	std::vector<float4> BezierPoint;
	float BezierProgress = 0.0f;
	float PressTime = 0.0f;

	std::function<void()> MoveEndCallback = nullptr;
	std::function<void()> ColEnterCallback = nullptr;
	std::function<void()> ColUpdateCallback = nullptr;
	std::function<void()> ColExitCallback = nullptr;

	GameEngineSoundPlayer DestroySound;

	void Start() override;
	void Update(float _DeltaTime) override;

	void Destroy() override;
	void SetWaveState(std::shared_ptr<GameEngineCollision> _PlatformCol);

	float4 GetEffectPos();

	virtual void UseGear();
	virtual void PlayDestroyEffect();
};