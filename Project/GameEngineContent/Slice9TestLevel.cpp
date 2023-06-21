#include "PrecompileHeader.h"
#include "Slice9TestLevel.h"
#include "ContentSlice9Renderer.h"
#include "ContentSlice9UIRenderer.h"

Slice9TestLevel::Slice9TestLevel()
{
}

Slice9TestLevel::~Slice9TestLevel()
{
}

void Slice9TestLevel::Start()
{
	ContentLevel::Start();

	if (nullptr == GameEngineTexture::Find("SpeechBubble.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble_Large.png").GetFullPath());
	}

	TestActor = CreateActor<GameEngineActor>();
	SliceRender = TestActor->CreateComponent<ContentSlice9Renderer>();

	SliceRender->SetTextureAndSlice("SpeechBubble.png", 0.1f, 0.9f, 0.1f, 0.9f);

}
