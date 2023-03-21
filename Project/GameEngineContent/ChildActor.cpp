#include "ChildActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "VertexActor.h"


ChildActor::ChildActor()
{
}

ChildActor::~ChildActor()
{
}

void ChildActor::Start()
{
	SetPos({ 200, 0 });
}

void ChildActor::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsPress("ChildScaleUp"))
	{
		Scale += _DeltaTime;
	}
	if (true == GameEngineInput::IsPress("ChildScaleDown"))
	{
		Scale -= _DeltaTime;
	}
	if (true == GameEngineInput::IsPress("ChildAnlgeUp"))
	{
		Angle += _DeltaTime * 45.0f;

		if (360.0f < Angle)
		{
			Angle -= 360.0f;
		}
	}
	if (true == GameEngineInput::IsPress("ChildAnlgeDown"))
	{
		Angle -= _DeltaTime * 45.0f;

		if (0.0f > Angle)
		{
			Angle += 360.0f;
		}
	}
}

void ChildActor::Render(float _DeltaTime)
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
	float4 ParentPos = GetParent()->GetPos();

	VertexActor* Parent = static_cast<VertexActor*>(GetParent());

	for (size_t i = 0; i < VertexCount; i++)
	{
		float4 VertexPos = Vertexs[i];

		// 자기 자신
		VertexPos *= Scale;
		VertexPos.RotaitonZDeg(Angle);
		VertexPos += ActorPos;

		// 부모
		VertexPos *= Parent->Scale;
		VertexPos.RotaitonZDeg(Parent->Angle);
		VertexPos += ParentPos;

		VertexPoint[i] = VertexPos.ToWindowPOINT();
	}

	Polygon(DoubleBuffer, VertexPoint, VertexCount);
}
