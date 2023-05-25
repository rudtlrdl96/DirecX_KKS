#include "PrecompileHeader.h"
#include "ChiefGuard.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include  "Projectile.h"
#include "BaseMonster.h"

ChiefGuard::ChiefGuard()
{
}

ChiefGuard::~ChiefGuard()
{
}

void ChiefGuard::Start()
{
	PlayerBaseSkull::Start();

	FlashCol = CreateComponent<GameEngineCollision>();
	float4 ColSize = float4(FlashMoveX, 58, 1);
	FlashCol->GetTransform()->SetWorldScale(ColSize);
	FlashCol->GetTransform()->SetWorldRotation(float4::Zero);
}

void ChiefGuard::Skill_SlotA_Enter()
{
	PlayerBaseSkull::Skill_SlotA_Enter();
	IsFlash = false;
}

void ChiefGuard::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (true == IsFlash)
	{
		FlashProgress += _DeltaTime * FlashSpeed;
		PlayerTrans->SetWorldPosition(float4::LerpClamp(FlashStart, FlashEnd, FlashProgress));

		if (1.0f <= FlashProgress)
		{
			IsFlash = false;
			FlashProgress = 0.0f;
		}
	}

	if (false == IsFlash && 19 == Render->GetCurrentFrame())
	{
		IsFlash = true;
		FlashProgress = 0.0f;

		FlashStart = PlayerTrans->GetWorldPosition();
		float4 FlashPos = FlashStart + float4(0, 30);

		GameEngineTransform* ColTrans = FlashCol->GetTransform();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			ColTrans->SetWorldPosition(FlashStart + float4(-FlashMoveX * 0.5f, 30, 0));
			break;
		case ActorViewDir::Right:
			ColTrans->SetWorldPosition(FlashStart + float4(FlashMoveX * 0.5f, 30, 0));
			break;
		default:
			break;
		}

		std::vector<std::shared_ptr<GameEngineCollision>> ColsDatas;

		FlashCol->CollisionAll((int)CollisionOrder::Monster, ColsDatas, ColType::AABBBOX2D, ColType::AABBBOX2D);

		for (size_t i = 0; i < ColsDatas.size(); i++)
		{
			std::shared_ptr<BaseMonster> HitEnemy = ColsDatas[i]->GetActor()->DynamicThis<BaseMonster>();

			if (nullptr == HitEnemy)
			{
				MsgAssert_Rtti<ChiefGuard>(" - BaseMonster를 상속받은 클래스만 CollisionOrder::Monster에 들어갈 수 있습니다");
				return;
			}

			HitEnemy->HitMonster(GetMagicAttackDamage(), GetViewDir(), true, true);
		}

		switch (GetViewDir())
		{
		case ActorViewDir::Left: 
			FlashPos += float4(-FlashMoveX * 0.5f, 0);
			FlashEnd = GetFlashPostion(ActorViewDir::Left);
			break;
		case ActorViewDir::Right:
			FlashPos += float4(FlashMoveX * 0.5f, 0);
			FlashEnd = GetFlashPostion(ActorViewDir::Right);
			break;
		default:
			break;
		}

		EffectManager::PlayEffect({
			.EffectName = "FlashCut",
			.Postion = FlashPos,
			.FlipX = GetViewDir() == ActorViewDir::Left});
	}
}

void ChiefGuard::Skill_SlotA_End()
{
}

void ChiefGuard::Skill_SlotB_Enter()
{
	PlayerBaseSkull::Skill_SlotB_Enter();

	IsProjecTileShot = false;
}

void ChiefGuard::Skill_SlotB_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotB_Update(_DeltaTime);

	if (false == IsProjecTileShot && 6 == Render->GetCurrentFrame())
	{
		IsProjecTileShot = true;

		std::shared_ptr<Projectile> NewProjectile = GetLevel()->CreateActor<Projectile>();

		float4 Dir = float4::Right;

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			Dir = float4::Left;
			break;
		case ActorViewDir::Right:
			Dir = float4::Right;
			break;
		default:
			break;
		}

		std::function<void(std::shared_ptr<BaseContentActor>, const ProjectileHitParameter& _Parameter)> Ptr = [Dir, this](std::shared_ptr<BaseContentActor> _Actor, const ProjectileHitParameter& _Parameter)
		{
			std::shared_ptr<BaseMonster> ColMonster = _Actor->DynamicThis<BaseMonster>();

			if (nullptr == ColMonster)
			{
				MsgAssert_Rtti<BaseMonster>(" - BaseMonster를 상속받은 클래스만 MonsterCol Order로 설정할 수 있습니다");
				return;
			}

			if (Dir.x > 0)
			{
				switch (AttackTypeValue)
				{
				case PlayerBaseSkull::AttackType::MeleeAttack:
					ColMonster->HitMonster(GetMeleeAttackDamage(), ActorViewDir::Right, true, true);
					break;
				case PlayerBaseSkull::AttackType::MagicAttack:
					ColMonster->HitMonster(GetMagicAttackDamage(), ActorViewDir::Right, true, true);
					break;
				default:
					break;
				}

			}
			else
			{
				switch (AttackTypeValue)
				{
				case PlayerBaseSkull::AttackType::MeleeAttack:
					ColMonster->HitMonster(GetMeleeAttackDamage(), ActorViewDir::Left, true, true);
					break;
				case PlayerBaseSkull::AttackType::MagicAttack:
					ColMonster->HitMonster(GetMagicAttackDamage(), ActorViewDir::Left, true, true);
					break;
				default:
					break;
				}
			}

		};

		EffectManager::PlayEffect({ .EffectName = "FireSlash",
			.Postion = PlayerTrans->GetWorldPosition() + float4(15 * Dir.x, 5),
			.FlipX = GetViewDir() == ActorViewDir::Left });

		NewProjectile->ShotProjectile({
			.EffectName = "FireProjectile",
			.Pos = PlayerTrans->GetWorldPosition() + float4(0, 30, 0),
			.Dir = Dir,
			.ColScale = float4(70, 70, 1),
			.ColOrder = (int)CollisionOrder::Monster,
			.Speed = 1200.0f,
			.LiveTime = 2.0f,
			.EnterEvent = Ptr,
			});
	}
}

void ChiefGuard::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();

	IsFlash = false;

	IsFlash_0 = false;
	IsFlash_1 = false;
	IsFlash_2 = false;
}

void ChiefGuard::Switch_Update(float _DeltaTime)
{
	if (true == IsFlash)
	{
		FlashProgress += _DeltaTime * FlashSpeed;
		PlayerTrans->SetWorldPosition(float4::LerpClamp(FlashStart, FlashEnd, FlashProgress));

		if (1.0f <= FlashProgress)
		{
			IsFlash = false;
			FlashProgress = 0.0f;
		}
	}

	if (false == IsFlash && 
		((false == IsFlash_0 && 0 == Render->GetCurrentFrame()) ||
		 (false == IsFlash_1 && 3 == Render->GetCurrentFrame()) || 
		 (false == IsFlash_2 && 6 == Render->GetCurrentFrame())))
	{
		IsFlash = true;
		FlashProgress = 0.0f;

		FlashStart = PlayerTrans->GetWorldPosition();
		float4 FlashPos = FlashStart + float4(0, 30);

		float Flip = 1.0f;

		if (0 == Render->GetCurrentFrame())
		{
			IsFlash_0 = true;
		}

		if (3 == Render->GetCurrentFrame())
		{
			IsFlash_1 = true;
			Flip = -1.0f;
		}

		if (6 == Render->GetCurrentFrame())
		{
			IsFlash_2 = true;
		}

		GameEngineTransform* ColTrans = FlashCol->GetTransform();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			if (Flip > 0.0f)
			{
				ColTrans->SetWorldPosition(FlashStart + float4(-FlashMoveX * 0.5f, 30, 0));
			}
			else
			{
				ColTrans->SetWorldPosition(FlashStart + float4(FlashMoveX * 0.5f, 30, 0));
			}
			break;
		case ActorViewDir::Right:
			if (Flip > 0.0f)
			{
				ColTrans->SetWorldPosition(FlashStart + float4(FlashMoveX * 0.5f, 30, 0));
			}
			else
			{
				ColTrans->SetWorldPosition(FlashStart + float4(-FlashMoveX * 0.5f, 30, 0));
			}
			break;
		default:
			break;
		}

		std::vector<std::shared_ptr<GameEngineCollision>> ColsDatas;

		FlashCol->CollisionAll((int)CollisionOrder::Monster, ColsDatas, ColType::AABBBOX2D, ColType::AABBBOX2D );

		for (size_t i = 0; i < ColsDatas.size(); i++)
		{
			std::shared_ptr<BaseMonster> HitEnemy = ColsDatas[i]->GetActor()->DynamicThis<BaseMonster>();

			if (nullptr == HitEnemy)
			{
				MsgAssert_Rtti<ChiefGuard>(" - BaseMonster를 상속받은 클래스만 CollisionOrder::Monster에 들어갈 수 있습니다");
				return;
			}

			switch (GetViewDir())
			{
			case ActorViewDir::Left:
				if (Flip > 0.0f)
				{
					HitEnemy->HitMonster(GetMeleeAttackDamage(), ActorViewDir::Left, true, true);
				}
				else
				{
					HitEnemy->HitMonster(GetMagicAttackDamage(), ActorViewDir::Right, true, true);
				}
				break;
			case ActorViewDir::Right:
				if (Flip > 0.0f)
				{
					HitEnemy->HitMonster(GetMeleeAttackDamage(), ActorViewDir::Right, true, true);
				}
				else
				{
					HitEnemy->HitMonster(GetMagicAttackDamage(), ActorViewDir::Left, true, true);
				}
				
				break;
			default:
				break;
			}
		}

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			FlashPos += float4(-FlashMoveX  * 0.5f * Flip, 0);

			if (Flip > 0.0f)
			{
				FlashEnd = GetFlashPostion(ActorViewDir::Left);
			}
			else
			{
				FlashEnd = GetFlashPostion(ActorViewDir::Right);
			}

			break;
		case ActorViewDir::Right:
			FlashPos += float4(FlashMoveX * 0.5f * Flip, 0);

			if (Flip > 0.0f)
			{
				FlashEnd = GetFlashPostion(ActorViewDir::Right);
			}
			else
			{
				FlashEnd = GetFlashPostion(ActorViewDir::Left);
			}
			break;
		default:
			break;
		}

		EffectManager::PlayEffect({
			.EffectName = "FlashCut",
			.Postion = FlashPos,
			.FlipX = GetViewDir() == ActorViewDir::Left });
	}

	PlayerBaseSkull::Switch_Update(_DeltaTime);
}

void ChiefGuard::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(203); // 203 == 경비대장
}

void ChiefGuard::TextureLoad()
{
}

void ChiefGuard::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ChiefGuard_Unique_Idle.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "ChiefGuard_Unique_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "ChiefGuard_Unique_Dash.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "ChiefGuard_Unique_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "ChiefGuard_Unique_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "ChiefGuard_Unique_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}

void ChiefGuard::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("ChiefGuard");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackA").GetFullPath()), 0.08f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackB").GetFullPath()), 0.08f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackC").GetFullPath()), 0.1f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_JumpAttack").GetFullPath()), 0.1f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_SkillA").GetFullPath()), 0.045f);
	Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_SkillB").GetFullPath()), 0.09f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_Switch").GetFullPath()), 0.1f);
}

float4 ChiefGuard::GetFlashPostion(ActorViewDir _Dir)
{
	float4 Result = float4::Zero;

	GameEngineTransform* ColTrans = FlashCol->GetTransform();

	float4 ColCenterWorldPos = PlayerTrans->GetWorldPosition();

	switch (_Dir)
	{
	case ActorViewDir::Left:
		ColCenterWorldPos += float4(-FlashMoveX * 0.5f, 32);
		break;
	case ActorViewDir::Right:
		ColCenterWorldPos += float4(FlashMoveX * 0.5f, 32);
		break;
	default:
		break;
	}

	ColTrans->SetWorldPosition(ColCenterWorldPos);

	std::vector<std::shared_ptr<GameEngineCollision>> PlatformDatas;

	if (true == FlashCol->CollisionAll(CollisionOrder::Platform_Normal, PlatformDatas, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		float4 PlayerPos = PlayerTrans->GetWorldPosition();
		float NearDis = D3D10_FLOAT32_MAX;

		for (size_t i = 0; i < PlatformDatas.size(); i++)
		{
			GameEngineTransform* PlatformTrans = PlatformDatas[i]->GetTransform();

			float4 PlatformColPos = PlatformTrans->GetWorldPosition();
			float4 PlatformSize = PlatformTrans->GetWorldScale();

			switch (_Dir)
			{
			case ActorViewDir::Left:
				PlatformColPos.x += PlatformSize.hx() + 30;
				break;
			case ActorViewDir::Right:
				PlatformColPos.x -= PlatformSize.hx() + 30;
				break;
			default:
				break;
			}

			float PlatformDis = (PlatformColPos - PlayerPos).Size();

			if (NearDis >= PlatformDis)
			{
				Result = PlatformColPos;
				NearDis = PlatformDis;
			}
		}

	}
	else
	{
		Result = PlayerTrans->GetWorldPosition();

		switch (_Dir)
		{
		case ActorViewDir::Left:
			Result -= float4(FlashMoveX, 0);
			break;
		case ActorViewDir::Right:
			Result += float4(FlashMoveX, 0);
			break;
		default:
			break;
		}
	}

	Result.y = PlayerTrans->GetWorldPosition().y;

	return Result;
}
