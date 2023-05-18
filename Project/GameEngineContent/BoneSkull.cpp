#include "PrecompileHeader.h"
#include "BoneSkull.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "BoneHead.h"
#include "EffectManager.h"

BoneSkull::BoneSkull()
{
}

BoneSkull::~BoneSkull()
{
}

void BoneSkull::Start()
{
	PlayerBaseSkull::Start();

	HeadActor = GetLevel()->CreateActor<BoneHead>();
	HeadActor->Off();

}

void BoneSkull::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (false == HeadActor->IsUpdate() && 1 == SkullRenderer->GetCurrentFrame())
	{
		HeadActor->ShotHead(GetViewDir());
		HeadActor->GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition() + float4(8, 50));
		HeadActor->On();
	}
}

void BoneSkull::Skill_SlotB_Enter()
{
	HeadActor->Off();

	GameEngineTransform* PlayerTrans = GetTransform();
	GameEngineTransform* HeadTrans = HeadActor->GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 HeadPos = HeadTrans->GetWorldPosition();

	PlayerTrans->SetLocalPosition(HeadPos - float4(0, 50));

	EffectManager::PlayEffect({"SkullAppearance", PlayerPos});
	EffectManager::PlayEffect({"SkullAppearance", HeadPos - float4(0, 50) });

	PlayerBaseSkull::Skill_SlotB_Enter();
}

void BoneSkull::TextureLoad()
{
	if (nullptr == GameEngineTexture::Find("BoneSkull_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("BoneSkull");
		Path.Move("Sheet");

		// Idle Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle_NoHead.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Idle_NoWeapon.png").GetFullPath(), 4, 1);

		// Walk Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk_NoHead.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Walk_NoWeapon.png").GetFullPath(), 8, 1);

		// Dash Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash_NoHead.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Dash_NoWeapon.png").GetFullPath(), 1, 1);

		// FallEnter Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Fall_NoWeapon.png").GetFullPath(), 2, 1);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_FallDead.png").GetFullPath(), 3, 1);

		// FallRepeat Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat_NoHead.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_FallRepeat_NoWeapon.png").GetFullPath(), 3, 1);

		// Jump Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump.png").GetFullPath(),2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump_NoHead.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Jump_NoWeapon.png").GetFullPath(), 2, 1);

		// AttackA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackA.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackA_NoHead.png").GetFullPath(), 5, 1);
		
		// AttackB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackB.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_AttackB_NoHead.png").GetFullPath(), 4, 1);
		
		// JumpAttack Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_JumpAttack.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_JumpAttack_NoHead.png").GetFullPath(), 4, 1);
		
		// SkillA Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Skill.png").GetFullPath(), 4, 1);

		// SkillB Sprite
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_SkillReborn.png").GetFullPath(), 9, 1);

		// Skull Switch
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Switch.png").GetFullPath(), 7, 1);
			
		// Reborn
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_Reborn2Field.png").GetFullPath(), 22, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_RebornCastle.png").GetFullPath(), 6, 5);

		// Story Animation
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Wait.png").GetFullPath(), 8, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_Getbone.png").GetFullPath(), 10, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_DeadLoop.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Getscroll.png").GetFullPath(), 6, 9);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_0.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_1.png").GetFullPath(), 5, 11);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Intro_2.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoneSkull_Normal_Getskull.png").GetFullPath(), 7, 7);
	}
}

void BoneSkull::CreateAnimation()
{
	//Idle Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "BoneSkull_Idle.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle_NoWeapon", .SpriteName = "BoneSkull_Idle_NoHead.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Idle_NoHead", .SpriteName = "BoneSkull_Idle_NoWeapon.png", .FrameInter = 0.15f, .ScaleToTexture = true });

	//Walk Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "BoneSkull_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk_NoWeapon", .SpriteName = "BoneSkull_Walk_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Walk_NoHead", .SpriteName = "BoneSkull_Walk_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	//Dash Animation
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "BoneSkull_Dash.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash_NoWeapon", .SpriteName = "BoneSkull_Dash_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Dash_NoHead", .SpriteName = "BoneSkull_Dash_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "BoneSkull_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall_NoWeapon", .SpriteName = "BoneSkull_Fall_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Fall_NoHead", .SpriteName = "BoneSkull_Fall_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall Repeat
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "BoneSkull_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat_NoWeapon", .SpriteName = "BoneSkull_FallRepeat_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "FallRepeat_NoHead", .SpriteName = "BoneSkull_FallRepeat_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Jump
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "BoneSkull_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump_NoWeapon", .SpriteName = "BoneSkull_Jump_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	SkullRenderer->CreateAnimation({ .AnimationName = "Jump_NoHead", .SpriteName = "BoneSkull_Jump_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}

void BoneSkull::AnimationColLoad()
{
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("8_Player");
		Path.Move("BoneSkull"); 
		
		Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_AttackA").GetFullPath()), 0.1f);
		Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_AttackB").GetFullPath()), 0.1f);
		Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_JumpAttack").GetFullPath()), 0.1f);
		Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_SkillA").GetFullPath()), 0.1f);
		Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_SkillB").GetFullPath()), 0.07f);
	}
}
