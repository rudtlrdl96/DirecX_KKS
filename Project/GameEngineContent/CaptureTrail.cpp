#include "PrecompileHeader.h"
#include "CaptureTrail.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "CaptureRenderer.h"

CaptureTrail::CaptureTrail()
{
	WaitRenders.reserve(16);
}

CaptureTrail::~CaptureTrail()
{
}

void CaptureTrail::SetTime(float _Time)
{
	Time = _Time;
}

void CaptureTrail::SetColor(const float4& _StartColor, const float4& _EndColor)
{
	StartColor = _StartColor;
	EndColor = _EndColor;
}

std::shared_ptr<CaptureRenderer> CaptureTrail::PlayTrail(const std::string_view& _TextureName, const float4& _AtlasData, bool _IsFlipX, float _ScaleRatio /*= 1.0f*/)
{
	if (0 == WaitRenders.size())
	{
		std::shared_ptr<CaptureRenderer> NewRender = GetLevel()->CreateActor<CaptureRenderer>();
		WaitRenders.push_back(NewRender);
	}

	std::shared_ptr<CaptureRenderer> WaitRender = WaitRenders.back();
	WaitRenders.pop_back();

	WaitRender->SetTexture(_TextureName, _AtlasData, _ScaleRatio);
	WaitRender->Play(StartColor, EndColor, Time);
	WaitRender->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	if (true == _IsFlipX)
	{
		WaitRender->GetTransform()->SetLocalNegativeScaleX();
	}
	else
	{
		WaitRender->GetTransform()->SetLocalPositiveScaleX();
	}

	PlayRenders.push_back(WaitRender);

	return WaitRender;
}

void CaptureTrail::Update(float _DeltaTime)
{
	std::list<std::shared_ptr<CaptureRenderer>>::iterator LoopIter = PlayRenders.begin();
	std::list<std::shared_ptr<CaptureRenderer>>::iterator EndIter = PlayRenders.end();

	float TrailZ = GetTransform()->GetWorldPosition().z;
	int CountCheck = 1;

	while (LoopIter != EndIter)
	{
		if (false == (*LoopIter)->IsPlaying())
		{
			WaitRenders.push_back((*LoopIter));
			LoopIter = PlayRenders.erase(LoopIter);
		}
		else
		{
			GameEngineTransform* RenderTrans = (*LoopIter)->GetTransform();

			float4 RenderPos = RenderTrans->GetWorldPosition();
			RenderPos.z = TrailZ + (CountCheck * 0.1f);
			RenderTrans->SetWorldPosition(RenderPos);

			++CountCheck;
			++LoopIter;
		}
	}

	
}
