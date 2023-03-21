#include "VertexActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ChildActor.h"

VertexActor::VertexActor()
{
}

VertexActor::~VertexActor()
{
}

void VertexActor::Start()
{
	SetPos({300, 300});

	SetName("Parent");
	ChildPtr = static_cast<GameEngineLevel*>(GetParent())->CreateActor<ChildActor>("Child");
	ChildPtr->SetParent(this);
}

void VertexActor::Update(float _DeltaTime)
{

	if (true == GameEngineInput::IsPress("ScaleUp"))
	{
		Scale += _DeltaTime;
	}
	if (true == GameEngineInput::IsPress("ScaleDown"))
	{
		Scale -= _DeltaTime;
	}	
	if (true == GameEngineInput::IsPress("AngleUp"))
	{
		Angle += _DeltaTime * 45.0f;

		if (360.0f < Angle)
		{
			Angle -= 360.0f;
		}
	}	
	if (true == GameEngineInput::IsPress("AngleDown"))
	{
		Angle -= _DeltaTime * 45.0f;

		if (0.0f > Angle)
		{
			Angle += 360.0f;
		}
	}

	if (true == GameEngineInput::IsPress("MoveUp"))
	{
		SetMove(float4::Up * 50.0f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("MoveDown"))
	{
		SetMove(float4::Down * 50.0f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("MoveLeft"))
	{
		SetMove(float4::Left * 50.0f * _DeltaTime);
	}

	if (true == GameEngineInput::IsPress("MoveRight"))
	{
		SetMove(float4::Right * 50.0f * _DeltaTime);
	}
}

void VertexActor::Render(float _DeltaTime)
{
	const int VertexCount = 4;

	float4 Vertexs[VertexCount];
	POINT VertexPoint[VertexCount];

	Vertexs[0] = { -50, -50 };
	Vertexs[1] = { 50, -50 };
	Vertexs[2] = { 50, 50 };
	Vertexs[3] = { -50, 50 };

	HDC DoubleBuffer = GameEngineWindow::GetWindowBackBufferHdc();

	float4 ActorPos = GetPos();

	std::string Name = GetParent()->GetName();

	for (size_t i = 0; i < VertexCount; i++)
	{
		float4 VertexPos = Vertexs[i];

		VertexPos *= Scale;

		VertexPos.RotaitonZDeg(Angle);

		VertexPos += ActorPos;

		VertexPoint[i] = VertexPos.ToWindowPOINT();
	}

	Polygon(DoubleBuffer, VertexPoint, VertexCount);
}
