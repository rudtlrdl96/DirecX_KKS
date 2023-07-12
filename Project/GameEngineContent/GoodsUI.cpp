#include "PrecompileHeader.h"
#include "GoodsUI.h"
#include "Inventory.h"

GoodsUI::GoodsUI()
{
}

GoodsUI::~GoodsUI()
{
}

void GoodsUI::GoodsUIOn(bool _IsMinimapOn)
{
	PrevFrame_GoldCount = Inventory::GetGoodsCount_Gold();
	PrevFrame_BoneCount = Inventory::GetGoodsCount_Bone();
	PrevFrame_ManaStoneCount = Inventory::GetGoodsCount_ManaStone();

	State = GoodsState::On;
	Progress = 0.0f;

	if (true == _IsMinimapOn)
	{
		StartPos = float4(390, -410);
		EndPos = float4(390, -305);
	}
	else
	{
		StartPos = float4(610, -410);
		EndPos = float4(610, -305);
	}

	On();

	IsGetGoldEffectMove = false;
	GoldEffectProgress = 0.0f;

	IsGetBoneEffectMove = false;
	BoneEffectProgress = 0.0f;

	IsGetManaStoneEffectMove = false;
	ManaStoneEffectProgress = 0.0f;

	BoneGoodsPivot->GetTransform()->SetLocalPosition(float4::Zero);
	GoldGoodsPivot->GetTransform()->SetLocalPosition(float4::Zero);
	ManaStoneGoodsPivot->GetTransform()->SetLocalPosition(float4::Zero);

	BoneCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	GoldCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	ManaStoneCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
}

void GoodsUI::GoodsUIOff(bool _IsMinimapOn)
{
	State = GoodsState::Off;
	Progress = 0.0f;

	if (true == _IsMinimapOn)
	{
		StartPos = float4(390, -305);
		EndPos = float4(390, -410);
	}
	else
	{
		StartPos = float4(610, -305);
		EndPos = float4(610, -410);
	}

	On();
}

void GoodsUI::Start()
{
	if (nullptr == GameEngineSprite::Find("MainSkillCooldownEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MainSkillCooldownEffect.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MainSwitchCooldownEffect.png").GetFullPath(), 5, 4);


		EffectManager::CreateMetaData("MainSkillCooldownEffect", {
			.SpriteName = "MainSkillCooldownEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("MainSwitchCooldownEffect", {
			.SpriteName = "MainSwitchCooldownEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("AddGoodsEffect", {
			.SpriteName = "MainSwitchCooldownEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimInter = 0.04f,
			.ScaleRatio = 0.4f });
	}

	BoneGoodsPivot = CreateComponent<GameEngineComponent>();
	GoldGoodsPivot = CreateComponent<GameEngineComponent>();
	ManaStoneGoodsPivot = CreateComponent<GameEngineComponent>();

	BoneGoodsRender = CreateComponent<GameEngineUIRenderer>();
	BoneGoodsRender->GetTransform()->SetParent(BoneGoodsPivot->GetTransform());
	BoneGoodsRender->SetScaleToTexture("BoneChip_Icon.png");
	float4 BoneTexScale = BoneGoodsRender->GetTransform()->GetLocalScale();
	BoneGoodsRender->GetTransform()->SetLocalScale(BoneTexScale * 2.0f);
	BoneGoodsRender->GetTransform()->SetLocalPosition(float4(0, 34, 0));

	GoldGoodsRender = CreateComponent<GameEngineUIRenderer>();
	GoldGoodsRender->GetTransform()->SetParent(GoldGoodsPivot->GetTransform());
	GoldGoodsRender->SetScaleToTexture("Gold_Icon.png");
	float4 GoldTexScale = GoldGoodsRender->GetTransform()->GetLocalScale();
	GoldGoodsRender->GetTransform()->SetLocalScale(GoldTexScale * 2.0f);
	GoldGoodsRender->GetTransform()->SetLocalPosition(float4(0, 0, 0));

	ManaStoneGoodsRender = CreateComponent<GameEngineUIRenderer>();
	ManaStoneGoodsRender->GetTransform()->SetParent(ManaStoneGoodsPivot->GetTransform());
	ManaStoneGoodsRender->SetScaleToTexture("ManaStone_Icon.png");
	float4 ManaStoneTexScale = ManaStoneGoodsRender->GetTransform()->GetLocalScale();
	ManaStoneGoodsRender->GetTransform()->SetLocalScale(ManaStoneTexScale * 2.0f);
	ManaStoneGoodsRender->GetTransform()->SetLocalPosition(float4(0, -34, 0));

	BoneCountFont = CreateComponent<ContentUIFontRenderer>();
	BoneCountFont->GetTransform()->SetParent(BoneGoodsPivot->GetTransform());
	BoneCountFont->GetTransform()->SetLocalPosition(float4(-18, 35, 0));
	BoneCountFont->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	BoneCountFont->SetScale(15);
	BoneCountFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_RIGHT | FW1_VCENTER));
	BoneCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	BoneCountFont->SetText("0");

	GoldCountFont = CreateComponent<ContentUIFontRenderer>();
	GoldCountFont->GetTransform()->SetParent(GoldGoodsPivot->GetTransform());
	GoldCountFont->GetTransform()->SetLocalPosition(float4(-18, 1, 0));
	GoldCountFont->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	GoldCountFont->SetScale(15);
	GoldCountFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_RIGHT | FW1_VCENTER));
	GoldCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	GoldCountFont->SetText("0");

	ManaStoneCountFont = CreateComponent<ContentUIFontRenderer>();
	ManaStoneCountFont->GetTransform()->SetParent(ManaStoneGoodsPivot->GetTransform());
	ManaStoneCountFont->GetTransform()->SetLocalPosition(float4(-18, -33, 0));
	ManaStoneCountFont->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	ManaStoneCountFont->SetScale(15);
	ManaStoneCountFont->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_RIGHT | FW1_VCENTER));
	ManaStoneCountFont->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	ManaStoneCountFont->SetText("0");

	GetTransform()->SetWorldPosition(float4(610, -410));

	// float4(0.9f, 0.9f, 0.9f, 1) float4(0.6588f, 0.651f, 0.6863f, 1) Bone
	// float4(0.9f, 0.9f, 0.9f, 1) float4(0.90196f, 0.8549f, 0.18431f, 1) Gold
	// float4(0.9f, 0.9f, 0.9f, 1) float4(0.549f, 0.36862f, 0.80392f, 1) ManaStone
}

void GoodsUI::Update(float _DeltaTime)
{
	if (false == GameEngineInput::IsKey("GetGoods"))
	{
		GameEngineInput::CreateKey("GetGoods", 'I');
	}

	if (true == GameEngineInput::IsDown("GetGoods"))
	{
		Inventory::AddGoods_Bone(10);
		Inventory::AddGoods_Gold(10);
		Inventory::AddGoods_ManaStone(10);
	}

	int CurFrame_GoldCount = Inventory::GetGoodsCount_Gold();
	int CurFrame_BoneCount = Inventory::GetGoodsCount_Bone();
	int CurFrame_ManaStoneCount = Inventory::GetGoodsCount_ManaStone();

	// Bone
	if (nullptr != BoneEffect && true == BoneEffect->IsDeath())
	{
		BoneEffect = nullptr;
	}

	if (false == IsGetBoneEffectMove && nullptr == BoneEffect && CurFrame_BoneCount != PrevFrame_BoneCount)
	{
		BoneEffect = EffectManager::PlayEffect({
			.EffectName = "AddGoodsEffect", .IsUI = true });

		BoneEffect->GetTransform()->SetParent(BoneGoodsRender->GetTransform());
		BoneEffect->GetTransform()->SetLocalPosition(float4(0, 14 / BoneGoodsRender->GetTransform()->GetWorldScale().y, -1));

		IsGetBoneEffectMove = true;
		BoneEffectProgress = 0.0f;
	}

	if (true == IsGetBoneEffectMove)
	{
		BoneEffectProgress += _DeltaTime * 2.0f;

		GoodsEffect(BoneGoodsPivot, BoneCountFont, float4(0.6588f, 0.651f, 0.6863f, 1), BoneEffectProgress);

		if (1.5f <= BoneEffectProgress) // End
		{
			IsGetBoneEffectMove = false;
			BoneEffectProgress = 0.0f;
		}
	}

	// Gold
	if (nullptr != GoldEffect && true == GoldEffect->IsDeath())
	{
		GoldEffect = nullptr;
	}
		
	if (false == IsGetGoldEffectMove && nullptr == GoldEffect &&  CurFrame_GoldCount != PrevFrame_GoldCount)
	{
		GoldEffect = EffectManager::PlayEffect({
			.EffectName = "AddGoodsEffect", .IsUI = true});

		GoldEffect->GetTransform()->SetParent(GoldGoodsRender->GetTransform());
		GoldEffect->GetTransform()->SetLocalPosition(float4(0, 14 / GoldGoodsRender->GetTransform()->GetWorldScale().y, -1));
	
		IsGetGoldEffectMove = true;
		GoldEffectProgress = 0.0f;
	}

	if (true == IsGetGoldEffectMove)
	{
		GoldEffectProgress += _DeltaTime * 2.0f;

		GoodsEffect(GoldGoodsPivot, GoldCountFont, float4(0.90196f, 0.8549f, 0.18431f, 1), GoldEffectProgress);

		if (1.5f <= GoldEffectProgress) // End
		{
			IsGetGoldEffectMove = false;
			GoldEffectProgress = 0.0f;
		}
	}

	// ManaStone
	if (nullptr != ManaStoneEffect && true == ManaStoneEffect->IsDeath())
	{
		ManaStoneEffect = nullptr;
	}

	if (false == IsGetManaStoneEffectMove && nullptr == ManaStoneEffect && CurFrame_ManaStoneCount != PrevFrame_ManaStoneCount)
	{
		ManaStoneEffect = EffectManager::PlayEffect({
			.EffectName = "AddGoodsEffect", .IsUI = true });

		ManaStoneEffect->GetTransform()->SetParent(ManaStoneGoodsRender->GetTransform());
		ManaStoneEffect->GetTransform()->SetLocalPosition(float4(0, 14 / ManaStoneGoodsRender->GetTransform()->GetWorldScale().y, -1));

		IsGetManaStoneEffectMove = true;
		ManaStoneEffectProgress = 0.0f;
	}

	if (true == IsGetManaStoneEffectMove)
	{
		ManaStoneEffectProgress += _DeltaTime * 2.0f;

		GoodsEffect(ManaStoneGoodsPivot, ManaStoneCountFont, float4(0.549f, 0.36862f, 0.80392f, 1), ManaStoneEffectProgress);

		if (1.5f <= ManaStoneEffectProgress) // End
		{
			IsGetManaStoneEffectMove = false;
			ManaStoneEffectProgress = 0.0f;
		}
	}

	BoneCountFont->SetText(std::to_string(Inventory::GetGoodsCount_Bone()));
	GoldCountFont->SetText(std::to_string(Inventory::GetGoodsCount_Gold()));
	ManaStoneCountFont->SetText(std::to_string(Inventory::GetGoodsCount_ManaStone()));

	switch (State)
	{
	case GoodsUI::GoodsState::None:
		break;
	default:
	{
		Progress += _DeltaTime * 2.0f;

		GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, EndPos, Progress));

		if (1.0f <= Progress)
		{
			if (State == GoodsState::Off)
			{
				Off();
			}

			Progress = 0.0f;
			State = GoodsState::None;
		}
	}
		break;
	}

	PrevFrame_GoldCount = CurFrame_GoldCount;
	PrevFrame_BoneCount = CurFrame_BoneCount;
	PrevFrame_ManaStoneCount = CurFrame_ManaStoneCount;
}

void GoodsUI::GoodsEffect(std::shared_ptr<GameEngineComponent>& _Pivot, std::shared_ptr<ContentUIFontRenderer>& _Font, const float4& _Color, float _Progress)
{
	if (1.25f <= _Progress) // 0.75f ~ 1.0f
	{
		_Font->SetColor(float4::LerpClamp(_Color, float4(0.9f, 0.9f, 0.9f, 1.0f), (_Progress - 1.25f) * 4.0f));
	}
	else if (0.25f <= _Progress) // 0.25f ~ 0.5f
	{
		_Pivot->GetTransform()->SetLocalPosition(float4::LerpClamp(float4(0, 5, 0), float4(0, 0, 0), (_Progress - 0.25f) * 4.0f));
	}
	else // 0 ~ 0.25f
	{
		_Font->SetColor(float4::LerpClamp(float4(0.9f, 0.9f, 0.9f, 1.0f), _Color, _Progress * 4.0f));
		_Pivot->GetTransform()->SetLocalPosition(float4::LerpClamp(float4(0, 0, 0), float4(0, 5, 0), _Progress * 4.0f));
	}
}