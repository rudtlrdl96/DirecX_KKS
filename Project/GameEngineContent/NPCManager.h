#pragma once
#include "BaseContentActor.h"
#include "BaseNPC.h"

class NPCManager : public BaseContentActor
{
public:
	NPCManager();
	~NPCManager();

	NPCManager(const NPCManager& _Other) = delete;
	NPCManager(NPCManager&& _Other) noexcept = delete;
	NPCManager& operator=(const NPCManager& _Other) = delete;
	NPCManager& operator=(NPCManager&& _Other) noexcept = delete;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);
	void ShowGUI() override;

	std::shared_ptr<BaseNPC> CreateNPC(const NPCMetaData& _NewNPCData);
	void ResetNPC();

protected:
	void Start() override;

private:
	std::vector<std::shared_ptr<BaseNPC>> NpcActors;

	//GUI
	int GUI_SelectNPC = 0;

};

