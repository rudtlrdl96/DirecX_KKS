#pragma once
#include "BattleActor.h"
#include "Rigidbody2D.h"
#include "MonsterData.h"
#include "AnimAttackCheck.h"

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

	virtual void HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush);
	
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
	bool IsStiffen = false;

	ActorViewDir Dir = ActorViewDir::Right;
	MonsterData Data = MonsterData();

	void Start() override;
	void Update(float _DeltaTime);

	virtual void DataLoad() = 0;

	virtual void SetViewDir(ActorViewDir _Dir, bool _Force = false);


};

