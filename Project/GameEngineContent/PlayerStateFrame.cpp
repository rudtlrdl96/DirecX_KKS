#include "PrecompileHeader.h"
#include "PlayerStateFrame.h"

#include <GameEngineCore/GameEngineLevel.h>

#include "ContentUIRender.h"
#include "Player.h"
#include "PlayerBaseSkull.h"

#include "ProgressUI_Circle.h"
#include "PlayerHealthBar.h"
#include "PlayerState.h"

PlayerStateFrame::PlayerStateFrame()
{
}

PlayerStateFrame::~PlayerStateFrame()
{
}

void PlayerStateFrame::SetParentPlayer(Player* _Player)
{
	ParentPlayer = _Player;
}

void PlayerStateFrame::FrameOn()
{
	Progress = 0.0f;
	State = FrameState::On;
	On();
}

void PlayerStateFrame::FrameOff()
{
	State = FrameState::Off;
	Progress = 0.0f;
}

void PlayerStateFrame::Start()
{
	if (nullptr == GameEngineTexture::Find("Player_MainFrame.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Player_MainFrame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Player_MainSkillB_Frame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Player_QuintessenceFrame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Player_SubSkillA_Frame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Player_SubSkillB_Frame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Player_SubSkull_Frame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("SkillCoolDownFront.png.png").GetFullPath());
			
		GameEngineTexture::Load(Path.GetPlusFileName("PlayerHealthBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("PlayerSubBar.png").GetFullPath());	
	}

	if (nullptr == GameEngineSprite::Find("MainSkillCooldownEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MainSkillCooldownEffect.png").GetFullPath(), 5, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MainSwitchCooldownEffect.png").GetFullPath(), 5, 4);


		EffectManager::CreateMetaData("MainSkillCooldownEffect", {
			.SpriteName = "MainSkillCooldownEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("MainSwitchCooldownEffect", {
			.SpriteName = "MainSwitchCooldownEffect.png",
			.AnimStart = 0,
			.AnimEnd = 19,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });
	}

	RenderCreate(MainFrame, float4(0, 0, 5.0f), "Player_MainFrame.png");

	Progress_Switch = GetLevel()->CreateActor<ProgressUI_Circle>();
	Progress_Switch->GetTransform()->SetParent(GetTransform());
	Progress_Switch->InitValue(float4(43.5f, 43.5f, 1), float4(0, 0, 0, 0.7f));
	Progress_Switch->InitProgressType(ProgressType::Circle, FillType::Down);
	Progress_Switch->GetTransform()->SetLocalPosition(float4(-73.0f, 9.0f, 4.7f));

	RenderCreate(TexRender_MainSkull, float4(-72.5f, 9.5f, 4.9f), "Empty.png");
	RenderCreate(TexRender_MainSkillA, float4(-31.5f, 6.5f, 4.8f), "Empty.png");
	RenderCreate(CooldownRender_MainSkillA, float4(-31.5f, 6.5f, 4.75f), "SkillCoolDownFront.png");
	CooldownRender_MainSkillA->GetTransform()->SetLocalScale(float4(24, 24, 1));
	CooldownRender_MainSkillA->Off();

	Progress_MainSkillA = GetLevel()->CreateActor<ProgressUI_Circle>();
	Progress_MainSkillA->GetTransform()->SetParent(GetTransform());
	Progress_MainSkillA->InitValue(float4(25.0f, 25.0f, 1), float4(0, 0, 0, 0.7f));
	Progress_MainSkillA->InitProgressType(ProgressType::Box, FillType::Down);
	Progress_MainSkillA->GetTransform()->SetLocalPosition(float4(-31.0f, 6.0f, 4.7f));

	RenderCreate(MainSkillBFrame, float4(0, 0, 4.0f), "Player_MainSkillB_Frame.png");
	RenderCreate(TexRender_MainSkillB, float4(0.5f, 6.5f, 3.9f), "Empty.png");
	RenderCreate(CooldownRender_MainSkillB, float4(0.5f, 6.5f, 3.85f), "SkillCoolDownFront.png");
	CooldownRender_MainSkillB->GetTransform()->SetLocalScale(float4(24, 24, 1));
	CooldownRender_MainSkillB->Off();

	Progress_MainSkillB = GetLevel()->CreateActor<ProgressUI_Circle>();
	Progress_MainSkillB->GetTransform()->SetParent(GetTransform());
	Progress_MainSkillB->InitValue(float4(25.0f, 25.0f, 1), float4(0, 0, 0, 0.7f));
	Progress_MainSkillB->InitProgressType(ProgressType::Box, FillType::Down);
	Progress_MainSkillB->GetTransform()->SetLocalPosition(float4(0.0f, 6.0f, 3.8f));

	RenderCreate(SubSkullFrame, float4(0, 0, 3.0f), "Player_SubSkull_Frame.png");
	RenderCreate(TexRender_SubSkull, float4(-82.5f, -14.5f, 2.9f), "Empty.png");
	RenderCreate(SubSkillFrame_A, float4(0, 0, 2.0f), "Player_SubSkillA_Frame.png");
	RenderCreate(TexRender_SubSkillA, float4(28, 1, 1.9f), "Empty.png");
	RenderCreate(CooldownRender_SubSkillA, float4(28, 1, 1.85f), "SkillCoolDownFront.png");
	CooldownRender_SubSkillA->GetTransform()->SetLocalScale(float4(17, 17, 1));
	CooldownRender_SubSkillA->Off();

	Progress_SubSkillA = GetLevel()->CreateActor<ProgressUI_Circle>();
	Progress_SubSkillA->GetTransform()->SetParent(GetTransform());
	Progress_SubSkillA->InitValue(float4(17.0f, 17.0f, 1), float4(0, 0, 0, 0.7f));
	Progress_SubSkillA->InitProgressType(ProgressType::Box, FillType::Down);
	Progress_SubSkillA->GetTransform()->SetLocalPosition(float4(28.0f, 1.0f, 1.7f));

	RenderCreate(SubSkillFrame_B, float4(0, 0, 1.0f), "Player_SubSkillB_Frame.png");
	RenderCreate(TexRender_SubSkillB, float4(51, 1, 0.9f), "Empty.png");
	RenderCreate(CooldownRender_SubSkillB, float4(51, 1, 0.85f), "SkillCoolDownFront.png");
	CooldownRender_SubSkillB->GetTransform()->SetLocalScale(float4(17, 17, 1));
	CooldownRender_SubSkillB->Off();

	Progress_SubSkillB = GetLevel()->CreateActor<ProgressUI_Circle>();
	Progress_SubSkillB->GetTransform()->SetParent(GetTransform());
	Progress_SubSkillB->InitValue(float4(17.0f, 17.0f, 1), float4(0, 0, 0, 0.7f));
	Progress_SubSkillB->InitProgressType(ProgressType::Box, FillType::Down);
	Progress_SubSkillB->GetTransform()->SetLocalPosition(float4(51.0f, 1.0f, 0.7f));

	RenderCreate(QuintessenceFrame, float4(0, 0, 0.0f), "Player_QuintessenceFrame.png");
	
	GetTransform()->SetWorldScale(float4(2.0f, 2.0f, 2.0f));
	GetTransform()->SetWorldPosition(float4(-439, -293, 0));

	HealthBarPtr = GetLevel()->CreateActor<PlayerHealthBar>();
	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(1, -16, 0));
	HealthBarPtr->SetTexture("PlayerHealthBar.png", "PlayerSubBar.png");
	HealthBarPtr->SetScale(1.325f);

	StartPos = float4(-439, -430);
	EndPos = float4(-439, -293);
}



#include "GameEngineActorGUI.h"

void PlayerStateFrame::Update(float _DeltaTime)
{
	switch (State)
	{
	case FrameState::On:
	{
		Progress += _DeltaTime * 2.0f;

		GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, EndPos, Progress));

		if (1.0f <= Progress)
		{
			State = FrameState::None;
		}
	}
	break;
	case FrameState::Off:
	{
		Progress += _DeltaTime * 2.0f;

		GetTransform()->SetWorldPosition(float4::LerpClamp(EndPos, StartPos, Progress));

		if (1.0f <= Progress)
		{
			Off();
			State = FrameState::None;
		}

	}
	break;
	}

	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(GetTransform());
	Ptr->On();

	if (nullptr == ParentPlayer)
	{
		MsgAssert_Rtti<PlayerStateFrame>(" - 플레이어가 설정되지 않았습니다");
		return;
	}

	if (nullptr == ParentPlayer->MainSkull)
	{
		MsgAssert_Rtti<PlayerStateFrame>(" - 메인스컬 정보가 없습니다");
		return;
	}

	TexRender_MainSkull->SetScaleToTexture(ParentPlayer->MainSkull->GetTexName_MainSkullUI());
	TexRender_MainSkull->On();

	HealthBarPtr->UpdateBar(PlayerState::HP, PlayerState::MaxHP, _DeltaTime);

	{
		float SwitchProgress = ParentPlayer->SwitchCoolTime / ParentPlayer->SwitchCoolEndTime;

		Progress_Switch->UpdateProgress(SwitchProgress);

		if (true == Progress_Switch->IsProgressEnd())
		{
			EffectManager::PlayEffect({
				.EffectName = "MainSwitchCooldownEffect",
				.Position = Progress_Switch->GetTransform()->GetWorldPosition() + float4(0, 70, -0.1f),
				.IsUI = true
				});
		}
	}

	{
		float MainSkillAProgress = ParentPlayer->MainSkull->GetCurSkillATime() / ParentPlayer->MainSkull->GetSkillAEndTime();

		if (true == ParentPlayer->MainSkull->IsActiveSkillA() &&
			(true == ParentPlayer->MainSkull->IsSkillALock() || 1.0f > MainSkillAProgress))
		{
			CooldownRender_MainSkillA->On();
		}
		else
		{
			CooldownRender_MainSkillA->Off();
		}

		Progress_MainSkillA->UpdateProgress(MainSkillAProgress);

		if (true == Progress_MainSkillA->IsProgressEnd())
		{
			EffectManager::PlayEffect({
				.EffectName = "MainSkillCooldownEffect",
				.Position = Progress_MainSkillA->GetTransform()->GetWorldPosition() + float4(0, 38, -0.1f),
				.IsUI = true
				});
		}
	}

	{
		float MainSkillBProgress = ParentPlayer->MainSkull->GetCurSkillBTime() / ParentPlayer->MainSkull->GetSkillBEndTime();

		if (true == ParentPlayer->MainSkull->IsActiveSkillB() &&
			(true == ParentPlayer->MainSkull->IsSkillBLock() || 1.0f > MainSkillBProgress))
		{
			CooldownRender_MainSkillB->On();
		}
		else
		{
			CooldownRender_MainSkillB->Off();
		}

		Progress_MainSkillB->UpdateProgress(MainSkillBProgress);

		if (true == Progress_MainSkillB->IsProgressEnd())
		{
			EffectManager::PlayEffect({
				.EffectName = "MainSkillCooldownEffect",
				.Position = Progress_MainSkillB->GetTransform()->GetWorldPosition() + float4(0, 38, -0.1f),
				.IsUI = true
				});
		}
	}

	if (true == ParentPlayer->MainSkull->IsActiveSkillA())
	{
		TexRender_MainSkillA->SetScaleToTexture(ParentPlayer->MainSkull->GetTexName_SkillA());
	}
	else
	{
		TexRender_MainSkillA->SetScaleToTexture("Empty.png");
	}

	if (true == ParentPlayer->MainSkull->IsActiveSkillB())
	{
		TexRender_MainSkillB->SetScaleToTexture(ParentPlayer->MainSkull->GetTexName_SkillB());
	}
	else
	{
		TexRender_MainSkillB->SetScaleToTexture("Empty.png");
	}

	if (nullptr == ParentPlayer->SubSkull)
	{
		SubSkullFrame->Off();
		SubSkillFrame_A->Off();
		SubSkillFrame_B->Off();
		Progress_SubSkillA->Off();
		Progress_SubSkillB->Off();
	}
	else
	{
		SubSkullFrame->On();
		SubSkillFrame_A->On();
		SubSkillFrame_B->On();

		TexRender_SubSkull->SetScaleToTexture(ParentPlayer->SubSkull->GetTexName_SubSkullUI());

		if (true == ParentPlayer->SubSkull->IsActiveSkillA())
		{
			TexRender_SubSkillA->SetTexture(ParentPlayer->SubSkull->GetTexName_SkillA());
			TexRender_SubSkillA->GetTransform()->SetLocalScale(float4(17, 17, 1));

			{
				float SubSkillAProgress = ParentPlayer->SubSkull->GetCurSkillATime() / ParentPlayer->SubSkull->GetSkillAEndTime();

				if (true == ParentPlayer->SubSkull->IsSkillALock() || 1.0f > SubSkillAProgress)
				{
					CooldownRender_SubSkillA->On();
				}
				else
				{
					CooldownRender_SubSkillA->Off();
				}

				Progress_SubSkillA->UpdateProgress(SubSkillAProgress);
			}
		}
		else
		{
			Progress_SubSkillA->Off();
			TexRender_SubSkillA->SetTexture("Empty.png");
			CooldownRender_SubSkillA->Off();
		}

		if (true == ParentPlayer->SubSkull->IsActiveSkillB())
		{
			TexRender_SubSkillB->SetTexture(ParentPlayer->SubSkull->GetTexName_SkillB());
			TexRender_SubSkillB->GetTransform()->SetLocalScale(float4(17, 17, 1));

			{
				float SubSkillBProgress = ParentPlayer->SubSkull->GetCurSkillBTime() / ParentPlayer->SubSkull->GetSkillBEndTime();

				if (true == ParentPlayer->SubSkull->IsSkillBLock() || 1.0f > SubSkillBProgress)
				{
					CooldownRender_SubSkillB->On();
				}
				else
				{
					CooldownRender_SubSkillB->Off();
				}

				Progress_SubSkillB->UpdateProgress(SubSkillBProgress);
			}
		}
		else
		{
			TexRender_SubSkillB->SetTexture("Empty.png");
			Progress_SubSkillB->Off();
			CooldownRender_SubSkillB->Off();
		}
	}

	if (nullptr == ParentPlayer->Quintessence)
	{
		QuintessenceFrame->Off();
	}
	else
	{
		QuintessenceFrame->On();
	}
}

void PlayerStateFrame::RenderCreate(std::shared_ptr<class ContentUIRender>& _Render, const float4& _LocalPos, const std::string_view& _TextureName /*= "Empty.png"*/)
{
	_Render = CreateComponent<ContentUIRender>();
	_Render->PipeSetting("2DTexture_Color");
	_Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	_Render->GetTransform()->SetLocalPosition(_LocalPos);
	_Render->SetScaleToTexture(_TextureName);
	_Render->On();
}
