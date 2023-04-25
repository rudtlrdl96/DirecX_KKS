#include "PrecompileHeader.h"
#include "DebugSpriteActor.h"
#include <GameEnginePlatform/GameEngineInput.h>

DebugSpriteActor::DebugSpriteActor()
{
}

DebugSpriteActor::~DebugSpriteActor()
{
}

void DebugSpriteActor::Start()
{
	if (false == GameEngineInput::IsKey("DebugMoveX++"))
	{
		GameEngineInput::CreateKey("DebugMoveUp", VK_UP);
		GameEngineInput::CreateKey("DebugMoveDown", VK_DOWN);
		GameEngineInput::CreateKey("DebugMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("DebugMoveRight", VK_RIGHT);
	}

	SpriteRender = CreateComponent<GameEngineSpriteRenderer>();
	SpriteRender->GetTransform()->SetLocalScale({100, 100});
}

void DebugSpriteActor::Update(float _DeltaTime)
{
	float MoveDis = _DeltaTime * MoveSpeed;

	if (true == GameEngineInput::IsPress("DebugMoveUp"))
	{
		GetTransform()->AddWorldPosition({ 0, MoveDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveDown"))
	{
		GetTransform()->AddWorldPosition({ 0, -MoveDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveLeft"))
	{
		GetTransform()->AddWorldPosition({ -MoveDis, 0, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveRight"))
	{
		GetTransform()->AddWorldPosition({ MoveDis, 0, 0 });
	}
}
