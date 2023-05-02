#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

std::string ContentLevel::CurLevelName = "";
std::string ContentLevel::PrevLevelName = "";

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

void ContentLevel::Start()
{
	GameEngineLevel::Start();

	std::shared_ptr<GameEngineCamera> Cam = GetMainCamera();
	MainCamCtrl.Start(Cam);
	Cam->GetTransform()->SetLocalPosition({0, 0, -5000});
	Cam->GetTransform()->SetLocalRotation(float4::Zero);
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
	}
	else
	{
		if (true == GameEngineInput::IsDown("NumPad1"))
		{
			Debug_LevelMove("Title");
		}
		else if (true == GameEngineInput::IsDown("NumPad2"))
		{
			Debug_LevelMove("Castle");
		}
		else if (true == GameEngineInput::IsDown("NumPad3"))
		{
			Debug_LevelMove("ForestOfHarmony");
		}
		else if (true == GameEngineInput::IsDown("NumPad4"))
		{
			Debug_LevelMove("GrandHall");
		}
		else if (true == GameEngineInput::IsDown("NumPad5"))
		{
			Debug_LevelMove("HolyCourtyard");
		}
		else if (true == GameEngineInput::IsDown("NumPad6"))
		{
			Debug_LevelMove("Shop");
		}
		else if (true == GameEngineInput::IsDown("NumPad7"))
		{
			Debug_LevelMove("Story");
		}
		else if (true == GameEngineInput::IsDown("NumPad8"))
		{
			Debug_LevelMove("EndingLogo");
		}
	}
}

void ContentLevel::Debug_LevelMove(const std::string_view& _Level)
{
	PrevLevelName = CurLevelName;
	CurLevelName = _Level;
	GameEngineCore::ChangeLevel(CurLevelName);
}
