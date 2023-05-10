#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>

PlayerBaseSkull::PlayerBaseSkull()
{
}

PlayerBaseSkull::~PlayerBaseSkull()
{
}

void PlayerBaseSkull::Start()
{
	SkullRenderer = CreateComponent<GameEngineSpriteRenderer>();
	
	if (false == GameEngineInput::IsKey("PlayerMove_Left"))
	{
		GameEngineInput::CreateKey("PlayerMove_Left", VK_LEFT);
		GameEngineInput::CreateKey("PlayerMove_Right", VK_RIGHT);
		GameEngineInput::CreateKey("PlayerMove_Dash", 'Z');
		GameEngineInput::CreateKey("PlayerMove_Attack", 'X');
		GameEngineInput::CreateKey("PlayerMove_Jump", 'C');
		GameEngineInput::CreateKey("PlayerMove_Skill_A", 'A');
		GameEngineInput::CreateKey("PlayerMove_Skill_B", 'S');
	}

	PlayerFSM.Init(Shared_This_dynamic_pointer<PlayerBaseSkull>());

	PlayerFSM.AddFSM("Idle", &PlayerBaseSkull::Idle_Enter, &PlayerBaseSkull::Idle_Update, &PlayerBaseSkull::Idle_End);
	PlayerFSM.AddFSM("Walk", &PlayerBaseSkull::Walk_Enter, &PlayerBaseSkull::Walk_Update, &PlayerBaseSkull::Walk_End);
	PlayerFSM.AddFSM("Attack", &PlayerBaseSkull::Attack_Enter, &PlayerBaseSkull::Attack_Update, &PlayerBaseSkull::Attack_End);
	PlayerFSM.AddFSM("Jump", &PlayerBaseSkull::Jump_Enter, &PlayerBaseSkull::Jump_Update, &PlayerBaseSkull::Jump_End);
	PlayerFSM.AddFSM("JumpAttack", &PlayerBaseSkull::JumpAttack_Enter, &PlayerBaseSkull::JumpAttack_Update, &PlayerBaseSkull::JumpAttack_End);
	PlayerFSM.AddFSM("Fall", &PlayerBaseSkull::Fall_Enter, &PlayerBaseSkull::Fall_Update, &PlayerBaseSkull::Fall_End);
	PlayerFSM.AddFSM("Dash", &PlayerBaseSkull::Dash_Enter, &PlayerBaseSkull::Dash_Update, &PlayerBaseSkull::Dash_End);
	PlayerFSM.AddFSM("Switch", &PlayerBaseSkull::Switch_Enter, &PlayerBaseSkull::Switch_Update, &PlayerBaseSkull::Switch_End);
	PlayerFSM.AddFSM("Skill_A", &PlayerBaseSkull::Skill_SlotA_Enter, &PlayerBaseSkull::Skill_SlotA_Update, &PlayerBaseSkull::Skill_SlotA_End);
	PlayerFSM.AddFSM("Skill_B", &PlayerBaseSkull::Skill_SlotB_Enter, &PlayerBaseSkull::Skill_SlotB_Update, &PlayerBaseSkull::Skill_SlotB_End);
}


bool PlayerBaseSkull::IsGround() const
{
	return true;
}