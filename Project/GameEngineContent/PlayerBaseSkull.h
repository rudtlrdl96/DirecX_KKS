#pragma once
#include "BaseContentActor.h"
#include "ClassFSM.h"

class PlayerBaseSkull : public BaseContentActor
{
public:
	PlayerBaseSkull();
	~PlayerBaseSkull();

	PlayerBaseSkull(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull(PlayerBaseSkull&& _Other) noexcept = delete;
	PlayerBaseSkull& operator=(const PlayerBaseSkull& _Other) = delete;
	PlayerBaseSkull& operator=(PlayerBaseSkull&& _Other) noexcept = delete;

protected:	
	void Start() override;

	std::shared_ptr<GameEngineSpriteRenderer> SkullRenderer = nullptr;

	template<typename SkullClass>
	void FSMInit(ClassFSM<SkullClass>& _SkullFSM, std::shared_ptr<SkullClass> _ClassPtr)
	{
		if (nullptr == _ClassPtr)
		{
			MsgAssert_Rtti<SkullClass>(" - nullptr 객체으로 스컬 FSM을 초기화하려 했습니다.");
		}

		_SkullFSM.Init(_ClassPtr);

		_SkullFSM.AddFSM("Idle", &SkullClass::Idle_Enter, &SkullClass::Idle_Update, &SkullClass::Idle_End);
		_SkullFSM.AddFSM("Walk", &SkullClass::Walk_Enter, &SkullClass::Walk_Update, &SkullClass::Walk_End);
		_SkullFSM.AddFSM("Attack", &SkullClass::Attack_Enter, &SkullClass::Attack_Update, &SkullClass::Attack_End);
		_SkullFSM.AddFSM("Jump", &SkullClass::Jump_Enter, &SkullClass::Jump_Update, &SkullClass::Jump_End);
		_SkullFSM.AddFSM("JumpAttack", &SkullClass::JumpAttack_Enter, &SkullClass::JumpAttack_Update, &SkullClass::JumpAttack_End);
		_SkullFSM.AddFSM("Fall",  &SkullClass::Fall_Enter, &SkullClass::Fall_Update, &SkullClass::Fall_End);
		_SkullFSM.AddFSM("Dash",  &SkullClass::Dash_Enter, &SkullClass::Dash_Update, &SkullClass::Dash_End);
		_SkullFSM.AddFSM("Switch", &SkullClass::Switch_Enter, &SkullClass::Switch_Update, &SkullClass::Switch_End);
		_SkullFSM.AddFSM("SkillSlotA", &SkullClass::Skill_SlotA_Enter, &SkullClass::Skill_SlotA_Update, &SkullClass::Skill_SlotA_End);
		_SkullFSM.AddFSM("SkillSlotB", &SkullClass::Skill_SlotB_Enter, &SkullClass::Skill_SlotB_Update, &SkullClass::Skill_SlotB_End);
	}
	
	virtual void Idle_Enter() {}
	virtual void Idle_Update(float _DeltaTime) {}
	virtual void Idle_End() {}

	virtual void Walk_Enter() {}
	virtual void Walk_Update(float _DeltaTime) {}
	virtual void Walk_End() {}

	virtual void Attack_Enter() {}
	virtual void Attack_Update(float _DeltaTime) {}
	virtual void Attack_End() {}

	virtual void JumpAttack_Enter() {}
	virtual void JumpAttack_Update(float _DeltaTime) {}
	virtual void JumpAttack_End() {}

	virtual void Jump_Enter() {}
	virtual void Jump_Update(float _DeltaTime) {}
	virtual void Jump_End() {}

	virtual void Fall_Enter() {}
	virtual void Fall_Update(float _DeltaTime) {}
	virtual void Fall_End() {}

	virtual void Dash_Enter() {}
	virtual void Dash_Update(float _DeltaTime) {}
	virtual void Dash_End() {}

	virtual void Switch_Enter() {}
	virtual void Switch_Update(float _DeltaTime) {}
	virtual void Switch_End() {}

	virtual void Skill_SlotA_Enter() {}
	virtual void Skill_SlotA_Update(float _DeltaTime) {}
	virtual void Skill_SlotA_End() {}

	virtual void Skill_SlotB_Enter() {}
	virtual void Skill_SlotB_Update(float _DeltaTime) {}
	virtual void Skill_SlotB_End() {}
private:

};

