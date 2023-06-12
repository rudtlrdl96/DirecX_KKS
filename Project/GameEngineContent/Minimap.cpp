#include "PrecompileHeader.h"
#include "Minimap.h"
#include "ContentUIRender.h"

Minimap::Minimap()
{
}

Minimap::~Minimap()
{
}

void Minimap::Start()
{
	if (nullptr == GameEngineTexture::Find("Minimap_Frame.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Minimap_Frame.png").GetFullPath());
	}

	MinimapFrameRender = CreateComponent<ContentUIRender>();
	MinimapFrameRender->PipeSetting("2DTexture_Color");
	MinimapFrameRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MinimapFrameRender->SetScaleToTexture("Minimap_Frame.png");
	float4 FrameScale = MinimapFrameRender->GetTransform()->GetLocalScale();
	MinimapFrameRender->GetTransform()->SetLocalScale(FrameScale * 2.0f);
}
