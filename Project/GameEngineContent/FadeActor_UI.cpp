#include "PrecompileHeader.h"
#include "FadeActor_UI.h"
#include "ContentUIRender.h"

FadeActor_UI::FadeActor_UI()
{
}

FadeActor_UI::~FadeActor_UI()
{
}

void FadeActor_UI::Start()
{
	MainRenderer = CreateComponent<ContentUIRender>();
	MainRenderer->PipeSetting("2DTexture_Color");
	MainRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MainRenderer->SetTexture("FadeImage.png");
	MainRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	MainRenderer->GetTransform()->SetLocalPosition({ 0, 0, 0, 1 });
}
