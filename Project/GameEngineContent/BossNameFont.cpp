#include "PrecompileHeader.h"
#include "BossNameFont.h"

BossNameFont::BossNameFont()
{
}

BossNameFont::~BossNameFont()
{
}

void BossNameFont::ShowBossName(const std::string_view& _Name, const std::string_view& _Note, std::function<void()> _EndCallback /*= nullptr*/)
{
	EndCallback = _EndCallback;

	FontRender->SetText(_Name);
	FontRender->SetColor(StartColor);
	FontRender->On();	
	
	NoteRender->SetText(_Note);
	NoteRender->SetColor(StartColor);
	NoteRender->On();

	FontState = State::FadeIn;

	ProgressTime = 0.0f;
}

void BossNameFont::Start()
{
	FontRender = CreateComponent<ContentUIFontRenderer>();
	FontRender->GetTransform()->SetLocalPosition(float4(0, -20, 0));
	FontRender->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	FontRender->SetScale(45);
	FontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_RIGHT | FW1_VCENTER));
	FontRender->SetColor(float4(0.98f, 0.98f, 0.96f, 1));
	FontRender->Off();

	NoteRender = CreateComponent<ContentUIFontRenderer>();
	NoteRender->GetTransform()->SetLocalPosition(float4(0, 20, 0));
	NoteRender->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	NoteRender->SetScale(28);
	NoteRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_RIGHT | FW1_VCENTER));
	NoteRender->SetColor(float4(0.98f, 0.98f, 0.96f, 1));
	NoteRender->Off();
}


void BossNameFont::Update(float _DeltaTime)
{
	switch (FontState)
	{
	case BossNameFont::State::None:
		break;
	case BossNameFont::State::FadeIn:
		ProgressTime += _DeltaTime * 0.5f;

		FontRender->SetColor(float4::LerpClamp(StartColor, EndColor, ProgressTime));
		NoteRender->SetColor(float4::LerpClamp(StartColor, EndColor, ProgressTime));

		if (1.5f <= ProgressTime)
		{
			FontState = State::FadeOut;
			ProgressTime = 0.0f;
		
			if (nullptr != EndCallback)
			{
				EndCallback();
			}
		}

		break;
	case BossNameFont::State::FadeOut:
		ProgressTime += _DeltaTime * 0.5f;

		FontRender->SetColor(float4::LerpClamp(EndColor, StartColor, ProgressTime));
		NoteRender->SetColor(float4::LerpClamp(EndColor, StartColor, ProgressTime));

		if (1.0f <= ProgressTime)
		{
			FontState = State::None;
			ProgressTime = 0.0f;

			FontRender->Off();
			NoteRender->Off();
		}
		break;
	default:
		break;
	}
}
