#include "PrecompileHeader.h"
#include "TalkNameTag.h"

TalkNameTag::TalkNameTag()
{
}

TalkNameTag::~TalkNameTag()
{
}

void TalkNameTag::SetNameTag(const std::string_view& _Name)
{
	NameText = _Name;
	SortText();
}

void TalkNameTag::SetFontSize(float _FontSize)
{
	FontSize = _FontSize;
	SortText();
}

void TalkNameTag::SetFontInterval(float _FontInterval)
{
	FontInterval = _FontInterval;
	SortText();
}

void TalkNameTag::Start()
{
	if (nullptr == GameEngineTexture::Find("NameTag_Left.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("NameTag_Left.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("NameTag_Center.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("NameTag_Right.png").GetFullPath());
	}

	LeftRender = CreateComponent<ContentUIRender>();
	LeftRender->PipeSetting("2DTexture_Color");
	LeftRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	LeftRender->SetScaleToTexture("NameTag_Left.png");

	RightRender = CreateComponent<ContentUIRender>();
	RightRender->PipeSetting("2DTexture_Color");
	RightRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	RightRender->SetScaleToTexture("NameTag_Right.png");

	CenterRender = CreateComponent<ContentUIRender>();
	CenterRender->PipeSetting("2DTexture_Color");
	CenterRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	CenterRender->SetScaleToTexture("NameTag_Center.png");

	SortText();
}

void TalkNameTag::SortText()
{
	float TotalDistance = NameText.size() * FontInterval + 20;

	LeftRender->GetTransform()->SetLocalPosition(float4(22, 0, 0.0f));

	if (88 > TotalDistance)
	{
		CenterRender->Off();
		RightRender->GetTransform()->SetLocalPosition(float4(66, 0, -0.2f));
	}
	else
	{
		CenterRender->GetTransform()->SetLocalPosition(float4(TotalDistance * 0.5f, 1, -0.1f));
		CenterRender->GetTransform()->SetLocalScale(float4(TotalDistance - 86, 34, 1));
		CenterRender->On();

		RightRender->GetTransform()->SetLocalPosition(float4(TotalDistance - 22, 0, -0.2f));
	}
}
