#include "PrecompileHeader.h"
#include "TalkBox.h"
#include "GameEngineActorGUI.h"

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
	MainText = _MainText;
	Progress = 0.0f;
	IsReadEnd = false;
	ReadEndCallback = _Callback;
}

void TalkBox::Start()
{
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
	Render->PipeSetting("2DTexture_ColorLight");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->SetScaleToTexture("TalkBox.png");

	DebugGUI = GameEngineGUI::FindGUIWindowConvert<TalkboxDebugGUI>("TalkboxDebugGUI");
	DebugGUI->On();

	NameTagPtr = GetLevel()->CreateActor<TalkNameTag>();
	NameTagPtr->GetTransform()->SetParent(GetTransform());
	NameTagPtr->GetTransform()->SetLocalPosition(float4(-310, 50, -0.1f));
	NameTagPtr->SetFontSize(20);
	NameTagPtr->SetFontInterval(10);
}

void TalkBox::Update(float _DeltaTime)
{
	DebugGUI->SetNameText(NameText);

	if (true == IsReadEnd)
	{
		return;
	}

	Progress += _DeltaTime * ReadSpeed / static_cast<float>(MainText.size());

	if (1.0f <= Progress)
	{
		Progress = 1.0f;
		IsReadEnd = true;
	}

	size_t ReadIndex = static_cast<size_t>(MainText.size() * Progress);

	if (0 == ReadIndex)
	{
		return;
	}

	std::wstring ReadText;
	ReadText.resize(ReadIndex + 1);

	memcpy_s(ReadText.data(), ReadIndex * 2, MainText.data(), ReadIndex * 2);

	ReadText[ReadIndex] = L'\0';

	DebugGUI->SetMainText(GameEngineString::UniCodeToAnsi(ReadText));
}
