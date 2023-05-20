#pragma once
#include "BaseContentActor.h"

class BaseMonster : public BaseContentActor
{
public:
	BaseMonster();
	~BaseMonster();

	BaseMonster(const BaseMonster& _Other) = delete;
	BaseMonster(BaseMonster&& _Other) noexcept = delete;
	BaseMonster& operator=(const BaseMonster& _Other) = delete;
	BaseMonster& operator=(BaseMonster&& _Other) noexcept = delete;

protected:
	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	
	void Start() override;

	virtual void Idle_Enter() {}
	virtual void Idle_Update(float _DeltaTime) {}
	virtual void Idle_End() {}


	virtual void Walk_Enter() {}
	virtual void Walk_Update(float _DeltaTime) {}
	virtual void Walk_End() {}

	virtual void Chasing_Enter() {}
	virtual void Chasing_Update(float _DeltaTime) {}
	virtual void Chasing_End() {}

	virtual void Attack_Enter() {}
	virtual void Attack_Update(float _DeltaTime) {}
	virtual void Attack_End() {}

	virtual void Hit_Enter() {}
	virtual void Hit_Update(float _DeltaTime) {}
	virtual void Hit_End() {}

	virtual void Death_Enter() {}
	virtual void Death_Update(float _DeltaTime) {}
	virtual void Death_End() {}

private:
	ClassFSM<BaseMonster> MonsterFsm;

	std::vector<AnimationAttackMetaData> AttackMetaDatas;

	std::shared_ptr<class GameEngineCollision> FindCol = nullptr;

};

