#include "PrecompileHeader.h"
#include "PlayerSpawnPointRenderer.h"

PlayerSpawnPointRenderer::PlayerSpawnPointRenderer()
{
}

PlayerSpawnPointRenderer::~PlayerSpawnPointRenderer()
{
}

void PlayerSpawnPointRenderer::Start()
{

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("SkulIcon.png");

	if (nullptr == FindTex)
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("11_Tool");

		FindTex = GameEngineTexture::Load(Path.GetPlusFileName("SkulIcon.png").GetFullPath());
	}

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<PlayerSpawnPointRenderer>(" - 플레이어 위치 표시용 텍스쳐를 찾을 수 없습니다");
		return;
	}

	float4 TextureScale;

	TextureScale.x = static_cast<float>(FindTex->GetWidth());
	TextureScale.y = static_cast<float>(FindTex->GetHeight());

	TextureScale *= 0.15f;

	SpawnRender = CreateComponent<GameEngineSpriteRenderer>();
	SpawnRender->SetTexture("SkulIcon.png");
	SpawnRender->GetTransform()->SetLocalScale(TextureScale);

	SpawnRender->GetTransform()->SetLocalPosition(float4(0, TextureScale.hy(), 0));
}
