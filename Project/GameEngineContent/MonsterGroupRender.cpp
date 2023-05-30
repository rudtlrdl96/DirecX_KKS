#include "PrecompileHeader.h"
#include "MonsterGroupRender.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "MonsterManager.h"
#include "MonsterDebugRender.h"
#include "MonsterData.h"

MonsterGroupRender::MonsterGroupRender()
{
}

MonsterGroupRender::~MonsterGroupRender()
{
}

void MonsterGroupRender::ShowGroup(const MonsterGroupMetaData& _GroupMetaData)
{
	if (static_cast<size_t>(-1) != OutlienActiveIndex)
	{
		MonsterRenders[OutlienActiveIndex]->SetOutlineColor(float4::Null);
		OutlienActiveIndex = static_cast<size_t>(-1);
	}


	size_t RednerCount = MonsterRenders.size();
	size_t GroupCount = _GroupMetaData.SpawnMonsters.size();

	if (RednerCount < GroupCount)
	{
		MonsterRenders.resize(GroupCount);

		for (size_t i = RednerCount; i < GroupCount; i++)
		{
			if (nullptr == MonsterRenders[i])
			{
				MonsterRenders[i] = GetLevel()->CreateActor<MonsterDebugRender>();
				MonsterRenders[i]->GetTransform()->SetParent(GetTransform());
			}
		}
	}

	for (size_t i = GroupCount; i < RednerCount; i++)
	{
		MonsterRenders[i]->Off();
	}

	for (size_t i = 0; i < MonsterRenders.size(); i++)
	{
		const MonsterData& Data =ContentDatabase<MonsterData, LevelArea>::GetData(_GroupMetaData.SpawnMonsters[i].Index);
		MonsterRenders[i]->SetScaleToTexture(Data.ImageName);
		MonsterRenders[i]->GetTransform()->SetLocalPosition(_GroupMetaData.SpawnMonsters[i].SpawnPos);
	}

	OutlienActiveIndex = static_cast<size_t>(_GroupMetaData.GUI_SelectMonster);

	if (0 <= OutlienActiveIndex && MonsterRenders.size() > OutlienActiveIndex)
	{
		MonsterRenders[OutlienActiveIndex]->SetOutlineColor(float4(1, 1, 0, 1));
	}
	else
	{
		OutlienActiveIndex = static_cast<size_t>(-1);
	}
}

void MonsterGroupRender::Start()
{
	MonsterRenders.reserve(16);
}
