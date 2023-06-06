#include "PrecompileHeader.h"
#include "NPCManager.h"
#include <GameEngineCore/imgui.h>

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

void NPCManager::ShowGUI()
{
	if (ImGui::BeginListBox("NPC ListBox"))
	{
		for (int n = 0; n < NpcActors.size(); n++)
		{
			const bool is_selected = (GUI_SelectNPC == n);

			if (ImGui::Selectable(
				GameEngineString::AnsiToUTF8((std::string("Npc ") + std::to_string(n) + "," + NpcActors[GUI_SelectNPC]->Data.Name)).data(), is_selected))
			{
				GUI_SelectNPC = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	if (0 > GUI_SelectNPC || NpcActors.size() <= GUI_SelectNPC)
	{
		return;
	}

	if (0 == NpcActors.size())
	{
		return;
	}

	if (true == ImGui::Button("Remove"))
	{
		NpcActors[GUI_SelectNPC]->Death();
		NpcActors[GUI_SelectNPC] = nullptr;

		NpcActors.erase(NpcActors.begin() + GUI_SelectNPC);
		--GUI_SelectNPC;

		if (0 > GUI_SelectNPC)
		{
			GUI_SelectNPC = 0;
		}

		return;
	}

	GameEngineDebug::DrawBox(GetLevel()->GetMainCamera().get(), NpcActors[GUI_SelectNPC]->MainRender->GetTransform());
	NpcActors[GUI_SelectNPC]->ShowGUI();
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
