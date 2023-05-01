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

void CaptureTrail::PlayTrail(const std::string_view& _TextureName, const float4& _Size /*= float4::Zero*/)
{
	if (0 == WaitRenders.size())
	{
		std::shared_ptr<CaptureRenderer> NewRender = GetLevel()->CreateActor<CaptureRenderer>();
		WaitRenders.push_back(NewRender);
	}

	std::shared_ptr<CaptureRenderer> WaitRender = WaitRenders.back();
	WaitRenders.pop_back();

	WaitRender->SetTexture(_TextureName, _Size);
	WaitRender->Play(StartColor, EndColor, Time);
	WaitRender->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition());

	PlayRenders.push_back(WaitRender);
}

void CaptureTrail::Update(float _DeltaTime)
{
	std::list<std::shared_ptr<CaptureRenderer>>::iterator LoopIter = PlayRenders.begin();
	std::list<std::shared_ptr<CaptureRenderer>>::iterator EndIter = PlayRenders.end();

	while (LoopIter != EndIter)
	{
		if (false == (*LoopIter)->IsPlaying())
		{
			WaitRenders.push_back((*LoopIter));
			LoopIter = PlayRenders.erase(LoopIter);
		}
		else
		{
			++LoopIter;
		}
	}
}
