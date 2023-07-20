#include "PrecompileHeader.h"
#include "MouseCursor.h"
#include "ContentFadeRender.h"

MouseCursor::MouseCursor()
{
}

MouseCursor::~MouseCursor()
{
}

void MouseCursor::Start()
{
	if (nullptr == GameEngineTexture::Find("Mouse_Cursor.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Mouse_Cursor.png").GetFullPath());
	}

	CursorRender = CreateComponent<ContentFadeRender>();
	CursorRender->PipeSetting("2DTexture_Color");
	CursorRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	CursorRender->SetScaleToTexture("Mouse_Cursor.png");
}

void MouseCursor::Update(float _DeltaTime)
{
	float4 Pos = GetContentLevel()->GetMousePos((int)CameraOrder::Fade);
	float4 CursorScale = CursorRender->GetTransform()->GetWorldScale();

	if (Pos != PrevPos)
	{
		HideTime = 0.0f;
	}
	else
	{
		HideTime += _DeltaTime;
	}

	if (3.0f <= HideTime)
	{
		CursorRender->Off();
	}
	else
	{
		CursorRender->On();
	}

	GetTransform()->SetWorldPosition(Pos + float4(CursorScale.hx(), -CursorScale.hy()));

	PrevPos = Pos;

}
