#include "PrecompileHeader.h"
#include "BlossomEnt.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

BlossomEnt::BlossomEnt()
{
}

BlossomEnt::~BlossomEnt()
{
}

void BlossomEnt::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(101); // 101 = 꽃 엔트

	AttackWaitEndTime = 2.0f;
}

void BlossomEnt::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("BlossomEntAttackEffect.png"))
	{
		GameEngineDirectory Path;
	
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
	
		{
			Path.Move("BlossomEnt");
			Path.Move("Effect");
	
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEntAttackEffect.png").GetFullPath(), 4, 7);
	
			Path.MoveParent();
			Path.MoveParent();
		}
	
		EffectManager::CreateMetaData("BlossomEntAttackEffect", {
			.SpriteName = "BlossomEntAttackEffect.png",
			.AnimStart = 0,
			.AnimEnd = 27,
			.AnimIter = 0.07f,
			.ScaleRatio = 1.5f,
			});
	}
}

void BlossomEnt::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "BlossomEnt_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "BlossomEnt_Walk.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "BlossomEnt_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "BlossomEnt_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "BlossomEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void BlossomEnt::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[9] = 1.5f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BlossomEnt_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void BlossomEnt::SetColData()
{
	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, -3, 0));
		ColTrans->SetWorldScale(float4(45, 6, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 45, 0));
		ColTrans->SetWorldScale(float4(50, 90, 1));
	}

	{
		GameEngineTransform* ColTrans = WalkCol->GetTransform();

		LocalWalkColPos = float4(32, 42, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		LocalBackColPos = float4(-32, 42, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		LocalWalkFallColPos = float4(32, 32, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		LocalFindColPos = float4(200, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(400, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(25, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(50, 100, 1));
	}
	
	LoadFindEffectPos = float4(0, 100, 0);
}

void BlossomEnt::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(7);
	DeadPartNames.push_back("Parts_BlossomEnt01.png");
	DeadPartNames.push_back("Parts_BlossomEnt02.png");
	DeadPartNames.push_back("Parts_BlossomEnt03.png");
	DeadPartNames.push_back("Parts_BlossomEnt04.png");
	DeadPartNames.push_back("Parts_BlossomEnt05.png");
	DeadPartNames.push_back("Parts_BlossomEnt06.png");
	DeadPartNames.push_back("Parts_BlossomEnt07.png");

	if (nullptr == GameEngineTexture::Find("Parts_BlossomEnt01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("BlossomEnt");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<BlossomEnt>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}
}

void BlossomEnt::Attack_Enter()
{
	NormalMonster::Attack_Enter();
	IsAttackStart = false;

	IsSuperArmor = true;
	IsUnPushArmor = true;

	Buffer.OutlineColor = float4(1.0f, 1.0f, -1.0f, 1.0f);
	AttackCoolTime = 0.3f;
}

void BlossomEnt::Attack_Update(float _DeltaTime)
{
	NormalMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackStart && 9 == Render->GetCurrentFrame())
	{
		IsAttackStart = true;
		
		EffectManager::PlayEffect({
			.EffectName = "BlossomEntAttackEffect",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 55, -0.1f)
			});
	}

	if (9 == Render->GetCurrentFrame())
	{
		AttackCoolTime -= _DeltaTime;

		if (0.0f < AttackCoolTime)
		{
			return;
		}

		AttackCol->On();

		GameEngineTransform* ColTrans = AttackCol->GetTransform();


		ColTrans->SetLocalPosition(float4(5, 55, 0));
		ColTrans->SetLocalScale(float4(250, 135, 1));

		std::shared_ptr<GameEngineCollision> ColPtr = AttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);
		 
		if (nullptr != ColPtr)
		{
			std::shared_ptr<Player> CastingPtr = ColPtr->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<BlossomEnt>(" - 플레이어만 Player Col Order를 가질 수 있습니다");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Position = CastingPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f });


			CastingPtr->HitPlayer(Data.Attack, float4::Zero);

			AttackCoolTime = 1.0f;
		}

	}
}

void BlossomEnt::Attack_End()
{
	IsSuperArmor = false;
	IsUnPushArmor = false;

	NormalMonster::Attack_End();
	Buffer.OutlineColor = float4::Null;
}
