#include "PrecompileHeader.h"
#include "MouseCursorFollowTex.h"
#include <GameEngineCore/GameEngineLevel.h>

MouseCursorFollowTex::MouseCursorFollowTex()
{
}

MouseCursorFollowTex::~MouseCursorFollowTex()
{
}

void MouseCursorFollowTex::SetTexture(const std::string_view& _TextureName)
{
	if (nullptr == CursorTex)
	{
		MsgAssert_Rtti<MouseCursorFollowTex>(" - 랜더러를 생성하지 않고 사용하려 했습니다");
	}

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_TextureName);

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<MouseCursorFollowTex>(" - 존재하지 않는 텍스쳐로 설정하려 했습니다");
	}

	float4 TextureScale = float4::Zero;

	TextureScale.x = static_cast<float>(FindTex->GetWidth());
	TextureScale.y = static_cast<float>(FindTex->GetHeight());
	TextureScale.z = 1;

	CursorTex->SetTexture(_TextureName);
	CursorTex->GetTransform()->SetWorldScale(TextureScale);
	CursorTex->On();
}

void MouseCursorFollowTex::Start()
{
	CursorTex = CreateComponent<GameEngineSpriteRenderer>();
	CursorTex->SetTexture("Empty.png");
	CursorTex->Off();
}

void MouseCursorFollowTex::Update(float _DeltaTime)
{
	float4 MousePos = ContentFunc::GetMousePos(GetLevel()->GetMainCamera());

	GetTransform()->SetWorldPosition(MousePos);
}
