#include "PrecompileHeader.h"
#include "GameEventManager.h"

#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "BaseDoor.h"


GameEventManager::GameEventManager()
{
}

GameEventManager::~GameEventManager()
{
}

void GameEventManager::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(&SpawnPoint, sizeof(float4));
	//_SaveSerializer.Write(&DoorPoint, sizeof(float4));
	//_SaveSerializer.Write(&DoorArea, sizeof(LevelArea));
	//_SaveSerializer.Write(&DType, sizeof(ClearDoorType));

	//float4 DoorPoint = float4::Zero;
	//LevelArea DoorArea = LevelArea::None;
	//ClearDoorType DType = ClearDoorType::SingleDoor;
}

void GameEventManager::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	_LoadSerializer.Read(&SpawnPoint, sizeof(float4));
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
					
			ClearBackRender->GetTransform()->SetLocalPosition(DoorPoint);

			if (nullptr != FirstDoorActor)
			{
				float4 FirstDoorPos = DoorPoint + float4(-100, 0, 0);
				FirstDoorActor->GetTransform()->SetLocalPosition(FirstDoorPos);
			}

			if (nullptr != SecondDoorActor)
			{
				float4 SecondDoorPos = DoorPoint + float4(100, 0, 0);
				SecondDoorActor->GetTransform()->SetLocalPosition(SecondDoorPos);
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
		ClearBackRender->GetTransform()->SetLocalPosition(DoorPoint);

		FirstDoorActor = GetLevel()->CreateActor<BaseDoor>();
		FirstDoorActor->GetTransform()->SetParent(GetTransform());
		FirstDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(-100, 0, 0));

		SecondDoorActor = GetLevel()->CreateActor<BaseDoor>();
		SecondDoorActor->GetTransform()->SetParent(GetTransform());
		SecondDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(100, 0, 0));
	
		ClearBackRender->On();
	}
	else
	{
		FirstDoorActor = GetLevel()->CreateActor<BaseDoor>();
		FirstDoorActor->GetTransform()->SetParent(GetTransform());
		FirstDoorActor->GetTransform()->SetLocalPosition(DoorPoint + float4(0, 0, 0));

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
