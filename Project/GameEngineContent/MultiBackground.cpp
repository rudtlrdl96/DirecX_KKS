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

	_Desc.Center.z = GetTransform()->GetWorldPosition().z + _Depth * 1000;

	BackgroundBuffer[_Depth] = GetLevel()->CreateActor<Background>();
	BackgroundBuffer[_Depth]->Init(_Desc);
}