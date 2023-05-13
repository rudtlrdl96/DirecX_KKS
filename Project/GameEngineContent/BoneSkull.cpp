#include "PrecompileHeader.h"
#include "BoneSkull.h"

BoneSkull::BoneSkull()
{
}

BoneSkull::~BoneSkull()
{
}

void BoneSkull::TextureLoad()
{
	if (nullptr == GameEngineTexture::Find("BronSkull_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("BornSkull");
		Path.Move("Sheet");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Idle.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Idle_NoHead.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Idle_NoWeapon.png").GetFullPath(), 4, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Walk.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Walk_NoHead.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Walk_NoWeapon.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Dash.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Dash_NoHead.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BronSkull_Dash_NoWeapon.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Fall.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Fall_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Fall_NoWeapon.png").GetFullPath(), 2, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Normal_FallDead.png").GetFullPath(), 3, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_FallRepeat.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_FallRepeat_NoHead.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_FallRepeat_NoWeapon.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Jump.png").GetFullPath(),2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Jump_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Jump_NoWeapon.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_AttackA.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_AttackA_NoHead.png").GetFullPath(), 5, 1);
		
		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_AttackB.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_AttackB_NoHead.png").GetFullPath(), 4, 1);
		
		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_JumpAttack.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_JumpAttack_NoHead.png").GetFullPath(), 4, 1);
		
		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Skill.png").GetFullPath(), 4, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_SkillReborn.png").GetFullPath(), 9, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Switch.png").GetFullPath(), 7, 1);
			
		// Reborn
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Normal_Reborn2Field.png").GetFullPath(), 22, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Normal_RebornCastle.png").GetFullPath(), 6, 5);

		// Story Animation
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Wait.png").GetFullPath(), 8, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Intro_Getbone.png").GetFullPath(), 10, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_DeadLoop.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Getscroll.png").GetFullPath(), 6, 9);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Intro_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Intro_0.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Intro_1.png").GetFullPath(), 5, 11);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Intro_2.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BornSkull_Normal_Getskull.png").GetFullPath(), 7, 7);
	}
}

void BoneSkull::CreateAnimation()
{
	//Idle Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "BronSkull_Idle.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle_NoWeapon", .SpriteName = "BronSkull_Idle_NoHead.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle_NoHead", .SpriteName = "BronSkull_Idle_NoWeapon.png", .FrameInter = 0.15f, .ScaleToTexture = true });

	//Walk Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "BronSkull_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk_NoWeapon", .SpriteName = "BronSkull_Walk_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk_NoHead", .SpriteName = "BronSkull_Walk_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	//Dash Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "BronSkull_Dash.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash_NoWeapon", .SpriteName = "BronSkull_Dash_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash_NoHead", .SpriteName = "BronSkull_Dash_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "BornSkull_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall_NoWeapon", .SpriteName = "BornSkull_Fall_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall_NoHead", .SpriteName = "BornSkull_Fall_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall Repeat
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "BornSkull_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat_NoWeapon", .SpriteName = "BornSkull_FallRepeat_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat_NoHead", .SpriteName = "BornSkull_FallRepeat_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Jump
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "BornSkull_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump_NoWeapon", .SpriteName = "BornSkull_Jump_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump_NoHead", .SpriteName = "BornSkull_Jump_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}
