#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

std::string ContentLevel::CurLevelName = "";
std::string ContentLevel::PrevLevelName = "";

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

float4 ContentLevel::GetMousePos() const
{
	float4 Result = GameEngineWindow::GetMousePosition();
	float4 CameraPos = MainCam->GetTransform()->GetWorldPosition();

	Result *= MainCam->GetViewPort().InverseReturn();
	Result *= MainCam->GetProjection().InverseReturn();
	Result *= MainCam->GetView().InverseReturn();

	return Result;
}

void ContentLevel::Start()
{
	GameEngineLevel::Start();

	MainCam = GetMainCamera();
	MainCamCtrl.Start(MainCam);
	MainCam->GetTransform()->SetLocalPosition({0, 0, -5000});
	MainCam->GetTransform()->SetLocalRotation(float4::Zero);
}

void ContentLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	MainCamCtrl.Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("NumPad0"))
	{
		if (PrevLevelName == "")
		{
			return;
		}

		ContentFunc::Swap<std::string>(&CurLevelName, &PrevLevelName);
		GameEngineCore::ChangeLevel(CurLevelName);
		return;
	}
		
	if (true == GameEngineInput::IsPress("CheckDebugCtrl"))
	{
		if (true == GameEngineInput::IsDown("NumPad1"))
		{
			Debug_LevelMove("BattleDebug");
		}
		else if (true == GameEngineInput::IsDown("NumPad2"))
		{
			Debug_LevelMove("ShaderDebug");
		}
		else if (true == GameEngineInput::IsDown("NumPad3"))
		{
			Debug_LevelMove("InventoryDebug");
		}
		else if (true == GameEngineInput::IsDown("NumPad4"))
		{
			Debug_LevelMove("MapTool");
		}
	}
	else if (true == GameEngineInput::IsPress("CheckUIAlt"))
	{
		if (true == GameEngineInput::IsDown("NumPad1"))
		{
			Debug_LevelMove("Title");
		}
		if (true == GameEngineInput::IsDown("NumPad2"))
		{
			Debug_LevelMove("Story");
		}
		else if (true == GameEngineInput::IsDown("NumPad3"))
		{
			Debug_LevelMove("EndingLogo");
		}
	}
	else
	{		
		if (true == GameEngineInput::IsDown("NumPad1"))
		{
			Debug_LevelMove("Castle");
		}
		else if (true == GameEngineInput::IsDown("NumPad2"))
		{
			Debug_LevelMove("Opening");
		}
		else if (true == GameEngineInput::IsDown("NumPad3"))
		{
			Debug_LevelMove("ForestOfHarmony");
		}
		else if (true == GameEngineInput::IsDown("NumPad4"))
		{
			Debug_LevelMove("ForestOfHarmony_Boss");
		}
		else if (true == GameEngineInput::IsDown("NumPad5"))
		{
			Debug_LevelMove("GrandHall");
		}
		else if (true == GameEngineInput::IsDown("NumPad6"))
		{
			Debug_LevelMove("GrandHall_Boss");
		}
		else if (true == GameEngineInput::IsDown("NumPad7"))
		{
			Debug_LevelMove("HolyCourtyard");
		}
		else if (true == GameEngineInput::IsDown("NumPad8"))
		{
			Debug_LevelMove("HolyCourtyard_Boss");
		}
		else if (true == GameEngineInput::IsDown("NumPad9"))
		{
			Debug_LevelMove("Shop");
		}
	}
}

void ContentLevel::Debug_LevelMove(const std::string_view& _Level)
{
	PrevLevelName = CurLevelName;
	CurLevelName = _Level;
	GameEngineCore::ChangeLevel(CurLevelName);
}
