#include "PrecompileHeader.h"
#include "Ent.h"
#include <GameEngineCore/GameEngineCollision.h>

Ent::Ent()
{
}

Ent::~Ent()
{
}

void Ent::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(100); // 100 = 엔트
}

void Ent::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("EntAttackEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		{
			Path.Move("Ent");
			Path.Move("Effect");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("EntAttackEffect.png").GetFullPath(), 1, 11);

			Path.MoveParent();
			Path.MoveParent();
		}

		EffectManager::CreateMetaData("EntAttackEffect", {
			.SpriteName = "EntAttackEffect.png",
			.AnimStart = 0,
			.AnimEnd = 10,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f,
			});
	}
}

void Ent::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "Ent_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "Ent_Walk.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "Ent_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "Ent_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Ent_Dead.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void Ent::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[0] = 0.5f;
	AnimPauseTimes[3] = 0.5f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Ent_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void Ent::SetColData()
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

void Ent::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(8);
	DeadPartNames.push_back("Parts_Ent01.png");
	DeadPartNames.push_back("Parts_Ent02.png");
	DeadPartNames.push_back("Parts_Ent03.png");
	DeadPartNames.push_back("Parts_Ent04.png");
	DeadPartNames.push_back("Parts_Ent05.png");
	DeadPartNames.push_back("Parts_Ent06.png");
	DeadPartNames.push_back("Parts_Ent07.png");
	DeadPartNames.push_back("Parts_Ent08.png");

	if (nullptr == GameEngineTexture::Find("Parts_Ent01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("Ent");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<Ent>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}
}

void Ent::Attack_Enter()
{
	BaseMonster::Attack_Enter();
	IsAttackMove = false;
}

void Ent::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackMove && 1 == Render->GetCurrentFrame())
	{
		IsAttackMove = true;

		switch (Dir)
		{
		case ActorViewDir::Left:
			AttackRigidbody.SetVelocity(float4::Left * 150.0f);
			break;
		case ActorViewDir::Right:
			AttackRigidbody.SetVelocity(float4::Right * 150.0f);
			break;
		default:
			break;
		}


		float4 EffectPos = GetTransform()->GetWorldPosition();

		switch (Dir)
		{
		case ActorViewDir::Left:
			EffectPos += float4(-45, 0, -0.1f);
			break;
		case ActorViewDir::Right:
			EffectPos += float4(45, 0, -0.1f);
			break;
		default:
			break;
		}

		EffectManager::PlayEffect({
			.EffectName = "EntAttackEffect",
			.Postion = EffectPos ,
			.FlipX = Dir == ActorViewDir::Left,
			});

	}
}