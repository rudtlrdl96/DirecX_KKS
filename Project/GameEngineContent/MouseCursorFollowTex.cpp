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
		MsgAssert_Rtti<MouseCursorFollowTex>(" - �������� �������� �ʰ� ����Ϸ� �߽��ϴ�");
	}

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find(_TextureName);

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<MouseCursorFollowTex>(" - �������� �ʴ� �ؽ��ķ� �����Ϸ� �߽��ϴ�");
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
