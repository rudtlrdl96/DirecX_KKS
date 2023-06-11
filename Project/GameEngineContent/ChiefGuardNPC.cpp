#include "PrecompileHeader.h"
#include "ChiefGuardNPC.h"
#include "GameEngineActorGUI.h"

ChiefGuardNPC::ChiefGuardNPC()
{
}

ChiefGuardNPC::~ChiefGuardNPC()
{
}

void ChiefGuardNPC::Death()
{
	BaseNPC::Death();

	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("ChiefGuard_Script00_End", GetActorCode());
}

void ChiefGuardNPC::Start()
{
	BaseNPC::Start();

	if (nullptr == GameEngineSprite::Find("GetSkull_Legendary_ElectricSide.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("ChiefGuard");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("GetSkull_Legendary_ElectricSide.png").GetFullPath(), 4, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("GetSkull_Legendary_ElectricUp.png").GetFullPath(), 5, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("GetSkull_Legendary_Smoke.png").GetFullPath(), 3, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("GetSkull_Thunder_Effect.png").GetFullPath(), 4, 3);

		EffectManager::CreateMetaData("GetSkull_Legendary_ElectricSide", {
			.SpriteName = "GetSkull_Legendary_ElectricSide.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f});

		EffectManager::CreateMetaData("GetSkull_Legendary_ElectricUp", {
			.SpriteName = "GetSkull_Legendary_ElectricUp.png",
			.AnimStart = 0,
			.AnimEnd = 14,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("GetSkull_Legendary_Smoke", {
			.SpriteName = "GetSkull_Legendary_Smoke.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("GetSkull_Thunder_Effect", {
			.SpriteName = "GetSkull_Thunder_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 10,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });
	}


	MainRender->CreateAnimation({
	.AnimationName = "Idle", .SpriteName = "ChiefGuardNPC_Idle.png", .ScaleToTexture = true, });

	MainRender->ChangeAnimation("Idle");

	HeadRender = CreateComponent<ContentSpriteRenderer>();
	HeadRender->PipeSetting("2DTexture_Color");
	HeadRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	HeadRender->SetScaleRatio(2.0f);
	
	HeadRender->CreateAnimation({
		.AnimationName = "HeadIdle", .SpriteName = "ChiefGuardNPC_Head.png", .ScaleToTexture = true, });

	HeadRender->ChangeAnimation("HeadIdle");
	HeadRender->GetTransform()->SetLocalPosition(float4(-13, 20, 0));

	ScriptCol = CreateComponent<GameEngineCollision>();
	ScriptCol->GetTransform()->SetLocalPosition(float4(0, 0, 1));
	ScriptCol->GetTransform()->SetLocalScale(float4(200, 1000, 1));

	GetContentLevel()->AddEvent("ChiefGuard_Script00_End", GetActorCode(), [this]()
		{
			HeadRender->Off();
		});
}

void ChiefGuardNPC::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);

	if (true == ScriptCol->IsUpdate() && 
		nullptr != ScriptCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		GetContentLevel()->CallEvent("ChiefGuard_PlayerMove");
		ScriptCol->Off();
	}
}

void ChiefGuardNPC::ResetBehavior()
{
	HeadRender->On();
	ScriptCol->On();
}

void ChiefGuardNPC::PlayBehavior()
{
	HeadRender->On();
	ScriptCol->On();

	GetContentLevel()->CallEvent("LockMonsterMove");
}

void ChiefGuardNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("ChiefGuardNPC_Head.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("ChiefGuard");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuardNPC_Head.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuardNPC_Idle.png").GetFullPath(), 1, 1);
	}
}
