#include "PrecompileHeader.h"
#include "WitchCage.h"
#include "DeadPartParticle.h"

WitchCage::WitchCage()
{
}

WitchCage::~WitchCage()
{
}

void WitchCage::Reset()
{
	Render->SetTexture("Cage_Front.png");
	BackCageRender->SetTexture("Cage_Behind.png");
	IsBrokenValue = false;
	HitCount = -5;
	HitCoolTime = 0.0f;
	IsAllMonsterDeath = false;
}

void WitchCage::Start()
{
	BattleActor::Start();

	if (nullptr == GameEngineTexture::Find("Cage_Behind.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Cage");

		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Behind.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Behind_Destroyed.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Front.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Front_Destroyed.png").GetFullPath());

		Path.Move("DeadPart");

		DeadPartNames.push_back("Cage_Particle01.png");
		DeadPartNames.push_back("Cage_Particle02.png");
		DeadPartNames.push_back("Cage_Particle03.png");
		DeadPartNames.push_back("Cage_Particle04.png");
		DeadPartNames.push_back("Cage_Particle05.png");
		DeadPartNames.push_back("Cage_Particle06.png");

		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle01.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle02.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle03.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle04.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle05.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Cage_Particle06.png").GetFullPath());
	}


	Render->SetScaleToTexture("Cage_Front.png");
	Render->GetTransform()->AddLocalPosition(float4(0, 110, -0.1f));

	float4 ForentScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(ForentScale * 2.0f);

	BackCageRender = CreateComponent<ContentSpriteRenderer>();
	BackCageRender->PipeSetting("2DTexture_ColorLight");
	BackCageRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", CageRenderBuffer);
	BackCageRender->SetScaleToTexture("Cage_Behind.png");
	BackCageRender->GetTransform()->AddLocalPosition(float4(0, 110, 0.1f));

	float4 BackScale = BackCageRender->GetTransform()->GetLocalScale();
	BackCageRender->GetTransform()->SetLocalScale(BackScale * 2.0f);

	CageCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::BrokenObject);
	CageCol->SetColType(ColType::AABBBOX2D);
	CageCol->GetTransform()->SetLocalPosition(float4(0, 111, 0));
	CageCol->GetTransform()->SetLocalScale(float4(390, 265, 1));

	GetContentLevel()->AddEvent("MonsterAllDeath", GetActorCode(), [this]()
		{
			IsAllMonsterDeath = true;
		});
}

void WitchCage::Update(float _DeltaTime)
{
	BattleActor::Update(_DeltaTime);

	if (false == IsAllMonsterDeath)
	{
		return;
	}

	HitCoolTime += _DeltaTime;

	if (false == IsBrokenValue && 0.0f <= HitCoolTime)
	{
		if (nullptr != CageCol->Collision((int)CollisionOrder::PlayerAttack, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			HitEffect();
			++HitCount;
			HitCoolTime = -0.3f;

			IsHit = true;
			IsHitEffectOn = true;
			HitEffectProgress = 0.0f;
		}

		if (0 <= HitCount)
		{

			if (nullptr != BrokenCallback)
			{
				BrokenCallback();
			}

			IsBrokenValue = true;

			PlayBrokenParticle();
			Render->SetTexture("Cage_Front_Destroyed.png");
			BackCageRender->SetTexture("Cage_Behind_Destroyed.png");
			GetContentLevel()->CallEvent("DoorLockMinus");
		}
	}
}

void WitchCage::PlayBrokenParticle()
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;
	GameEngineTransform* ColTrans = CageCol->GetTransform();

	float ColX =  ColTrans->GetLocalScale().hx();
	float ColY = ColTrans->GetLocalScale().hy();

	for (size_t n = 0; n < 5; n++)
	{
		for (size_t i = 0; i < DeadPartNames.size(); i++)
		{
			std::shared_ptr<DeadPartParticle> DeadPart = GetLevel()->CreateActor<DeadPartParticle>();

			GameEngineTransform* PartTrans = DeadPart->GetTransform();
			GameEngineRandom& MainRand = GameEngineRandom::MainRandom;

			float4 Dir = float4::Up;
			Dir.RotaitonZDeg(MainRand.RandomFloat(-20, 20));
			DeadPart->Init(DeadPartNames[i], Dir, MainRand.RandomFloat(700.0f, 900.0f), 1.0f);
			PartTrans->SetWorldPosition(ColTrans->GetWorldPosition() + float4(Rand.RandomFloat(-ColX, ColX), Rand.RandomFloat(-ColY, ColY)));

			PartTrans->SetWorldScale(PartTrans->GetWorldScale() * 2.0f);
		}
	}
}
