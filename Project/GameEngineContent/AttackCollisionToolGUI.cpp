#include "PrecompileHeader.h"
#include "AttackCollisionToolGUI.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "DebugCollisionRender.h"

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

	if (true == ImGui::Button("Sprite Load", ImVec2(120, 35)))
	{
		std::string Path = ContentFunc::GetOpenFilePath();

		if ("" != Path)
		{
			GameEnginePath File = GameEnginePath(Path);
			SpriteAnimationName = File.GetFileName();

			std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(SpriteAnimationName);

			if (nullptr == FindSprite)
			{
				FindSprite = GameEngineSprite::LoadSheet(Path, LoadWitdhCount, LoadHeightCount);
			}

			std::shared_ptr<AnimationInfo> FindAnimInfo = SpriteRender->FindAnimation(SpriteAnimationName);

			if (nullptr == FindAnimInfo)
			{
				FindAnimInfo = SpriteRender->CreateAnimation({.AnimationName = SpriteAnimationName, .SpriteName = SpriteAnimationName, .ScaleToTexture = true});
			
				EndIndex = static_cast<UINT>(FindAnimInfo->EndFrame);
			}

			ShowIndex = 0;
			SpriteRender->ChangeAnimation(SpriteAnimationName, ShowIndex, true);

			SpriteRender->AnimPause();
		}
	}

	ImGui::InputFloat("RenderScaleRatio", &RenderScale);
	SpriteRender->SetScaleRatio(RenderScale);

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

		SpriteRender->ChangeAnimation(SpriteAnimationName, ShowIndex, true);
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

		SpriteRender->ChangeAnimation(SpriteAnimationName, ShowIndex, true);
	}

	ImGui::Spacing();

	if (nullptr == ColRender)
	{
		ImGui::Text("DebugCollisionRender Not Found");
		return;
	}

	ImGui::Combo("ColType", &ColComboIndex, ColTypeComboText, IM_ARRAYSIZE(ColTypeComboText));

	switch (ColComboIndex)
	{
	case 0: // Box
		ColRender->SetColType(DeubgColType::Box);
		break;
	case 1: // Sphere
		ColRender->SetColType(DeubgColType::Sphere);
		break;
	default:
		break;
	}


	float InputColCenter[4] = { ColCenterPos.x, ColCenterPos.y, ColCenterPos.z, ColCenterPos.w};

	ImGui::DragFloat4("ColCenter", InputColCenter);
	ColCenterPos = ContentFunc::ConvertFloat4(InputColCenter);

	ColRender->GetTransform()->SetLocalPosition(ColCenterPos);

	float InputColSize[4] = { ColSize.x, ColSize.y , ColSize.z ,ColSize.w };

	ImGui::DragFloat4("ColSize", InputColSize);
	ColSize = ContentFunc::ConvertFloat4(InputColSize);

	ColRender->SetSize(ColSize);

}

void AttackCollisionToolGUI::SetRenderer(std::shared_ptr<class GameEngineSpriteRenderer> _Render)
{
	SpriteRender = _Render;

	if (nullptr != SpriteRender)
	{
		SpriteRender->AnimPause();
	}
}

void AttackCollisionToolGUI::SetCol(std::shared_ptr<class DebugCollisionRender> _Render)
{
	ColRender = _Render;
}
