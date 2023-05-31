#include "PrecompileHeader.h"
#include "GameEventManager.h"

#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseDoor.h"
#include "BattleLevel.h"

// Static Start

std::map<std::string, std::map<UINT, std::function<void(void)>>> GameEventManager::EventCallback;

void GameEventManager::AddEvent(const std::string_view& _Event, UINT _ActorCode, std::function<void()> _Callback)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);
	EventCallback[UpperName][_ActorCode] = _Callback;
}

void GameEventManager::RemoveEvent(const std::string_view& _Event, UINT _ActorCode, std::function<void()> _Callback)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);
	
	std::map<UINT, std::function<void(void)>>& EventRef = EventCallback[UpperName];
	
	std::map<UINT, std::function<void(void)>>::iterator FindIter = EventRef.find(_ActorCode);

	if (FindIter != EventRef.end())
	{
		EventRef.erase(FindIter);
	}
}

void GameEventManager::CallEvent(const std::string_view& _Event)
{
	std::string UpperName = GameEngineString::ToUpper(_Event);
	std::map<UINT, std::function<void(void)>>& EventRef = EventCallback[UpperName];

	std::map<UINT, std::function<void(void)>>::iterator LoopIter = EventRef.begin();
	std::map<UINT, std::function<void(void)>>::iterator EndIter = EventRef.end();

	while (LoopIter != EndIter)
	{
		if (nullptr == LoopIter->second)
		{
			MsgAssert_Rtti<GameEventManager>(" - nullptr callback 함수를 호출하려 했습니다");
			continue;
		}

		LoopIter->second();
		++LoopIter;
	}
}

// Static End //


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
}

void GameEventManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&SpawnPoint, sizeof(float4));
	_LoadSerializer.Read(&DoorPoint, sizeof(float4));
	_LoadSerializer.Read(&DoorArea, sizeof(LevelArea));
	_LoadSerializer.Read(&DType, sizeof(ClearDoorType));

	SetClearDoorType(DType);
}

void GameEventManager::ShowGUI()
{
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
