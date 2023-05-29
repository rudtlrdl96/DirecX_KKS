#include "PrecompileHeader.h"
#include "MonsterManager.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "CarleonRecruit.h"
#include "CarleonArcher.h"
#include "CarleonManAtArms.h"
#include "Ent.h"
#include "BlossomEnt.h"
#include "GiantEnt.h"
#include "RootEnt.h"
#include "FlameWizard.h"
#include "GlacialWizard.h"

void MonsterSpawnMetaData::MonsterSpawn(GameEngineLevel* _SpawnLevel, GameEngineTransform* _Parent)
{
	std::shared_ptr<BaseMonster> NewMonster = nullptr;

	switch (Index)
	{
	case 0: // Į���� �ź�
	{
		NewMonster = _SpawnLevel->CreateActor<CarleonRecruit>();
		break;
	}
	case 1: // Į���� �ü�
	{
		NewMonster = _SpawnLevel->CreateActor<CarleonArcher>();
		break;
	}
	case 106: // Į���� �ߺ���
	{
		NewMonster = _SpawnLevel->CreateActor<CarleonManAtArms>();
		break;
	}
	case 100: // ��Ʈ
	{
		NewMonster = _SpawnLevel->CreateActor<Ent>();
		break;
	}
	case 102: // �Ѹ� ��Ʈ
	{
		NewMonster = _SpawnLevel->CreateActor<RootEnt>();
		break;
	}
	case 103: // ������ (���̾�Ʈ ��Ʈ)
	{
		NewMonster = _SpawnLevel->CreateActor<GiantEnt>();
		break;
	}
	case 101: // �� ��Ʈ
	{
		NewMonster = _SpawnLevel->CreateActor<BlossomEnt>();
		break;
	}
	case 108: // ȭ�� ������
	{
		NewMonster = _SpawnLevel->CreateActor<FlameWizard>();
		break;
	}
	case 109: // ���� ������
	{
		NewMonster = _SpawnLevel->CreateActor<GlacialWizard>();
		break;
	}
	default:
		break;
	}

	if (nullptr == NewMonster)
	{
		MsgAssert_Rtti<MonsterSpawnMetaData>("���� �������� ���� ���͸� ��ȯ�Ϸ� �߽��ϴ�");
		return;
	}

	NewMonster->GetTransform()->SetParent(_Parent);
	NewMonster->GetTransform()->SetLocalPosition(SpawnPos);
}

void MonsterSpawnMetaData::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(&Index, sizeof(size_t));
	_SaveSerializer.Write(&SpawnPos, sizeof(float4));
}

void MonsterSpawnMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&Index, sizeof(size_t));
	_LoadSerializer.Read(&SpawnPos, sizeof(float4));
}

void MonsterGroupMetaData::WaveSpawn(GameEngineLevel* _SpawnLevel, GameEngineTransform* _Parent)
{
	if (true == IsSpawnEnd)
	{
		MsgAssert_Rtti<MonsterGroupMetaData>(" - ���� ���̺긦 �������� �ʰ� ��ȯ�Ϸ� �߽��ϴ�");
		return;
	}

	IsSpawnEnd = true;

	for (size_t i = 0; i < SpawnMonsters.size(); i++)
	{
		SpawnMonsters[i].MonsterSpawn(_SpawnLevel, _Parent);
	}
}

void MonsterGroupMetaData::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(&WaveNumber, sizeof(UINT));
	_SaveSerializer.Write(&IsCollision, sizeof(bool));
	_SaveSerializer.Write(&ColCenter, sizeof(float4));
	_SaveSerializer.Write(&ColScale, sizeof(float4));

	int SpawnMonsterCount = static_cast<int>(SpawnMonsters.size());

	_SaveSerializer.Write(&SpawnMonsterCount, sizeof(int));

	for (size_t i = 0; i < SpawnMonsters.size(); i++)
	{
		SpawnMonsters[i].SaveBin(_SaveSerializer);
	}
}

void MonsterGroupMetaData::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	IsSpawnEnd = false;

	_LoadSerializer.Read(&WaveNumber, sizeof(UINT));
	_LoadSerializer.Read(&IsCollision, sizeof(bool));
	_LoadSerializer.Read(&ColCenter, sizeof(float4));
	_LoadSerializer.Read(&ColScale, sizeof(float4));

	int SpawnMonsterCount = 0;

	_LoadSerializer.Read(&SpawnMonsterCount, sizeof(int));

	SpawnMonsters.resize(SpawnMonsterCount);

	for (size_t i = 0; i < SpawnMonsters.size(); i++)
	{
		SpawnMonsters[i].LoadBin(_LoadSerializer);
	}
}

MonsterManager::MonsterManager()
{
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	int WaveSize = static_cast<int>(WaveDatas.size());

	_SaveSerializer.Write(&WaveSize, sizeof(int));

	for (size_t i = 0; i < WaveDatas.size(); i++)
	{
		int GroupSize = static_cast<int>(WaveDatas[i].size());

		_SaveSerializer.Write(&GroupSize, sizeof(int));

		for (size_t j = 0; j < WaveDatas[i].size(); j++)
		{
			WaveDatas[i][j].SaveBin(_SaveSerializer);
		}
	}
}

void MonsterManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	int WaveSize = 0;
	_LoadSerializer.Read(&WaveSize, sizeof(int));

	WaveDatas.resize(WaveSize);

	for (size_t i = 0; i < WaveDatas.size(); i++)
	{
		int GroupSize = 0;
		_LoadSerializer.Read(&GroupSize, sizeof(int));

		WaveDatas[i].resize(GroupSize);

		for (size_t j = 0; j < WaveDatas[i].size(); j++)
		{
			WaveDatas[i][j].LoadBin(_LoadSerializer);
		}
	}

}

void MonsterManager::ShowGUI()
{
}

void MonsterManager::Start()
{
	WaveCollision = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WaveCollision->GetTransform()->SetWorldRotation(float4::Zero);
}

void MonsterManager::Update(float _DeltaTime)
{
	std::vector<std::vector<std::shared_ptr<BaseMonster>>>::iterator WaveLoopIter = MonsterActors.begin();
	std::vector<std::vector<std::shared_ptr<BaseMonster>>>::iterator WaveEndIter = MonsterActors.end();

	// ���� ���� ������ üũ
	while (WaveLoopIter != WaveEndIter)
	{
		std::vector<std::shared_ptr<BaseMonster>>::iterator MonsterLoopIter = WaveLoopIter->begin();
		std::vector<std::shared_ptr<BaseMonster>>::iterator MonsterEndIter = WaveLoopIter->end();

		while (MonsterLoopIter != MonsterEndIter)
		{
			std::shared_ptr<BaseMonster> MonsterPtr = (*MonsterLoopIter);

			if (true == MonsterPtr->IsDeath())
			{
				(*MonsterLoopIter) = nullptr;
				MonsterLoopIter = WaveLoopIter->erase(MonsterLoopIter);
			}
			else
			{
				++MonsterLoopIter;
			}
		}

		++MonsterLoopIter;
	}

	// ���� ���̺� üũ
	if (CurWave < WaveDatas.size())
	{
		std::vector<MonsterGroupMetaData>& SpawnRef = WaveDatas[CurWave];

		bool WaveEndCheck = true;

		for (size_t i = 0; i < SpawnRef.size(); i++)
		{
			if (false == SpawnRef[i].IsSpawnEnd)
			{
				WaveEndCheck = false;
			}
		}

		if (0 != MonsterActors[CurWave].size())
		{
			WaveEndCheck = false;
		}

		if (true == WaveEndCheck)
		{
			++CurWave;
		}
	}

	// ���� �������� üũ
	if (CurWave < WaveDatas.size())
	{
		std::vector<MonsterGroupMetaData>& SpawnRef = WaveDatas[CurWave];

		for (size_t i = 0; i < SpawnRef.size(); i++)
		{
			if (true == SpawnRef[CurWave].IsSpawnEnd)
			{
				continue;
			}

			if (true == SpawnRef[CurWave].IsCollision)
			{
				GameEngineTransform* ColTrans = WaveCollision->GetTransform();

				ColTrans->SetWorldPosition(SpawnRef[CurWave].ColCenter);
				ColTrans->SetWorldScale(SpawnRef[CurWave].ColScale);

				if (nullptr != WaveCollision->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
				{
					SpawnRef[CurWave].WaveSpawn(GetLevel(), GetTransform());
				}
			}
			else
			{
				SpawnRef[CurWave].WaveSpawn(GetLevel(), GetTransform());
			}
		}
	}
}
