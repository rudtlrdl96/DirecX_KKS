#include "PrecompileHeader.h"
#include "TalkNameTag.h"
#include "ContentUIFontRenderer.h"

TalkNameTag::TalkNameTag()
{
}

TalkNameTag::~TalkNameTag()
{
}

void TalkNameTag::SetNameTag(const std::string_view& _Name, const float4& _Pivot /*= float4::Zero*/, const float4& _ForceSize /*= float4::Zero*/)
{
	NameText = _Name;
	FontNameRender->SetText(NameText);
	FontPivot = _Pivot;
	ForceSize = _ForceSize;
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

	FontNameRender = CreateComponent<ContentUIFontRenderer>();
	FontNameRender->SetFont("³Ø½¼Lv2°íµñ");
	FontNameRender->SetScale(20);
	FontNameRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
	FontNameRender->SetColor(float4(0.78039f, 0.72549f, 0.67058f, 1));

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
	float TotalDistance = (NameText.size() / 2.0f) * FontInterval + 40;

	if (ForceSize != float4::Zero)
	{
		TotalDistance = ForceSize.x;
	}

	LeftRender->GetTransform()->SetLocalPosition(float4(22, 0, 0.0f));

	if (108 > TotalDistance)
	{
		CenterRender->Off();
		RightRender->GetTransform()->SetLocalPosition(float4(66, 0, -0.2f));
	}
	else
	{
		CenterRender->GetTransform()->SetLocalPosition(float4(TotalDistance * 0.5f, 1, -0.1f));
		CenterRender->GetTransform()->SetLocalScale(float4(TotalDistance - 66, 34, 1));
		CenterRender->On();

		RightRender->GetTransform()->SetLocalPosition(float4(TotalDistance - 22, 0, -0.2f));
	}

	FontNameRender->GetTransform()->SetLocalPosition(float4(TotalDistance * 0.5f, 2, -0.5f) + FontPivot);
}
