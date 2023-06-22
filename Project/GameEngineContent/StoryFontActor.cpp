#include "PrecompileHeader.h"
#include "StoryFontActor.h"
#include "ContentUIFontRenderer.h"

StoryFontActor::StoryFontActor()
{
}

StoryFontActor::~StoryFontActor()
{
}

void StoryFontActor::WriteText(std::vector<StoryFontParameter> _TextParameter)
{
	Reset();

	TextRender.resize(_TextParameter.size());

	for (size_t i = 0; i < TextRender.size(); i++)
	{
		float PosX = _TextParameter[i].PosX;
		float PosY = FontSize * 1.4f * -_TextParameter[i].Line;

		TextRender[i] = CreateComponent<ContentUIFontRenderer>();
		TextRender[i]->GetTransform()->SetParent(GetTransform());	
		TextRender[i]->SetFont("³Ø½¼Lv2°íµñ");
		TextRender[i]->GetTransform()->SetLocalPosition({ PosX , PosY });
		TextRender[i]->SetScale(FontSize);
		TextRender[i]->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_VCENTER | FW1_TEXT_FLAG::FW1_CENTER));
		TextRender[i]->SetText(_TextParameter[i].StoryText);
		TextRender[i]->Off();
	}

	Index = 0;
	ReadProgress = 0.0f;
	IsRead = true;
}

void StoryFontActor::ReadText()
{
	IsRead = true;
	ReadProgress = 0.0f;
	++Index;

	for (size_t i = 0; i < Index; i++)
	{
		TextRender[i]->SetColor(FontColorFadeEnd);
	}
}

void StoryFontActor::Reset()
{
	Index = 0;

	for (size_t i = 0; i < TextRender.size(); i++)
	{
		if (nullptr != TextRender[i])
		{
			TextRender[i]->Death();
			TextRender[i] = nullptr;
		}
	}

	TextRender.clear();
}

void StoryFontActor::SkipText()
{
	for (size_t i = 0; i < TextRender.size(); i++)
	{
		TextRender[i]->SetColor(FontColorFadeEnd);
		TextRender[i]->On();
	}

	Index = TextRender.size();
}

void StoryFontActor::Update(float _DeltaTime)
{
	if (false == IsRead)
	{
		return;
	}

	ReadProgress += _DeltaTime * FadeSpeed;

	if (Index >= TextRender.size())
	{
		return;
	}

	TextRender[Index]->On();
	TextRender[Index]->SetColor(
		float4::LerpClamp(FontColorFadeStart, FontColorFadeEnd, ReadProgress));

	if (1.0f <= ReadProgress)
	{
		IsRead = false;
	}
}