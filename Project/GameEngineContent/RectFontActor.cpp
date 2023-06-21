#include "PrecompileHeader.h"
#include "RectFontActor.h"

RectFontActor::RectFontActor()
{
}

RectFontActor::~RectFontActor()
{
}

void RectFontActor::Reset()
{
	TextRender->Off();
	RemoveText();
}

void RectFontActor::WriteText(const std::string_view& _Text)
{
}

void RectFontActor::RemoveText()
{
	Text = "";
	ReadIndex = 0;
}

void RectFontActor::SkipText()
{
}

void RectFontActor::Start()
{
	TextRender = CreateComponent<GameEngineFontRenderer>();
}