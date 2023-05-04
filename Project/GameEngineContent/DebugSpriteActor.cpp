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
		GameEngineInput::CreateKey("DebugMoveUp", VK_UP);
		GameEngineInput::CreateKey("DebugMoveDown", VK_DOWN);
		GameEngineInput::CreateKey("DebugMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("DebugMoveRight", VK_RIGHT);

		GameEngineInput::CreateKey("DebugRotX+", 'W');
		GameEngineInput::CreateKey("DebugRotX-", 'S');
		GameEngineInput::CreateKey("DebugRotY+", 'A');
		GameEngineInput::CreateKey("DebugRotY-", 'D');
		GameEngineInput::CreateKey("DebugRotZ+", 'Q');
		GameEngineInput::CreateKey("DebugRotZ-", 'E');
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

	if (true == GameEngineInput::IsPress("DebugMoveUp"))
	{
		GetTransform()->AddLocalPosition({ 0, MoveDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveDown"))
	{
		GetTransform()->AddLocalPosition({ 0, -MoveDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveLeft"))
	{
		GetTransform()->AddLocalPosition({ -MoveDis, 0, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugMoveRight"))
	{
		GetTransform()->AddLocalPosition({ MoveDis, 0, 0 });
	}

	float RotDis = _DeltaTime * RotSpeed;
	if (true == GameEngineInput::IsPress("DebugRotX+"))
	{
		GetTransform()->AddLocalRotation({ RotDis, 0, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugRotX-"))
	{
		GetTransform()->AddLocalRotation({ -RotDis, 0, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugRotY+"))
	{
		GetTransform()->AddLocalRotation({ 0, RotDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugRotY-"))
	{
		GetTransform()->AddLocalRotation({ 0, -RotDis, 0 });
	}
	else if (true == GameEngineInput::IsPress("DebugRotZ+"))
	{
		GetTransform()->AddLocalRotation({ 0, 0, RotDis });
	}
	else if (true == GameEngineInput::IsPress("DebugRotZ-"))
	{
		GetTransform()->AddLocalRotation({ 0, 0, -RotDis });
	}
}
