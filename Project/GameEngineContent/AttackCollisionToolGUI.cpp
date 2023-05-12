#include "PrecompileHeader.h"
#include "AttackCollisionToolGUI.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>

AttackCollisionToolGUI::AttackCollisionToolGUI()
{
}

AttackCollisionToolGUI::~AttackCollisionToolGUI()
{
}

void AttackCollisionToolGUI::Start()
{
}

void AttackCollisionToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
	if (nullptr == SpriteRender)
	{
		ImGui::Text("GameEngineSpriteRenderer Not Found");
		return;
	}

	if (true == ImGui::Button("Sprite Load", ImVec2(60, 30)))
	{
		std::string Path = ContentFunc::GetOpenFilePath();


		if ("" != Path)
		{
			GameEnginePath File = GameEnginePath(Path);
			std::string FileName = File.GetFileName();

			std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(FileName);

			if (nullptr == FindSprite)
			{
				FindSprite = GameEngineSprite::LoadSheet(Path, LoadWitdhCount, LoadHeightCount);
			}

			std::shared_ptr<AnimationInfo> FindAnimInfo = SpriteRender->FindAnimation(FileName);

			if (nullptr == FindAnimInfo)
			{
				FindAnimInfo = SpriteRender->CreateAnimation({ FileName });
			}

			//SpriteRender->SetAnimStop(true);
		}
	}

	ImGui::Text(std::string("Show Animation Index : " + std::to_string(ShowIndex)).data());

	int InputStart = StartIndex;

	ImGui::InputInt("Animation Start", &InputStart);

	if (InputStart != StartIndex)
	{
		if (InputStart < 0)
		{
			InputStart = 0;
		}

		StartIndex = static_cast<UINT>(InputStart);
	}

	int InputEnd = EndIndex;

	ImGui::InputInt("Animation End", &InputEnd);

	if (InputEnd != EndIndex)
	{
		if (InputEnd < 0)
		{
			InputEnd = 0;
		}

		EndIndex = static_cast<UINT>(InputEnd);
	}

	if (true == ImGui::Button("Prev", ImVec2(60, 30)))
	{
		if (StartIndex == ShowIndex)
		{
			ShowIndex = EndIndex;
		}
		else
		{
			--ShowIndex;
		}
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Next", ImVec2(60, 30)))
	{
		if (EndIndex == ShowIndex)
		{
			ShowIndex = StartIndex;
		}
		else
		{
			++ShowIndex;
		}
	}
}