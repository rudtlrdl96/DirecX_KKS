#include "PrecompileHeader.h"
#include "FieldNoteActor.h"
#include "KeyActor.h"

FieldNoteActor::FieldNoteActor()
{
}

FieldNoteActor::~FieldNoteActor()
{
}

void FieldNoteActor::SetText(const std::string_view& _Text)
{
	NoteText = _Text;
	TextRender->SetText(NoteText);
}

void FieldNoteActor::Start()
{
	if (nullptr == GameEngineTexture::Find("Interaction_BackGround.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Interaction_BackGround.png").GetFullPath());
	}

	BackRender = CreateComponent<ContentSpriteRenderer>();
	BackRender->PipeSetting("2DTexture_Color");
	BackRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	BackRender->SetScaleToTexture("Interaction_BackGround.png");

	float4 Sclae = BackRender->GetTransform()->GetLocalScale();

	Sclae.x *= 3.5f;
	Sclae.y *= 1.8f;

	BackRender->GetTransform()->SetLocalScale(Sclae);

	TextRender = CreateComponent<GameEngineFontRenderer>();
	TextRender->SetFont("³Ø½¼Lv2°íµñ");
	TextRender->GetTransform()->SetLocalPosition(float4(-38, 9, -0.1f));
	TextRender->SetScale(18);
	TextRender->SetColor(float4(1.0f, 1.0f, 1.0f, 1));
}
