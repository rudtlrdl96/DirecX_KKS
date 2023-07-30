#include "PrecompileHeader.h"
#include "NPC_TalkBox.h"
#include "TalkArrow.h"

NPC_TalkBox::NPC_TalkBox()
{
}

NPC_TalkBox::~NPC_TalkBox()
{
}

void NPC_TalkBox::SetTalkBoxName(const std::string_view& _Name, const float4& _NamePivot /*= float4::Zero*/, const float4& _ForceSize /*= float4::Zero*/)
{
	NameText = _Name;
	NameTagPtr->SetNameTag(NameText, _NamePivot, _ForceSize);
}

void NPC_TalkBox::AddMainText(const std::wstring_view& _MainText)
{
	std::wstring AddText = _MainText.data();

	float TextureSclaeX = 610.0f;
	float CurX = 0.0f;
	float FontX = FontSize * 0.7f;

	for (size_t i = 0; i < AddText.size(); i++)
	{
		CurX += FontX;

		if (AddText[i] == L'\n')
		{
			CurX = 0.0f;
			continue;
		}

		if (CurX + FontX >= TextureSclaeX)
		{
			CurX = 0.0f;

			AddText.insert(AddText.begin() + i, L'\n');
		}
	}

	TalkList.push_back(AddText);
}

void NPC_TalkBox::ClearMainText()
{
	TalkList.clear();
}

void NPC_TalkBox::SetNextText()
{
	FontTextRender->SetText("");

	++ReadTalkIndex;

	if (ReadTalkIndex >= TalkList.size())
	{
		ReadTalkIndex = 0;
	}

	MainText = TalkList[ReadTalkIndex];
	IsReadEnd = false;
	Progress = 0.0f;
	ReadSoundCount = 0;
	IsTalk = false;
	IsBoost = false;
	BoostSpeed = 1.0f;
}

void NPC_TalkBox::SetTalkMainText(const std::wstring_view& _Text, std::function<void()> _TalkEndCallback)
{
	FontTextRender->SetText("");
	MainText = _Text;
	IsReadEnd = false;
	Progress = 0.0f;
	ReadSoundCount = 0;
	IsTalk = true;
	IsBoost = false;
	BoostSpeed = 1.0f;
	TalkEndCallback = _TalkEndCallback;

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

void NPC_TalkBox::PlayText(const std::wstring_view& _Text)
{
	FontTextRender->SetText("");

	MainText = _Text;

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

	IsReadEnd = false;
	Progress = 0.0f;
	ReadSoundCount = 0;
	IsTalk = false;
	IsBoost = false;
	BoostSpeed = 1.0f;
}

void NPC_TalkBox::On()
{
	BaseContentActor::On();
	SetNextText();

	GetContentLevel()->CallEvent("StoryFadeIn");
	GetContentLevel()->CallEvent("PlayerInputLock");
	GetContentLevel()->CallEvent("PlayerFrameDisable");
	GetContentLevel()->CallEvent("MinimapOff");
	GetContentLevel()->CallEvent("GoodsUIOff");
	GetContentLevel()->CallEvent("UseKeyOff");
	ResetButton();
	YesOrNoDisable();

	IsYesOrNo = false;
}

void NPC_TalkBox::Off()
{
	BaseContentActor::Off();
	FontTextRender->Off();
}

void NPC_TalkBox::AddButton(const std::string_view& _Text, std::function<void()> _Callback)
{
	std::shared_ptr<TalkButton> NewTalkButton = GetLevel()->CreateActor<TalkButton>();

	NewTalkButton->GetTransform()->SetParent(ButtonPivot->GetTransform());
	NewTalkButton->GetTransform()->SetLocalPosition(ButtonInterval * static_cast<float>(TalkButtonActors.size()));

	NewTalkButton->SetText(_Text);
	NewTalkButton->AddCallback(_Callback);

	TalkButtonActors.push_back(NewTalkButton);
}

void NPC_TalkBox::ButtonActive()
{
	IsButtonActive = true;

	for (size_t i = 0; i < TalkButtonActors.size(); i++)
	{
		TalkButtonActors[i]->On();
	}
}

void NPC_TalkBox::ButtonDisable()
{
	IsButtonActive = false;

	for (size_t i = 0; i < TalkButtonActors.size(); i++)
	{
		TalkButtonActors[i]->Off();
	}
}

void NPC_TalkBox::YesOrNoActive(const std::wstring_view& _Text, std::function<void()> _YesCallback, std::function<void()> _NoCallback)
{
	PlayText(_Text);

	if (0 == YesOrNoButtonActors.size())
	{
		YesOrNoButtonActors.resize(2);

		std::shared_ptr<TalkButton> NoButton = GetLevel()->CreateActor<TalkButton>();

		NoButton->GetTransform()->SetParent(ButtonPivot->GetTransform());
		NoButton->GetTransform()->SetLocalPosition(ButtonInterval * 1);
		NoButton->SetText("아니요");

		YesOrNoButtonActors[0] = NoButton;

		std::shared_ptr<TalkButton> YesButton = GetLevel()->CreateActor<TalkButton>();

		YesButton->GetTransform()->SetParent(ButtonPivot->GetTransform());
		YesButton->GetTransform()->SetLocalPosition(ButtonInterval * 2);
		YesButton->SetText("예");

		YesOrNoButtonActors[1] = YesButton;
	}

	YesOrNoButtonActors[0]->AddCallback(_NoCallback);
	YesOrNoButtonActors[1]->AddCallback(_YesCallback);

	ButtonDisable();
	YesOrNoResetButton();
	
	for (size_t i = 0; i < YesOrNoButtonActors.size(); i++)
	{
		YesOrNoButtonActors[i]->On();
	}

	IsYesOrNo = true;
}

void NPC_TalkBox::YesOrNoDisable()
{
	for (size_t i = 0; i < YesOrNoButtonActors.size(); i++)
	{
		YesOrNoButtonActors[i]->Off();
	}

	IsYesOrNo = false;
}

void NPC_TalkBox::Start()
{
	ButtonPivot = CreateComponent<GameEngineComponent>();
	ButtonPivot->GetTransform()->SetLocalPosition(float4(440, -34, 0));

	if (false == GameEngineInput::IsKey("ButtonUp"))
	{
		GameEngineInput::CreateKey("ButtonUp", VK_UP);
		GameEngineInput::CreateKey("ButtonDown", VK_DOWN);
		GameEngineInput::CreateKey("ButtonUse", 'X');
		GameEngineInput::CreateKey("TalkCancel", 'C');
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

	Render = CreateComponent<ContentUIRender>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->SetScaleToTexture("TalkBox.png");

	NameTagPtr = GetLevel()->CreateActor<TalkNameTag>();
	NameTagPtr->GetTransform()->SetParent(GetTransform());
	NameTagPtr->GetTransform()->SetLocalPosition(float4(-310, 50, -0.1f));
	NameTagPtr->SetFontInterval(21);

	FontTextRender = CreateComponent<ContentUIFontRenderer>();
	FontTextRender->SetFont("넥슨Lv2고딕");
	FontTextRender->GetTransform()->SetLocalPosition(float4(-300, 25, -1));
	FontTextRender->SetScale(FontSize);
	FontTextRender->SetColor(float4(0.58431f, 0.48627f, 0.3647f, 1));
	FontTextRender->Off();

	ArrowPtr = GetLevel()->CreateActor<TalkArrow>();
	ArrowPtr->GetTransform()->SetParent(GetTransform());
	ArrowPtr->GetTransform()->SetLocalPosition(float4(285.0f, -35.0f, -0.1f));
	ArrowPtr->SetSpeed(1.5f);
	ArrowPtr->Off();

	AddButton("취소", [this]()
		{
			Off();
			GetContentLevel()->CallEvent("PlayerInputUnlock");
			GetContentLevel()->CallEvent("StoryFadeOut");
			GetContentLevel()->CallEvent("PlayerFrameActive");

			if (true == IsOffMinimapOn)
			{
				GetContentLevel()->CallEvent("MinimapOn");
			}

			GetContentLevel()->CallEvent("GoodsUIOn");
			GetContentLevel()->CallEvent("UseKeyOn");
		});
}

void NPC_TalkBox::Update(float _DeltaTime)
{
	if (true == IsYesOrNo)
	{
		if (true == GameEngineInput::IsDown("ButtonUp"))
		{
			YesOrNoButtonUp();
		}
		else if (true == GameEngineInput::IsDown("ButtonDown"))
		{
			YesOrNoButtonDown();
		}
		else if (true == GameEngineInput::IsUp("ButtonUse"))
		{
			YesOrNoButtonUse();
		}
		else if (true == GameEngineInput::IsUp("TalkCancel"))
		{
			YesOrNoButtonCancel();
		}
	}
	else if (true == IsButtonActive)
	{
		if (true == GameEngineInput::IsDown("ButtonUp"))
		{
			ButtonUp();
		}
		else if (true == GameEngineInput::IsDown("ButtonDown"))
		{
			ButtonDown();
		}
		else if (true == GameEngineInput::IsUp("ButtonUse"))
		{
			ButtonUse();
		}
		else if (true == GameEngineInput::IsUp("TalkCancel"))
		{
			ButtonCancel();
		}
	}

	if (false == IsTalk)
	{
		ArrowPtr->Off();
	}
	else if (true == GameEngineInput::IsDown("ButtonUse"))
	{
		BoostSpeed = 15.0f;
		IsBoost = true;

		if (1 <= ReadSoundCount)
		{
			GameEngineSound::Play("UI_Talk.wav");
			ReadSoundCount = 0;
		}
	}

	Progress += _DeltaTime * ReadSpeed * BoostSpeed / static_cast<float>(MainText.size());
		
	if (1.0f <= Progress)
	{
		Progress = 1.0f;
		IsReadEnd = true;

		BoostSpeed = 1.0f;
		IsBoost = false;

		if (true == IsTalk && true == GameEngineInput::IsDown("ButtonUse"))
		{
			if (nullptr == TalkEndCallback)
			{
				MsgAssert_Rtti<NPC_TalkBox>(" - NPC대화 : nullptr Callback을 설정했습니다");
				return;
			}

			TalkEndCallback();
			return;
		}

		if (true == IsTalk)
		{
			ArrowPtr->On();
		}
	}

	size_t ReadIndex = static_cast<size_t>(MainText.size() * Progress);

	if (0 == ReadIndex)
	{
		return;
	}

	if (PrevAddIndex != ReadIndex)
	{
		if (MainText[ReadIndex] != L'\n')
		{
			++ReadSoundCount;
			PrevAddIndex = static_cast<int>(ReadIndex);
		}
		else
		{
			ReadSoundCount = 0;
		}
	}

	if (false == IsBoost)
	{
		if (2 <= ReadSoundCount)
		{
			GameEngineSound::Play("UI_Talk.wav");
			ReadSoundCount = 0;
		}
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

void NPC_TalkBox::ButtonUp()
{
	TalkButtonActors[ButtonIndex]->HoverOff();
	++ButtonIndex;

	if (ButtonIndex >= TalkButtonActors.size())
	{
		ButtonIndex = 0;
	}

	TalkButtonActors[ButtonIndex]->HoverOn();
}

void NPC_TalkBox::ButtonDown()
{
	TalkButtonActors[ButtonIndex]->HoverOff();
	--ButtonIndex;

	if (ButtonIndex < 0)
	{
		ButtonIndex = static_cast<int>(TalkButtonActors.size() - 1);
	}

	TalkButtonActors[ButtonIndex]->HoverOn();
}

void NPC_TalkBox::ButtonUse()
{
	TalkButtonActors[ButtonIndex]->UseButton();	
}

void NPC_TalkBox::ButtonCancel()
{
	TalkButtonActors[0]->UseButton();
}

void NPC_TalkBox::ResetButton()
{
	for (size_t i = 0; i < TalkButtonActors.size(); i++)
	{
		TalkButtonActors[i]->HoverOff();
	}

	ButtonIndex = 0;
	TalkButtonActors[ButtonIndex]->HoverOn(); 
}

void NPC_TalkBox::YesOrNoButtonUp()
{
	YesOrNoButtonActors[YesOrNoButtoneIndex]->HoverOff();
	++YesOrNoButtoneIndex;

	if (YesOrNoButtoneIndex >= YesOrNoButtonActors.size())
	{
		YesOrNoButtoneIndex = 0;
	}

	YesOrNoButtonActors[YesOrNoButtoneIndex]->HoverOn();
}

void NPC_TalkBox::YesOrNoButtonDown()
{
	YesOrNoButtonActors[YesOrNoButtoneIndex]->HoverOff();
	--YesOrNoButtoneIndex;

	if (YesOrNoButtoneIndex < 0)
	{
		YesOrNoButtoneIndex = static_cast<int>(YesOrNoButtonActors.size() - 1);
	}

	YesOrNoButtonActors[YesOrNoButtoneIndex]->HoverOn();
}

void NPC_TalkBox::YesOrNoButtonUse()
{
	YesOrNoButtonActors[YesOrNoButtoneIndex]->UseButton();
}

void NPC_TalkBox::YesOrNoButtonCancel()
{
	YesOrNoButtonActors[0]->UseButton();
}

void NPC_TalkBox::YesOrNoResetButton()
{
	for (size_t i = 0; i < YesOrNoButtonActors.size(); i++)
	{
		YesOrNoButtonActors[i]->HoverOff();
	}

	YesOrNoButtoneIndex = 0;
	YesOrNoButtonActors[YesOrNoButtoneIndex]->HoverOn();
}