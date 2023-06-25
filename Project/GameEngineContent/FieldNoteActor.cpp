#include "PrecompileHeader.h"
#include "FieldNoteActor.h"

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

void FieldNoteActor::AddKeyImage(const std::string_view& _KeyImage, const float4& _Pos)
{
	std::shared_ptr<GameEngineSpriteRenderer> NewImageRender = CreateComponent<GameEngineSpriteRenderer>();

	NewImageRender->GetTransform()->SetLocalPosition(_Pos);
	NewImageRender->SetScaleToTexture(_KeyImage);
	float4 Scale = NewImageRender->GetTransform()->GetLocalScale();
	NewImageRender->GetTransform()->SetLocalScale(Scale * 1.5f);

	KeyImageRenders.push_back(NewImageRender);
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
	TextRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));
	TextRender->SetScale(17);
	TextRender->SetColor(float4(1.0f, 1.0f, 1.0f, 1));
}
