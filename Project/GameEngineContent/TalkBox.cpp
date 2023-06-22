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

void TalkBox::ActiveTalkBox(const std::string_view& _Name, const float4& _NamePivot /*= float4::Zero*/, const float4& _ForceSize /*= float4::Zero*/)
{ 
	NameText = _Name;
	NameTagPtr->SetNameTag(NameText, _NamePivot, _ForceSize);
	On();
}

void TalkBox::SetMainText(const std::wstring_view& _MainText, std::function<void()> _Callback)
{
	BoostSpeed = 1.0f;
	MainText = _MainText;
	Progress = 0.0f;
	IsReadEnd = false;
	ReadEndCallback = _Callback;

	float TextureSclaeX = 610.0f;
	float CurX = 0.0f;
	float FontX = FontSize * 0.7f;

	for (size_t i = 0; i < MainText.size(); i++)
	{
		CurX += FontX;

		if (MainText[i] == L'\n')
		{
			CurX = 0.0f;
			continue;
		}

		if (CurX + FontX >= TextureSclaeX)
		{
			CurX = 0.0f;

			MainText.insert(MainText.begin() + i, L'\n');
		}
	}
}

#include "GameEngineActorGUI.h"

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
	NameTagPtr->SetFontInterval(21);

	FontTextRender = CreateComponent<ContentUIFontRenderer>();
	FontTextRender->SetFont("³Ø½¼Lv2°íµñ");
	FontTextRender->GetTransform()->SetLocalPosition(float4(-300, 25, -1));
	FontTextRender->SetScale(FontSize);
	FontTextRender->SetColor(float4(0.58431f, 0.48627f, 0.3647f, 1));
	FontTextRender->Off();
}

void TalkBox::Update(float _DeltaTime)
{
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