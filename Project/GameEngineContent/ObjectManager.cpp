#include "PrecompileHeader.h"
#include "ObjectManager.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/imgui.h>

ObjectManager::ObjectManager()
{
	StaticObjectActors.reserve(32);
}

ObjectManager::~ObjectManager()
{
}

std::shared_ptr<StaticObject> ObjectManager::CreateStaticObject(const SObject_DESC& _Desc)
{
	if ("" == _Desc.Name)
	{
		return nullptr;
	}

	std::shared_ptr<StaticObject> CreatePtr = GetLevel()->CreateActor<StaticObject>();
	CreatePtr->SetName(_Desc.Name + " - " + std::to_string(CreatePtr->GetActorCode()));
	CreatePtr->GetTransform()->SetParent(this->GetTransform());
	CreatePtr->Init(_Desc);
	StaticObjectActors.push_back(CreatePtr);
	CurrentStaticObjectIndex = static_cast<int>(StaticObjectActors.size() - 1);

	return CreatePtr;
}

void ObjectManager::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(static_cast<int>(StaticObjectActors.size()));

	for (const std::shared_ptr<StaticObject>& LoopRef : StaticObjectActors)
	{ 
		LoopRef->SaveBin(_SaveSerializer);
	}	

	_SaveSerializer.Write(static_cast<int>(BrokenObjectActors.size()));

	for (const std::shared_ptr<BrokenObject>& LoopRef : BrokenObjectActors)
	{
		//LoopRef->SaveBin(_SaveSerializer);
	}
}

void ObjectManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < StaticObjectActors.size(); i++)
	{
		if (nullptr == StaticObjectActors[i])
		{
			continue;
		}

		StaticObjectActors[i]->Death();
		StaticObjectActors[i] = nullptr;
	}

	StaticObjectActors.clear();

	int StaticObjectCount = 0;
	_LoadSerializer.Read(StaticObjectCount);

	StaticObjectActors.reserve(StaticObjectCount);

	for (int i = 0; i < StaticObjectCount; i++)
	{
		SObject_DESC LoadDesc = StaticObject::LoadBin(_LoadSerializer);
		CreateStaticObject(LoadDesc);
	}

	int BrokenObjectCount = 0;
	_LoadSerializer.Read(BrokenObjectCount);

	for (int i = 0; i < BrokenObjectCount; i++)
	{
	}
}


void ObjectManager::ShowGUI()
{
	if (ImGui::BeginListBox("SObjectBox 1"))
	{
		for (int n = 0; n < StaticObjectActors.size(); n++)
		{
			const bool is_selected = (CurrentStaticObjectIndex == n);

			if (ImGui::Selectable(StaticObjectActors[n]->GetName().data(), is_selected))
			{
				CurrentStaticObjectIndex = n;
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	if (true == ImGui::Button("Copy", ImVec2(70, 25)))
	{
		if (CurrentStaticObjectIndex < 0)
		{
			return;
		}

		CreateStaticObject(StaticObjectActors[CurrentStaticObjectIndex]->GetDesc());
	}

	if (true == ImGui::Button("Remove", ImVec2(70, 25)))
	{
		if (CurrentStaticObjectIndex < 0)
		{
			return;
		}

		std::vector<std::shared_ptr<StaticObject>>::iterator EraseIter = StaticObjectActors.begin();

		EraseIter += CurrentStaticObjectIndex;

		(*EraseIter)->Death();
		(*EraseIter) = nullptr;
		EraseIter = StaticObjectActors.erase(EraseIter);

		if (CurrentStaticObjectIndex >= StaticObjectActors.size())
		{
			CurrentStaticObjectIndex = static_cast<int>(StaticObjectActors.size() - 1);
		}

		if (StaticObjectActors.size() <= 0)
		{
			CurrentStaticObjectIndex = -1;
		}
	}
}
