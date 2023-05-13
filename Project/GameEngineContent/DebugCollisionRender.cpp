#include "PrecompileHeader.h"
#include "DebugCollisionRender.h"

DebugCollisionRender::DebugCollisionRender()
{
}

DebugCollisionRender::~DebugCollisionRender()
{
}

void DebugCollisionRender::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->SetTexture("Empty.png");
}

void DebugCollisionRender::Update(float _DeltaTime)
{
	switch (Type)
	{
	case DeubgColType::Box:
		Render->SetTexture("BoxCol.png");
		Render->GetTransform()->SetLocalScale(Size);
		break;
	case DeubgColType::Sphere:
		Render->SetTexture("SphereCol.png");
		Render->GetTransform()->SetLocalScale(float4(Size.x, Size.x, Size.z));
		break;
	default:
		break;
	}
}
