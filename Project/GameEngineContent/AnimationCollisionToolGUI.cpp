#include "PrecompileHeader.h"
#include "AnimationCollisionToolGUI.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include "AttackColRender.h"

AnimationCollisionToolGUI::AnimationCollisionToolGUI()
{
}

AnimationCollisionToolGUI::~AnimationCollisionToolGUI()
{
}

void AnimationCollisionToolGUI::Start()
{
}

void AnimationCollisionToolGUI::OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime)
{
	if (nullptr == SpriteRender)
	{
		ImGui::Text("GameEngineSpriteRenderer Not Found");
		return;
	}

	if (true == ImGui::Button("Sprite Load"))
	{
		std::string Path = ContentFunc::GetOpenFilePath();

		if ("" != Path)
		{
			GameEnginePath File = GameEnginePath(Path);
			SpriteAnimationName = File.GetFileName();

			std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(SpriteAnimationName);

			if (nullptr == FindSprite)
			{
				MsgAssert_Rtti<AnimationCollisionToolGUI>(" - 로드되지 않은 시트를 사용하려 했습니다");
				return;
			}

			std::shared_ptr<AnimationInfo> FindAnimInfo = SpriteRender->FindAnimation(SpriteAnimationName);

			if (nullptr == FindAnimInfo)
			{
				FindAnimInfo = SpriteRender->CreateAnimation({.AnimationName = SpriteAnimationName, .SpriteName = SpriteAnimationName, .ScaleToTexture = true});			
				EndFrame = static_cast<UINT>(FindAnimInfo->EndFrame);
			}

			ShowFrame = 0;

			SpriteRender->ChangeAnimation(SpriteAnimationName, ShowFrame, true);
			SpriteRender->SetAnimPauseOn();

			ColMetaDatas.Clear();
		}
	}

	if (true == ImGui::Button("Data Save"))
	{
		Save();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Data Load"))
	{
		Load();
	}

	ImGui::InputFloat("RenderScaleRatio", &RenderScale);
	SpriteRender->SetScaleRatio(RenderScale);

	ImGui::Text(std::string("Show Animation Index : " + std::to_string(ShowFrame)).data());

	int InputStart = StartFrame;

	ImGui::InputInt("Animation Start", &InputStart);

	if (InputStart != StartFrame)
	{
		if (InputStart < 0)
		{
			InputStart = 0;
		}

		StartFrame = static_cast<UINT>(InputStart);
	}

	int InputEnd = EndFrame;

	ImGui::InputInt("Animation End", &InputEnd);

	if (InputEnd != EndFrame)
	{
		if (InputEnd < 0)
		{
			InputEnd = 0;
		}

		EndFrame = static_cast<UINT>(InputEnd);
	}

	if (true == ImGui::Button("Prev", ImVec2(60, 30)))
	{
		if (StartFrame == ShowFrame)
		{
			ShowFrame = EndFrame;
		}
		else
		{
			--ShowFrame;
		}

		SpriteRender->ChangeAnimation(SpriteAnimationName, ShowFrame, true);
		SpriteRender->SetAnimPauseOn();
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Next", ImVec2(60, 30)))
	{
		if (EndFrame == ShowFrame)
		{
			ShowFrame = StartFrame;
		}
		else
		{
			++ShowFrame;
		}

		SpriteRender->ChangeAnimation(SpriteAnimationName, ShowFrame, true);
		SpriteRender->SetAnimPauseOn();
	}

	ImGui::Spacing();
	ImGui::Spacing();

	if (nullptr == ColRender)
	{
		ImGui::Text("DebugCollisionRender Not Found");
		return;
	}

	if (true == ImGui::Button("Create AnimCol Data"))
	{
		ColMetaDatas.Create(SpriteAnimationName, StartFrame, EndFrame);
	}

	ImGui::SameLine();

	if (true == ImGui::Button("Clear AnimCol Data"))
	{
		ColMetaDatas.Clear();
	}

	if (0 == ColMetaDatas.AttackMetaData.size())
	{
		ColRender->DrawColData({});
		return;
	}
	else
	{
		int Frame = ShowFrame - ColMetaDatas.AnimStart;

		if (0 <= Frame && ColMetaDatas.AttackMetaData.size() > Frame)
		{
			ColMetaDatas.ShowGUI(Frame);
			ColRender->DrawColData(ColMetaDatas.AttackMetaData[Frame]);
		}
	}
}

void AnimationCollisionToolGUI::SetRenderer(std::shared_ptr<class GameEngineSpriteRenderer> _Render)
{
	SpriteRender = _Render;
}

void AnimationCollisionToolGUI::SetCol(std::shared_ptr<AttackColRender> _Render)
{
	ColRender = _Render;
}

void AnimationCollisionToolGUI::Save()
{
	std::string Path = ContentFunc::GetSaveFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(2048);

	ColMetaDatas.SaveBin(SaveSerializer);

	GameEngineFile SaveFile = GameEngineFile(Path);
	SaveFile.SaveBin(SaveSerializer);
}

void AnimationCollisionToolGUI::Load()
{
	std::string Path = ContentFunc::GetOpenFilePath();

	if ("" == Path)
	{
		return;
	}

	ColMetaDatas.Clear();

	GameEngineFile LoadFile = GameEngineFile(Path);

	GameEngineSerializer LoadSerializer;
	LoadSerializer.BufferResize(2048);
	LoadFile.LoadBin(LoadSerializer);

	ColMetaDatas.LoadBin(LoadSerializer);

	SpriteAnimationName = ColMetaDatas.GetSpriteName();
	std::shared_ptr<GameEngineSprite> FindSprite = GameEngineSprite::Find(SpriteAnimationName);

	if (nullptr == FindSprite)
	{
		MsgAssert_Rtti<AnimationCollisionToolGUI>(" - 로드되지 않은 시트를 사용하려 했습니다");
		return;
	}

	std::shared_ptr<AnimationInfo> FindAnimInfo = SpriteRender->FindAnimation(SpriteAnimationName);

	if (nullptr == FindAnimInfo)
	{
		FindAnimInfo = SpriteRender->CreateAnimation({ .AnimationName = SpriteAnimationName, .SpriteName = SpriteAnimationName, .ScaleToTexture = true });
		EndFrame = static_cast<UINT>(FindAnimInfo->EndFrame);
	}

	ShowFrame = 0;

	SpriteRender->ChangeAnimation(SpriteAnimationName, ShowFrame, true);
	SpriteRender->SetAnimPauseOn();
}