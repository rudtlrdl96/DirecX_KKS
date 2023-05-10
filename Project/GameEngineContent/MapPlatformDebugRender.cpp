#include "PrecompileHeader.h"
#include "MapPlatformDebugRender.h"

MapPlatformDebugRender::MapPlatformDebugRender()
{
}

MapPlatformDebugRender::~MapPlatformDebugRender()
{
}

void MapPlatformDebugRender::SetTargetPlatform(MapPlatform* _TargetPaltform)
{
	ParentPlatform = _TargetPaltform;
}

void MapPlatformDebugRender::Start()
{
	DebugRender = CreateComponent<GameEngineSpriteRenderer>();
	DebugRender->SetPipeLine("2DTexture_ColorLight");
	DebugRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", DebugBuffer);
	DebugRender->SetTexture("Debug_1_MapToolEmpty.png");
}

void MapPlatformDebugRender::Update(float _DeltaTime)
{
	if (nullptr == ParentPlatform)
	{
		Death();
		return;
	}

	if (false == ParentPlatform->IsDebug())
	{
		Death();
		return;
	}

	if (nullptr == DebugRender)
	{
		MsgAssert_Rtti<MapPlatformDebugRender>(" - DebugRender가 생성되지 않았습니다.");
		return;
	}

	switch (ParentPlatform->Desc.Type)
	{
	case MapPlatform::PlatformType::Normal:
		DebugBuffer.Color = float4(-1, 1, -1, 1);
		break;

	case MapPlatform::PlatformType::Half:
		DebugBuffer.Color = float4(1, -1, 0, 1);
		break;
	default:
		break;
	}

	DebugRender->GetTransform()->SetLocalScale(ParentPlatform->Desc.Scale);
}
