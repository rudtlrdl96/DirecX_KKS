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
	void Start() override;

	virtual void Wait_Enter() {}
	virtual void Wait_Update(float _DeltaTime) {}
	virtual void Wait_End() {}

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
};

