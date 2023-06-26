#pragma once
#include "BattleActor.h"
#include "Rigidbody2D.h"
#include "MonsterData.h"
#include "AnimAttackCheck.h"
#include "SpeechBubble.h"

class BaseMonster : public BattleActor
{
public:
	static void SetMonstersMove(bool _IsMove);

protected:
	static bool MonsterUnMove;
public:
	BaseMonster();
	~BaseMonster();

	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

	virtual void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush, bool _IsMagicAttack, std::function<void()> _KillEvent = nullptr);
	
	std::shared_ptr<ContentSpriteRenderer> GetRender()
	{
		return Render;
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
	float HP = 0;
	float HitDamageCheck = 0.0f;
	bool IsStiffen = false;

	ActorViewDir Dir = ActorViewDir::Right;
	MonsterData Data = MonsterData();

	float4 DamageFontPivot = float4::Zero;

	float HitWaitTime = 0.0f;

	std::shared_ptr<SpeechBubble> Bubble = nullptr;
	float4 BubblePivot = float4(0, 100, -100);

	void Start() override;
	void Update(float _DeltaTime);

	virtual void DataLoad() = 0;

	virtual void SetViewDir(ActorViewDir _Dir, bool _Force = false);
	
	void PlaySpeechBubble(const std::string_view& _TalkString, float _LiveTime = 3.0f);

};

