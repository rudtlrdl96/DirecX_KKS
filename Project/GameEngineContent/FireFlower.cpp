#include "PrecompileHeader.h"
#include "FireFlower.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "Projectile.h"
#include "Player.h"

FireFlower::FireFlower()
{
}

FireFlower::~FireFlower()
{
}

void FireFlower::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("FireFlower_Idle.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("FireFlower");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireFlower_Idle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireFlower_Attack.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireFlower_Projectile.png").GetFullPath(), 3, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireFlowerProjectileEffect.png").GetFullPath(), 4, 5);

		EffectManager::CreateMetaData("FireFlower_Projectile", {
			.SpriteName = "FireFlower_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.025f,
			.ScaleRatio = 0.5f
			});

		EffectManager::CreateMetaData("FireFlowerProjectileEffect", {
			.SpriteName = "FireFlowerProjectileEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.025f,
			.ScaleRatio = 1.0f
			});
	}

	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "FireFlower_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Active", .SpriteName = "FireFlower_Attack.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Render->SetScaleRatio(2.0f);
	Render->ChangeAnimation("Idle");
}

void FireFlower::Update(float _DeltaTime)
{
	ShotCoolTime -= _DeltaTime;

	if (0.0f < ShotCoolTime)
	{
		IsShot = false;

		if (true == Render->IsAnimationEnd())
		{
			Render->ChangeAnimation("Idle");
		}

		return;
	}

	Render->ChangeAnimation("Active", static_cast<size_t>(-1), false);

	if (false == IsShot && 5 == Render->GetCurrentFrame())
	{
		IsShot = true;

		std::shared_ptr<Projectile> NewProjectile = GetLevel()->CreateActor<Projectile>();

		float4 ShotDir = float4::Up;
		ShotDir.RotaitonZDeg(GetTransform()->GetLocalRotation().z);

		float4 SpawnPos = GetTransform()->GetWorldPosition() + (ShotDir * 25.0f);

		NewProjectile->ShotProjectile({
			.EffectName = "FireFlower_Projectile",
			.Pos = SpawnPos,
			.Dir = ShotDir,
			.ColScale = float4(20, 20, 1),
			.ColOrder = (int)CollisionOrder::Player,
			.IsPlatformCol = true,
			.IsColDeath = true,
			.Damage = 10,
			.Speed = 500.0f,
			.EnterEvent = [this, ShotDir](std::shared_ptr<BaseContentActor> _Player, ProjectileHitParameter _Parameter)
			{
				std::shared_ptr<Player> CastingPtr = _Player->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<FireFlower>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				std::shared_ptr<EffectActor> Actor =
					EffectManager::PlayEffect({
					.EffectName = "FireFlowerProjectileEffect",
					.Position = _Parameter.ProjectilePos, });

				float Rot = acosf(float4::DotProduct3D(float4::Left, ShotDir.NormalizeReturn()));
				Rot *= GameEngineMath::RadToDeg;
				Actor->GetTransform()->SetLocalRotation(float4(0, 0, Rot));

				CastingPtr->HitPlayer(_Parameter.Attack, float4::Zero);
			},
			.DeathEvent = [this, ShotDir](const float4& _Pos)
			{
				std::shared_ptr<EffectActor> Actor = 
				EffectManager::PlayEffect({
				.EffectName = "FireFlowerProjectileEffect",
				.Position = _Pos,});
				
				float Rot = acosf(float4::DotProduct3D(float4::Left, ShotDir.NormalizeReturn()));				
				Rot *= GameEngineMath::RadToDeg;
				Actor->GetTransform()->SetLocalRotation(float4(0, 0, Rot));
			}, });

		ShotCoolTime = 2.0f;
	}
}

void FireFlower::ResetBehavior()
{
	Render->ChangeAnimation("Idle");
	ShotCoolTime = 0.0f;
	IsShot = false;
}

void FireFlower::PlayBehavior()
{
	Render->ChangeAnimation("Idle");
	ShotCoolTime = 0.0f;
	IsShot = false;
}
