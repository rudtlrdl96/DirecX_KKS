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

	SkillA_DamageRatio = 0.5f;
	SkillB_DamageRatio = 2.7f;
	Switch_DamageRatio = 1.5f;

	HitEvent = []()
	{
		SoundDoubleCheck::Play("Hit_Sword_Small.wav");
	};
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

			HitEnemy->HitMonster(GetMagicAttackDamage() * 1.5f, GetCiriticalDamage(), GetViewDir(), true, true, false, IsCritical(), HitEffectType::Normal);
		}

		switch (GetViewDir())
		{
		case ActorViewDir::Left: 
			FlashPos += float4(-FlashMoveX * 0.5f, 0);
			FlashEnd = GetFlashPosition(ActorViewDir::Left);
			break;
		case ActorViewDir::Right:
			FlashPos += float4(FlashMoveX * 0.5f, 0);
			FlashEnd = GetFlashPosition(ActorViewDir::Right);
			break;
		default:
			break;
		}

		EffectManager::PlayEffect({
			.EffectName = "FlashCut",
			.Position = FlashPos,
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
		GameEngineSound::Play("Atk_Flame_Large 1.wav");

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

			SoundDoubleCheck::Play("Hit_Flame_Small.wav");

			if (Dir.x > 0)
			{
				switch (AttackTypeValue)
				{
				case PlayerBaseSkull::AttackType::MeleeAttack:
					ColMonster->HitMonster(GetMeleeAttackDamage() * SkillB_DamageRatio, GetCiriticalDamage(), ActorViewDir::Right, true, true, true, IsCritical(), HitEffectType::Normal);
					break;
				case PlayerBaseSkull::AttackType::MagicAttack:
					ColMonster->HitMonster(GetMagicAttackDamage() * SkillB_DamageRatio, GetCiriticalDamage(), ActorViewDir::Right, true, true, true, IsCritical(), HitEffectType::Normal);
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
					ColMonster->HitMonster(GetMeleeAttackDamage() * SkillB_DamageRatio, GetCiriticalDamage(), ActorViewDir::Left, true, true, true, IsCritical(), HitEffectType::Normal);
					break;
				case PlayerBaseSkull::AttackType::MagicAttack:
					ColMonster->HitMonster(GetMagicAttackDamage() * SkillB_DamageRatio, GetCiriticalDamage(), ActorViewDir::Left, true, true, true, IsCritical(), HitEffectType::Normal);
					break;
				default:
					break;
				}
			}

		};

		EffectManager::PlayEffect({ .EffectName = "FireSlash",
			.Position = PlayerTrans->GetWorldPosition() + float4(15 * Dir.x, 5),
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
	BattleActorRigidbody.SetVelocity(float4::Zero);

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
			GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");
		}

		if (3 == Render->GetCurrentFrame())
		{
			IsFlash_1 = true;
			Flip = -1.0f;
			GameEngineSound::Play("Atk_Sword_Large (Slash Down)_2.wav");
		}

		if (6 == Render->GetCurrentFrame())
		{
			IsFlash_2 = true;
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
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

			SoundDoubleCheck::Play("Hit_Sword_Small.wav");

			switch (GetViewDir())
			{
			case ActorViewDir::Left:
				if (Flip > 0.0f)
				{
					HitEnemy->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetCiriticalDamage(), ActorViewDir::Left, true, true, false, IsCritical(), HitEffectType::Normal);
				}
				else
				{
					HitEnemy->HitMonster(GetMagicAttackDamage() * Switch_DamageRatio, GetCiriticalDamage(), ActorViewDir::Right, true, true, false, IsCritical(), HitEffectType::Normal);
				}
				break;
			case ActorViewDir::Right:
				if (Flip > 0.0f)
				{
					HitEnemy->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetCiriticalDamage(), ActorViewDir::Right, true, true, false, IsCritical(), HitEffectType::Normal);
				}
				else
				{
					HitEnemy->HitMonster(GetMagicAttackDamage() * Switch_DamageRatio, GetCiriticalDamage(), ActorViewDir::Left, true, true, false, IsCritical(), HitEffectType::Normal);
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
				FlashEnd = GetFlashPosition(ActorViewDir::Left);
			}
			else
			{
				FlashEnd = GetFlashPosition(ActorViewDir::Right);
			}

			break;
		case ActorViewDir::Right:
			FlashPos += float4(FlashMoveX * 0.5f * Flip, 0);

			if (Flip > 0.0f)
			{
				FlashEnd = GetFlashPosition(ActorViewDir::Right);
			}
			else
			{
				FlashEnd = GetFlashPosition(ActorViewDir::Left);
			}
			break;
		default:
			break;
		}

		EffectManager::PlayEffect({
			.EffectName = "FlashCut",
			.Position = FlashPos,
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
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("ChiefGuard_Head.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");
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

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackA").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackB").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_AttackC").GetFullPath()), 0.085f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_JumpAttack").GetFullPath()), 0.07f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_SkillA").GetFullPath()), 0.045f);
	Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_SkillB").GetFullPath()), 0.09f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("ChiefGuard_Unique_Switch").GetFullPath()), 0.06f);

	Render->SetAnimationStartEvent("AttackA", 2, []()
		{
			GameEngineSound::Play("Atk_Sword_Small 1.wav");
		});	

	Render->SetAnimationStartEvent("AttackB", 2, []()
		{
			GameEngineSound::Play("Atk_Sword_Small 2.wav");
		});

	Render->SetAnimationStartEvent("AttackC", 3, []()
		{
			GameEngineSound::Play("Atk_Sword_Small 3.wav");
		});	

	Render->SetAnimationStartEvent("JumpAttack", 2, []()
		{
			GameEngineSound::Play("Atk_Sword_Small 3.wav");
		});
	
	Render->SetAnimationStartEvent("SkillA", 1, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 3, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 5, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 7, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 9, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 11, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
		});	
	
	Render->SetAnimationStartEvent("SkillA", 13, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");
		});

	Render->SetAnimationStartEvent("SkillA", 15, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
		});	
	
	Render->SetAnimationStartEvent("SkillA", 17, []()
		{
			GameEngineSound::Play("Atk_BluntWeapon_Small 1.wav");
		});	
	
	Render->SetAnimationStartEvent("SkillA", 19, []()
		{
			GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");
		});
}

float4 ChiefGuard::GetFlashPosition(ActorViewDir _Dir)
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
	Result.z = -25.0f;

	return Result;
}
