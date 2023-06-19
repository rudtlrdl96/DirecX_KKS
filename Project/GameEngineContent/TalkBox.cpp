#include "PrecompileHeader.h"
#include "TalkBox.h"
#include "GameEngineActorGUI.h"
#include "TalkArrow.h"

TalkBox::TalkBox()
{
}

TalkBox::~TalkBox()
{
}

void TalkBox::ActiveTalkBox(const std::string_view& _Name)
{ 
	NameText = _Name;
	NameTagPtr->SetNameTag(NameText);
	On();
}

void TalkBox::SetMainText(const std::wstring_view& _MainText, std::function<void()> _Callback)
{
	BoostSpeed = 1.0f;
	MainText = _MainText;
	Progress = 0.0f;
	IsReadEnd = false;
	ReadEndCallback = _Callback;
}

void TalkBox::On()
{
	BaseContentActor::On();

	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	//Ptr->SetTarget(FontNameRender->GetTransform());
	//Ptr->On();
}

void TalkBox::Off()
{
	BaseContentActor::Off();
	FontTextRender->Off();
}

#include "GameEngineActorGUI.h"

void TalkBox::Start()
{
	if (false == GameEngineInput::IsKey("TalkKey"))
	{
		GameEngineInput::CreateKey("TalkKey", 'X');
	}

	if (nullptr == GameEngineTexture::Find("TalkBox.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resrouces");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("TalkBox.png").GetFullPath());
	}

	ArrowPtr = GetLevel()->CreateActor<TalkArrow>();
	ArrowPtr->GetTransform()->SetParent(GetTransform());
	ArrowPtr->GetTransform()->SetLocalPosition(float4(285.0f, -35.0f, -0.1f));
	ArrowPtr->SetSpeed(1.5f);
	ArrowPtr->Off();

	Render = CreateComponent<ContentUIRender>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->SetScaleToTexture("TalkBox.png");

	NameTagPtr = GetLevel()->CreateActor<TalkNameTag>();
	NameTagPtr->GetTransform()->SetParent(GetTransform());
	NameTagPtr->GetTransform()->SetLocalPosition(float4(-310, 50, -0.1f));
	//NameTagPtr->SetFontSize(26);
	NameTagPtr->SetFontInterval(21);

	FontNameRender = CreateComponent<ContentUIFontRenderer>();
	FontNameRender->SetFont("³Ø½¼Lv2°íµñ");
	FontNameRender->GetTransform()->SetLocalPosition(float4(-282, 63, -1));
	FontNameRender->SetScale(20);
	FontNameRender->SetColor(float4(0.78039f, 0.72549f, 0.67058f, 1));

	FontTextRender = CreateComponent<ContentUIFontRenderer>();
	FontTextRender->SetFont("³Ø½¼Lv2°íµñ");
	FontTextRender->GetTransform()->SetLocalPosition(float4(-295, 25, -1));
	FontTextRender->SetScale(16);
	FontTextRender->SetColor(float4(0.58431f, 0.48627f, 0.3647f, 1));
	FontTextRender->Off();


}

void TalkBox::Update(float _DeltaTime)
{
	FontNameRender->SetText(NameText);

	if (true == IsReadEnd)
	{
		if (true == GameEngineInput::IsDown("TalkKey"))
		{
			if (nullptr != ReadEndCallback)
			{
				ReadEndCallback();
			}
		}

		return;
	}

	if (true == GameEngineInput::IsDown("TalkKey"))
	{
		BoostSpeed = 10.0f;
	}

	Progress += _DeltaTime * ReadSpeed * BoostSpeed / static_cast<float>(MainText.size());

	if (1.0f <= Progress)
	{
		Progress = 1.0f;
		IsReadEnd = true;
		ArrowPtr->On();
	}
	else
	{
		ArrowPtr->Off();
	}

	size_t ReadIndex = static_cast<size_t>(MainText.size() * Progress);

	if (0 == ReadIndex)
	{
		return;
	}

	if (false == FontTextRender->IsUpdate())
	{
		FontTextRender->On();
	}

	std::wstring ReadText;
	ReadText.resize(ReadIndex + 1);

	memcpy_s(ReadText.data(), ReadIndex * 2, MainText.data(), ReadIndex * 2);

	ReadText[ReadIndex] = L'\0';

	FontTextRender->SetText(GameEngineString::UniCodeToAnsi(ReadText));
}