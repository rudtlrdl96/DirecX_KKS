#include "PrecompileHeader.h"
#include "GameEventManager.h"

#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseDoor.h"
#include "BattleLevel.h"
#include "EventActor.h"
#include "ScaleDebugRender.h"

GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
}

void GameEventManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&SpawnPoint, sizeof(float4));
	_SaveSerializer.Write(&DoorPoint, sizeof(float4));
	_SaveSerializer.Write(&DoorArea, sizeof(LevelArea));
	_SaveSerializer.Write(&DType, sizeof(ClearDoorType));

	int SaveEvnetCount = static_cast<int>(EventActors.size());
	_SaveSerializer.Write(&SaveEvnetCount, sizeof(int));

	for (size_t i = 0; i < EventActors.size(); i++)
	{
		EventActors[i]->SaveBin(_SaveSerializer);
	}
}

void GameEventManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	for (size_t i = 0; i < EventActors.size(); i++)
	{
		EventActors[i]->Death();
		EventActors[i] = nullptr;
	}

	EventActors.clear();

	_LoadSerializer.Read(&SpawnPoint, sizeof(float4));
	_LoadSerializer.Read(&DoorPoint, sizeof(float4));
	_LoadSerializer.Read(&DoorArea, sizeof(LevelArea));
	_LoadSerializer.Read(&DType, sizeof(ClearDoorType));

	int LoadEvnetCount = 0;
	_LoadSerializer.Read(&LoadEvnetCount, sizeof(int));
	
	EventActors.reserve(LoadEvnetCount);
	
	for (int i = 0; i < LoadEvnetCount; i++)
	{
		std::shared_ptr<EventActor> NewEvent = GetLevel()->CreateActor<EventActor>();
		NewEvent->GetTransform()->SetParent(GetTransform());
		NewEvent->LoadBin(_LoadSerializer);
		EventActors.push_back(NewEvent);
	}

	SetClearDoorType(DType);
}

void GameEventManager::ShowGUI()
{
	if (nullptr == GUI_EventColRender)
	{
		GUI_EventColRender = GetLevel()->CreateActor<ScaleDebugRender>();
		GUI_EventColRender->GetTransform()->SetParent(GetTransform());
		GUI_EventColRender->SetTexture("EventCol.png");
	}

	GUI_EventColRender->Off();

	ImGui::Text("Spawn");
	ImGui::Spacing();

	{
		float InputFloat4[4] = { SpawnPoint.x, SpawnPoint.y, SpawnPoint.z, SpawnPoint.w };

		ImGui::DragFloat4("SpawnPoint", InputFloat4);

		SpawnPoint.x = InputFloat4[0];
		SpawnPoint.y = InputFloat4[1];
		SpawnPoint.z = InputFloat4[2];
		SpawnPoint.w = InputFloat4[3];
	}

	ImGui::Spacing();
	
	ImGui::Text("Door");
	ImGui::Spacing();

	{
		float InputFloat4[4] = { DoorPoint.x, DoorPoint.y, DoorPoint.z, DoorPoint.w };

		ImGui::DragFloat4("DoorPoint", InputFloat4);

		if (DoorPoint.x != InputFloat4[0] ||
			DoorPoint.y != InputFloat4[1] ||
			DoorPoint.z != InputFloat4[2] ||
			DoorPoint.w != InputFloat4[3])
		{
			DoorPoint.x = InputFloat4[0];
			DoorPoint.y = InputFloat4[1];
			DoorPoint.z = InputFloat4[2];
			DoorPoint.w = InputFloat4[3];
					
			ClearBackRender->GetTransform()->SetLocalPosition(DoorPoint + float4(0, -30, 0));

			if (DType == ClearDoorType::DoubleDoor)
			{
				if (nullptr != FirstDoorActor)
				{
					float4 FirstDoorPos = DoorPoint + float4(-300, 0, -0.1f);
					FirstDoorActor->GetTransform()->SetLocalPosition(FirstDoorPos);
				}

				if (nullptr != SecondDoorActor)
				{
					float4 SecondDoorPos = DoorPoint + float4(300, 0, -0.1f);
					SecondDoorActor->GetTransform()->SetLocalPosition(SecondDoorPos);
				}
			}
			else
			{
				if (nullptr != FirstDoorActor)
				{
					float4 FirstDoorPos = DoorPoint + float4(0, 0, -0.1f);
					FirstDoorActor->GetTransform()->SetLocalPosition(FirstDoorPos);
				}
			}
	
		}
	}

	{
		static int CurrentAreaType = 0;
		ImGui::Combo("AreaType", &CurrentAreaType, AreaComboText, IM_ARRAYSIZE(AreaComboText));

		LevelArea InputType = (LevelArea)CurrentAreaType;

		if (InputType < LevelArea::None || InputType > LevelArea::Shop)
		{
			MsgAssert_Rtti<GameEventManager>(" - 잘못된 Area 타입이 입력되었습니다");
		}

		if (InputType != DoorArea)
		{
			DoorArea = InputType;
			SetClearDoorType(DType);
			SetDoorType(DoorType::Normal, DoorType::Normal);
		}
	}

	{
		static int CurrentDoorType = 0;
		ImGui::Combo("DoorType", &CurrentDoorType, DoorComboText, IM_ARRAYSIZE(DoorComboText));

		ClearDoorType InputType = (ClearDoorType)CurrentDoorType;

		if (InputType < ClearDoorType::SingleDoor || InputType > ClearDoorType::DoubleDoor)
		{
			MsgAssert_Rtti<GameEventManager>(" - 잘못된 Door 타입이 입력되었습니다");
		}

		if (InputType != DType)
		{
			SetClearDoorType(InputType);
		}
	}

	// Event

	ImGui::Spacing();
	ImGui::Text("Event List");
	ImGui::Spacing();

	if (ImGui::BeginListBox("Event ListBox"))
	{
		for (int n = 0; n < EventActors.size(); n++)
		{
			const bool is_selected = (GUI_SelectEvent == n);

			if (ImGui::Selectable((std::string("Event : ") + std::to_string(n)).data(), is_selected))
			{
				GUI_SelectEvent = n;
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();
	}

	if (true == ImGui::Button("Add Event", ImVec2(100, 24)))
	{
		std::shared_ptr<EventActor> NewEvent = GetLevel()->CreateActor<EventActor>();
		NewEvent->GetTransform()->SetParent(GetTransform());
		EventActors.push_back(NewEvent);

		GUI_SelectEvent = static_cast<int>(EventActors.size() - 1);
	}

	if (true == ImGui::Button("Remove Event", ImVec2(100, 24)))
	{
		if (0 <= GUI_SelectEvent && EventActors.size() > GUI_SelectEvent)
		{
			EventActors.erase(EventActors.begin() + GUI_SelectEvent);

			if (GUI_SelectEvent >= EventActors.size())
			{
				GUI_SelectEvent = static_cast<int>(EventActors.size() - 1);
			}
		}
	}

	if (0 > GUI_SelectEvent || EventActors.size() <= GUI_SelectEvent)
	{
		return;
	}

	EventActors[GUI_SelectEvent]->ShowGUI();

	GUI_EventColRender->On();
	GUI_EventColRender->GetTransform()->SetLocalPosition(EventActors[GUI_SelectEvent]->ColCenter);
	GUI_EventColRender->GetTransform()->SetLocalScale(EventActors[GUI_SelectEvent]->ColScale);
}

void GameEventManager::DoorActive()
{
	if (nullptr != FirstDoorActor)
	{
		FirstDoorActor->ActiveOn();
	}

	if (nullptr != SecondDoorActor)
	{
		SecondDoorActor->ActiveOn();
	}

}

void GameEventManager::DoorDisable()
{
	if (nullptr != FirstDoorActor)
	{
		FirstDoorActor->ActiveOff();
	}

	if (nullptr != SecondDoorActor)
	{
		SecondDoorActor->ActiveOff();
	}
}

void GameEventManager::SetDoorLevel(std::shared_ptr<class BattleLevel> _Level)
{
	if (nullptr != FirstDoorActor)
	{
		FirstDoorActor->SetBattleLevel(_Level.get());
	}

	if (nullptr != SecondDoorActor)
	{
		SecondDoorActor->SetBattleLevel(_Level.get());
	}

}

void GameEventManager::Start()
{
	EventActors.reserve(8);

	if (nullptr == GameEngineTexture::Find("ForestOfHarmony_ClearBackground.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Door");
		Path.Move("ForestOfHarmony");

		GameEngineTexture::Load(Path.GetPlusFileName("ForestOfHarmony_ClearBackground.png").GetFullPath());
	}

	ClearBackRender = CreateComponent<ContentSpriteRenderer>();
	ClearBackRender->PipeSetting("2DTexture_ColorLight");
	ClearBackRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", ClearBackBuffer);
	ClearBackRender->SetScaleToTexture("ForestOfHarmony_ClearBackground.png");
	
	float4 Scale = ClearBackRender->GetTransform()->GetLocalScale();
	ClearBackRender->GetTransform()->SetLocalScale(Scale * 2.0f);

	ClearBackRender->Off();

	SetClearDoorType(ClearDoorType::SingleDoor);
}

void GameEventManager::SetClearDoorType(ClearDoorType _Type)
{
	if (nullptr != FirstDoorActor)
	{
		FirstDoorActor->Death();
		FirstDoorActor = nullptr;
	}

	if (nullptr != SecondDoorActor)
	{
		SecondDoorActor->Death();
		SecondDoorActor = nullptr;
	}

	DType = _Type;

	if (ClearDoorType::DoubleDoor == DType)
	{
		ClearBackRender->GetTransform()->SetLocalPosition(DoorPoint + float4(0, -30, 0));

		FirstDoorActor = GetLevel()->CreateActor<BaseDoor>();
		FirstDoorActor->GetTransform()->SetParent(GetTransform());
		FirstDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(-300, 0, -0.1f));

		SecondDoorActor = GetLevel()->CreateActor<BaseDoor>();
		SecondDoorActor->GetTransform()->SetParent(GetTransform());
		SecondDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(300, 0, -0.1f));
	
		ClearBackRender->On();
	}
	else
	{
		FirstDoorActor = GetLevel()->CreateActor<BaseDoor>();
		FirstDoorActor->GetTransform()->SetParent(GetTransform());
		FirstDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(0, 0, -0.1f));

		ClearBackRender->Off();
	}

	SetDoorType(DoorType::Normal, DoorType::Normal);
}

void GameEventManager::SetDoorType(DoorType _FirstType, DoorType _SecondType)
{
	if (nullptr != FirstDoorActor)
	{
		FirstDoorActor->SetDoorType(DoorArea, _FirstType);
	}

	if (nullptr != SecondDoorActor)
	{
		SecondDoorActor->SetDoorType(DoorArea, _SecondType);
	}
}
