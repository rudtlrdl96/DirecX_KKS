#include "PrecompileHeader.h"
#include "MultiBackground.h"
#include <GameEngineCore/GameEngineLevel.h>

MultiBackground::MultiBackground()
{
}

MultiBackground::~MultiBackground()
{
}

void MultiBackground::CreateBackground(Background::BG_DESC& _Desc, int _Depth)
{
	if (BackgroundBuffer.find(_Depth) != BackgroundBuffer.end())
	{
		MsgAssert("중복된 뎁스의 백그라운드를 생성하려 했습니다.");
		return;
	}

	_Desc.Center.z = _Depth * 1000.0f;

	BackgroundBuffer[_Depth] = GetLevel()->CreateActor<Background>();
	BackgroundBuffer[_Depth]->Init(_Desc);
}

void MultiBackground::UpdateTargetPos(float _DeltaTime, const float4& _TargetPos)
{
	std::map<int, std::shared_ptr<Background>>::iterator LoopIter = BackgroundBuffer.begin();
	std::map<int, std::shared_ptr<Background>>::iterator EndIter = BackgroundBuffer.end();

	while (LoopIter != EndIter)
	{
		if (true == LoopIter->second->IsDeath())
		{
			LoopIter = BackgroundBuffer.erase(LoopIter);
			continue;
		}
		else
		{
			LoopIter->second->UpdateTargetPos(_DeltaTime, _TargetPos);
			++LoopIter;
		}
	}
}

void MultiBackground::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(static_cast<int>(BackgroundBuffer.size()));

	for (const std::pair<int, std::shared_ptr<Background>>& LoopRef : BackgroundBuffer)
	{
		_SaveSerializer.Write(LoopRef.first);
		LoopRef.second->SaveBin(_SaveSerializer);
	}
}

void MultiBackground::LoadBin(GameEngineSerializer& _SaveSerializer)
{
	int BackCount = 0;
	_SaveSerializer.Read(BackCount);

	for (int i = 0; i < BackCount; i++)
	{
		int Depth = 0;
		_SaveSerializer.Read(Depth);

		Background::BG_DESC LoadDesc = Background::LoadBin(_SaveSerializer);
		CreateBackground(LoadDesc, Depth);
	}
}
