#include "PrecompileHeader.h"
#include "GameEventManager.h"
#include <GameEngineCore/imgui.h>

GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
}

void GameEventManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&SpawnPoint, sizeof(float4));
}

void GameEventManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&SpawnPoint, sizeof(float4));
}

void GameEventManager::ShowGUI()
{
	float InputFloat4[4] = { SpawnPoint.x, SpawnPoint.y, SpawnPoint.z, SpawnPoint.w};

	ImGui::DragFloat4("SpawnPoint", InputFloat4);

	if (InputFloat4[0] != SpawnPoint.x ||
		InputFloat4[1] != SpawnPoint.y ||
		InputFloat4[2] != SpawnPoint.z ||
		InputFloat4[3] != SpawnPoint.w)
	{
		SpawnPoint.x = InputFloat4[0];
		SpawnPoint.y = InputFloat4[1];
		SpawnPoint.z = InputFloat4[2];
		SpawnPoint.w = InputFloat4[3];
	}

}
