#include "PrecompileHeader.h"
#include "EventActor.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/imgui.h>

#include "GameEventManager.h"

EventActor::EventActor()
{
}

EventActor::~EventActor()
{
}

void EventActor::Start()
{
	EventCol = CreateComponent<GameEngineCollision>();
}

void EventActor::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> PlayerCol = EventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (true == IsEventEnter)
	{
		if (true == ActiveEnterEvent)
		{
			GameEventManager::CallEvent(UpdateEventName);
		}

		if (nullptr == PlayerCol)
		{
			IsEventEnter = false;
			GameEventManager::CallEvent(ExitEventName);
		}
	}

	if (false == IsEventEnter)
	{
		if (nullptr != PlayerCol)
		{
			IsEventEnter = true;
			GameEventManager::CallEvent(EnterEventName);
		}
	}
}

void EventActor::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&ColCenter, sizeof(float4));
	_SaveSerializer.Write(&ColScale, sizeof(float4));

	_SaveSerializer.Write(&ActiveEnterEvent, sizeof(bool));
	_SaveSerializer.Write(EnterEventName); // String

	_SaveSerializer.Write(&ActiveUpdateEvent, sizeof(bool));
	_SaveSerializer.Write(UpdateEventName); // String

	_SaveSerializer.Write(&ActiveExitEvent, sizeof(bool));
	_SaveSerializer.Write(ExitEventName); // String
}

void EventActor::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&ColCenter, sizeof(float4));
	_LoadSerializer.Read(&ColScale, sizeof(float4));

	_LoadSerializer.Read(&ActiveEnterEvent, sizeof(bool));
	_LoadSerializer.Read(EnterEventName); // String

	_LoadSerializer.Read(&ActiveUpdateEvent, sizeof(bool));
	_LoadSerializer.Read(UpdateEventName); // String

	_LoadSerializer.Read(&ActiveExitEvent, sizeof(bool));
	_LoadSerializer.Read(ExitEventName); // String

	GetTransform()->SetLocalPosition(ColCenter);
	EventCol->GetTransform()->SetLocalScale(ColScale);
}

void EventActor::ShowGUI()
{
	ImGui::Text("Event");
	ImGui::Spacing();

	{
		float InputFloat4[4] = { ColCenter.x, ColCenter.y, ColCenter.z, ColCenter.w };

		ImGui::DragFloat4("EventPoint", InputFloat4);

		ColCenter.x = InputFloat4[0];
		ColCenter.y = InputFloat4[1];
		ColCenter.z = InputFloat4[2];
		ColCenter.w = InputFloat4[3];

		GetTransform()->SetLocalPosition(ColCenter);
	}

	{
		float InputFloat4[4] = { ColScale.x, ColScale.y, ColScale.z, ColScale.w };

		ImGui::DragFloat4("EventPoint", InputFloat4);

		ColScale.x = InputFloat4[0];
		ColScale.y = InputFloat4[1];
		ColScale.z = InputFloat4[2];
		ColScale.w = InputFloat4[3];
	
		EventCol->GetTransform()->SetLocalScale(ColScale);
	}

	{
		ImGui::Checkbox("ET", &ActiveEnterEvent);

		if (true == ActiveEnterEvent)
		{
			ImGui::SameLine();
			char EnterText[255] = "";
			strcpy_s(EnterText, 255, EnterEventName.c_str());
			ImGui::InputText("Enter Event", EnterText, IM_ARRAYSIZE(EnterText));
			EnterEventName = EnterText;		
		}
	}

	{
		ImGui::Checkbox("UP", &ActiveUpdateEvent);

		if (true == ActiveUpdateEvent)
		{
			ImGui::SameLine();
			char UpdateText[255] = "";
			strcpy_s(UpdateText, 255, UpdateEventName.c_str());
			ImGui::InputText("Update Event", UpdateText, IM_ARRAYSIZE(UpdateText));
			UpdateEventName = UpdateText;
		}
	}

	{
		ImGui::Checkbox("EX", &ActiveExitEvent);

		if (true == ActiveExitEvent)
		{
			ImGui::SameLine();
			char ExitText[255] = "";
			strcpy_s(ExitText, 255, ExitEventName.c_str());
			ImGui::InputText("Update Event", ExitText, IM_ARRAYSIZE(ExitText));
			ExitEventName = ExitText;
		}
	}
}