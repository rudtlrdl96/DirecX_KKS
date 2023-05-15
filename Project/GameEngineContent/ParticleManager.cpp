#include "PrecompileHeader.h"
#include "ParticleManager.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/imgui.h>

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::CreateMapParticleArea(const ParticleAreaMetaData& _Parameter)
{
	std::shared_ptr<ParticleArea> NewArea = GetLevel()->CreateActor<ParticleArea>();
	NewArea->SetName(std::string("Area : ") + std::to_string(NewArea->GetActorCode()));

	NewArea->GetTransform()->SetParent(GetTransform());
	NewArea->Init(_Parameter);

	ParticleAreaDatas.push_back(NewArea);

	CurrentAreaParticleNumber = static_cast<int>(ParticleAreaDatas.size() - 1);
}

void ParticleManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(ParticleAreaDatas.size()));

	for (size_t i = 0; i < ParticleAreaDatas.size(); i++)
	{
		ParticleAreaDatas[i]->SaveBin(_SaveSerializer);
	}
}

void ParticleManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < ParticleAreaDatas.size(); i++)
	{
		ParticleAreaDatas[i]->Death();
		ParticleAreaDatas[i] = nullptr;
	}

	ParticleAreaDatas.clear();

	int LoadSize = 0;
	_LoadSerializer.Read(LoadSize);

	for (int i = 0; i < LoadSize; i++)
	{
		CreateMapParticleArea(ParticleArea::LoadBin(_LoadSerializer));
	}
}

void ParticleManager::ShowGUI()
{
	ImGui::Spacing();
	ImGui::Text("Select Particle Parameter");
	
	if (0 == ParticleAreaDatas.size())
	{
		return;
	}


	if (ImGui::BeginListBox("Particle ListBox"))
	{
		for (int n = 0; n < ParticleAreaDatas.size(); n++)
		{
			const bool is_selected = (CurrentAreaParticleNumber == n);

			if (ImGui::Selectable(ParticleAreaDatas[n]->GetName().data(), is_selected))
			{
				CurrentAreaParticleNumber = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	if (0 > CurrentAreaParticleNumber && ParticleAreaDatas.size() <= CurrentAreaParticleNumber )
	{
		return;
	}

	if (true == ImGui::Button("Copy", ImVec2(70, 25)))
	{
		if (CurrentAreaParticleNumber < 0)
		{
			return;
		}

		CreateMapParticleArea(ParticleAreaDatas[CurrentAreaParticleNumber]->GetMetaData());
		return;
	}

	if (true == ImGui::Button("Remove", ImVec2(70, 25)))
	{
		if (CurrentAreaParticleNumber < 0)
		{
			return;
		}

		std::vector<std::shared_ptr<ParticleArea>>::iterator EraseIter = ParticleAreaDatas.begin();

		EraseIter += CurrentAreaParticleNumber;

		(*EraseIter)->Death();
		(*EraseIter) = nullptr;
		EraseIter = ParticleAreaDatas.erase(EraseIter);

		if (CurrentAreaParticleNumber >= ParticleAreaDatas.size())
		{
			CurrentAreaParticleNumber = static_cast<int>(ParticleAreaDatas.size() - 1);
		}

		if (ParticleAreaDatas.size() <= 0)
		{
			CurrentAreaParticleNumber = -1;
		}

		return;
	}

	ParticleAreaMetaData& SelectAreaParticle = ParticleAreaDatas[CurrentAreaParticleNumber]->GetMetaData();

	const char* AreaComboText[5] = { "Opening", "Castle", "ForestOfHarmony", "ForestOfHarmony_Blue", "GrandHall"};

	int SelectIndex = static_cast<int>(SelectAreaParticle.Type);

	ImGui::Combo("Select Particle Type", &SelectIndex, AreaComboText, IM_ARRAYSIZE(AreaComboText));

	ParticleAreaType InputType = static_cast<ParticleAreaType>(SelectIndex);

	if (InputType != SelectAreaParticle.Type)
	{
		SelectAreaParticle.Type = InputType;
	}

	float4 Center = SelectAreaParticle.Center;
	float InputCenter[4] = { Center.x, Center.y, Center.z, Center.w };
	ImGui::DragFloat4("Select Center", InputCenter);

	SelectAreaParticle.Center.x = InputCenter[0];
	SelectAreaParticle.Center.y = InputCenter[1];
	SelectAreaParticle.Center.z = InputCenter[2];
	SelectAreaParticle.Center.w = InputCenter[3];

	ParticleAreaDatas[CurrentAreaParticleNumber]->GetTransform()->SetLocalPosition(SelectAreaParticle.Center);

	float4 Size = SelectAreaParticle.Size;
	float InputSize[4] = { Size.x, Size.y, Size.z, Size.w };

	ImGui::DragFloat4("Select Size", InputSize);

	SelectAreaParticle.Size.x = InputSize[0];
	SelectAreaParticle.Size.y = InputSize[1];
	SelectAreaParticle.Size.z = InputSize[2];
	SelectAreaParticle.Size.w = InputSize[3];

	ImGui::Checkbox("Select Is Top Spawn", &SelectAreaParticle.IsTopSpawn);

	float4 MinWind = SelectAreaParticle.MinWindDir;
	float InputMinWind[4] = { MinWind.x, MinWind.y, MinWind.z, MinWind.w };

	ImGui::DragFloat4("Select Min Wind", InputMinWind);

	SelectAreaParticle.MinWindDir.x = InputMinWind[0];
	SelectAreaParticle.MinWindDir.y = InputMinWind[1];
	SelectAreaParticle.MinWindDir.z = InputMinWind[2];
	SelectAreaParticle.MinWindDir.w = InputMinWind[3];


	float4 MaxWind = SelectAreaParticle.MaxWindDir;
	float InputMaxWind[4] = { MaxWind.x, MaxWind.y, MaxWind.z, MaxWind.w };

	ImGui::DragFloat4("Select Max Wind", InputMaxWind);

	SelectAreaParticle.MaxWindDir.x = InputMaxWind[0];
	SelectAreaParticle.MaxWindDir.y = InputMaxWind[1];
	SelectAreaParticle.MaxWindDir.z = InputMaxWind[2];
	SelectAreaParticle.MaxWindDir.w = InputMaxWind[3];


	float4 MinRandRot = SelectAreaParticle.MinRandRot;
	float InputMinRandrot[4] = { MinRandRot.x, MinRandRot.y, MinRandRot.z, MinRandRot.w };

	ImGui::DragFloat4("Select Min RandRot", InputMinRandrot);

	SelectAreaParticle.MinRandRot.x = InputMinRandrot[0];
	SelectAreaParticle.MinRandRot.y = InputMinRandrot[1];
	SelectAreaParticle.MinRandRot.z = InputMinRandrot[2];
	SelectAreaParticle.MinRandRot.w = InputMinRandrot[3];


	float4 MaxRandRot = SelectAreaParticle.MaxRandRot;
	float InputMaxRandrot[4] = { MaxRandRot.x, MaxRandRot.y, MaxRandRot.z, MaxRandRot.w };

	ImGui::DragFloat4("Select Max RandRot", InputMaxRandrot);

	SelectAreaParticle.MaxRandRot.x = InputMaxRandrot[0];
	SelectAreaParticle.MaxRandRot.y = InputMaxRandrot[1];
	SelectAreaParticle.MaxRandRot.z = InputMaxRandrot[2];
	SelectAreaParticle.MaxRandRot.w = InputMaxRandrot[3];

	ImGui::DragFloat("Select Create MinTime", &SelectAreaParticle.CreateMinTime);
	ImGui::DragFloat("Select Create MaxTime", &SelectAreaParticle.CreateMaxTime);

}
