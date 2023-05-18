#include "PrecompileHeader.h"
#include "ChiefGuard.h"

ChiefGuard::ChiefGuard()
{
}

ChiefGuard::~ChiefGuard()
{
}

void ChiefGuard::TextureLoad()
{

}

void ChiefGuard::CreateAnimation()
{
	if (nullptr == GameEngineTexture::Find("BoneSkull_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("ChiefGuard");
		Path.Move("Sheet");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Idle.png").GetFullPath(), 6, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Walk.png").GetFullPath(), 6, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Dash.png").GetFullPath(), 5, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Fall.png").GetFullPath(), 2, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_FallRepeat.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Jump.png").GetFullPath(), 3, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackA.png").GetFullPath(), 5, 1);

		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackB.png").GetFullPath(), 5, 1);
		// AttackC Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_AttackC.png").GetFullPath(), 6, 1);

		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_JumpAttack.png").GetFullPath(), 5, 1);

		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_SkillA.png").GetFullPath(), 22, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_SkillB.png").GetFullPath(), 9, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuard_Unique_Switch.png").GetFullPath(), 9, 1);

	}
}

void ChiefGuard::AnimationColLoad()
{
}
