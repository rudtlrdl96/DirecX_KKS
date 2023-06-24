#include "PrecompileHeader.h"
#include "TalkButton.h"

TalkButton::TalkButton()
{
}

TalkButton::~TalkButton()
{
}

void TalkButton::UseButton()
{
	if (nullptr == UseCallback)
	{
		MsgAssert_Rtti<TalkButton>(" - 버튼의 Callback 함수를 설정하지 않았습니다.");
		return;
	}

	UseCallback();
}

void TalkButton::HoverOn()
{
	FrameRender->SetTextureAndSlice("TalkButtonFrame_Hover.png", 0.1f, 0.1f, 0.2f, 0.2f);
	FrameRender->GetTransform()->SetLocalScale(float4(184, 34, 1));
}

void TalkButton::HoverOff()
{
	FrameRender->SetTextureAndSlice("TalkButtonFrame.png", 0.1f, 0.1f, 0.2f, 0.2f);
	FrameRender->GetTransform()->SetLocalScale(float4(180, 30, 1));
}

void TalkButton::Start()
{
	if (nullptr == GameEngineTexture::Find("TalkButtonFrame.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("TalkButtonFrame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("TalkButtonFrame_Hover.png").GetFullPath());
	}

	FontRender = CreateComponent<ContentUIFontRenderer>();
	FontRender->SetColor(float4(0.78039f, 0.72549f, 0.67058f, 1));
	FontRender->SetFont("넥슨Lv2고딕");
	FontRender->SetText("텍스트 미설정");
	FontRender->SetScale(18);
	FontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));
	FontRender->GetTransform()->SetLocalPosition(float4(0, 0, -0.1f));

	FrameRender = CreateComponent<ContentSlice9UIRenderer>();   
	FrameRender->SetTextureAndSlice("TalkButtonFrame.png", 0.1f, 0.1f, 0.2f, 0.2f);
	FrameRender->GetTransform()->SetLocalScale(float4(180, 30, 1));
	HoverOff();
}
