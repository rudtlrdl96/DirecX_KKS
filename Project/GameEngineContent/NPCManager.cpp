#include "PrecompileHeader.h"
#include "NPCManager.h"

NPCManager::NPCManager()
{
}

NPCManager::~NPCManager()
{
}

void NPCManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	int SaveSize = static_cast<int>(NpcActors.size());
	_SaveSerializer.Write(&SaveSize, sizeof(int));

	for (int i = 0; i < SaveSize; i++)
	{
		NpcActors[i]->SaveBin(_SaveSerializer);
	}
}

void NPCManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < NpcActors.size(); i++)
	{
		NpcActors[i]->Death();
		NpcActors[i] = nullptr;
	}
	NpcActors.clear();

	int SaveSize = 0;
	_LoadSerializer.Read(&SaveSize, sizeof(int));

	for (int i = 0; i < SaveSize; i++)
	{
		NPCMetaData LoadData = BaseNPC::LoadBin(_LoadSerializer);
		CreateNPC(LoadData);
	}
}

void NPCManager::ResetNPC()
{
	for (size_t i = 0; i < NpcActors.size(); i++)
	{
		NpcActors[i]->ResetNPC();
	}
}

void NPCManager::Start()
{
	NpcActors.reserve(4);
}
