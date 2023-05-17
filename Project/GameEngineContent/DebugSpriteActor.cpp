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
	if (false == GameEngineInput::IsKey("DebugMoveUp"))
	{
		GameEngineInput::CreateKey("DebugMoveUp", 'W');
		GameEngineInput::CreateKey("DebugMoveDown", 'S');
		GameEngineInput::CreateKey("DebugMoveLeft", 'A');
		GameEngineInput::CreateKey("DebugMoveRight", 'D');
		GameEngineInput::CreateKey("DebugBoost", VK_LSHIFT);
	}

	SpriteRender = CreateComponent<GameEngineSpriteRenderer>();
	SpriteRender->GetTransform()->SetLocalScale({100, 100});
}

void DebugSpriteActor::Update(float _DeltaTime)
{
	if (true == UnMove)
	{
		return;
	}

	float MoveDis = _DeltaTime * MoveSpeed;

	if (true == GameEngineInput::IsPress("DebugBoost"))
	{
		MoveDis *= 2.0f;
	}

	if (true == GameEngineInput::IsPress("DebugMoveUp"))
	{
		GetTransform()->AddLocalPosition({ 0, MoveDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveDown"))
	{
		GetTransform()->AddLocalPosition({ 0, -MoveDis, 0 });
	}

	if (true == GameEngineInput::IsPress("DebugMoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0, 0 });
	}
}
