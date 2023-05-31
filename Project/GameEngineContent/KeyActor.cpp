#include "PrecompileHeader.h"
#include "KeyActor.h"

KeyActor::KeyActor()
{
}

KeyActor::~KeyActor()
{
}

void KeyActor::Start()
{
	KeyRender = CreateComponent<ContentSpriteRenderer>();
	KeyRender->PipeSetting("2DTexture_ColorLight");
	KeyRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	KeyRender->Off();

	if (nullptr == GameEngineTexture::Find("KeyUI_A.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");
		Path.Move("Key");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}
}