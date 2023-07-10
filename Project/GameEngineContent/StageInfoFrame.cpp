#include "PrecompileHeader.h"
#include "StageInfoFrame.h"

StageInfoFrame::StageInfoFrame()
{
}

StageInfoFrame::~StageInfoFrame()
{
}

void StageInfoFrame::FrameOn(const std::string_view& _LevelName, const std::string_view& _StageNumber, const std::string_view& _StageName)
{
	LevelFontRender->SetText(_LevelName);
	StageNumberFontRender->SetText(_StageNumber);
	StageNameFontRender->SetText(_StageName);

	State = StageFrameState::Down;
	GetTransform()->SetWorldPosition(StartPos);
	Rigid.SetVelocity(float4::Zero);

	GroundColCount = 0;
}

void StageInfoFrame::FrameOff()
{
	State = StageFrameState::Up;
	GetTransform()->SetWorldPosition(EndPos);
	Rigid.SetVelocity(float4::Zero);
}

void StageInfoFrame::Start()
{
	FrameRender = CreateComponent<GameEngineUIRenderer>();
	FrameRender->SetScaleToTexture("InDungeon.png");

	float4 FrameScale = FrameRender->GetTransform()->GetLocalScale();
	FrameRender->GetTransform()->SetLocalScale(FrameScale * 2.0f);

	LevelFontRender = CreateComponent<ContentUIFontRenderer>();
	LevelFontRender->SetFont("³Ø½¼Lv2°íµñ");
	LevelFontRender->GetTransform()->SetLocalPosition(float4(0, 2, -1));
	LevelFontRender->SetScale(18);
	LevelFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	LevelFontRender->SetColor(float4(0.647f, 0.5725f, 0.5254f, 1));

	StageNumberFontRender = CreateComponent<ContentUIFontRenderer>();
	StageNumberFontRender->SetFont("HY°ß°íµñ");
	StageNumberFontRender->GetTransform()->SetLocalPosition(float4(0, -21, -1));
	StageNumberFontRender->SetScale(18);
	StageNumberFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	StageNumberFontRender->SetColor(float4(0.647f, 0.5725f, 0.5254f, 1));

	StageNameFontRender = CreateComponent<ContentUIFontRenderer>();
	StageNameFontRender->SetFont("³Ø½¼Lv2°íµñ");
	StageNameFontRender->GetTransform()->SetLocalPosition(float4(0, -54, -1));
	StageNameFontRender->SetScale(24);
	StageNameFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	StageNameFontRender->SetColor(float4(0.7647f, 0.7058f, 0.6627f, 1));

	StartPos = float4(0, 500, 0);
	EndPos = float4(0, 234, 0);

	GetTransform()->SetWorldPosition(StartPos);

	Rigid.SetMaxSpeed(500.0f);
}

void StageInfoFrame::Update(float _DeltaTime)
{
	switch (State)
	{
	case StageFrameState::Down:
	{
		if (1 < GroundColCount)
		{
			Rigid.AddForce(float4(0, -1200));
		}
		else
		{
			Rigid.AddForce(float4(0, -800));
		}

		Rigid.UpdateForce(_DeltaTime);

		float4 TotalVel = Rigid.GetVelocity();
		float4 FrameVel = TotalVel * _DeltaTime;

		float4 CurPos = GetTransform()->GetWorldPosition();

		if (0.0f > FrameVel.y && EndPos.y > CurPos.y + FrameVel.y)
		{
			++GroundColCount;

			if (125.0f < TotalVel.Size())
			{
				TotalVel.y = -TotalVel.y * 0.55f;
				Rigid.SetVelocity(TotalVel);

				TotalVel = Rigid.GetVelocity();
				FrameVel = TotalVel * _DeltaTime;
			}
			else
			{
				State = StageFrameState::Wait;
				WaitTime = 0.0f;
				GetTransform()->SetWorldPosition(EndPos);
				return;
			}
		}

		GetTransform()->AddWorldPosition(FrameVel);
	}
		break;
	case StageFrameState::Wait:
	{
		WaitTime += _DeltaTime;

		if (2.0f <= WaitTime)
		{
			FrameOff();
			WaitTime = 0.0f;
		}
	}
		break;
	case StageFrameState::Up:
	{
		Rigid.AddForce(float4(0, 1000));
		Rigid.UpdateForce(_DeltaTime);

		float4 TotalVel = Rigid.GetVelocity();
		float4 FrameVel = TotalVel * _DeltaTime;

		GetTransform()->AddWorldPosition(FrameVel);

		float4 CurPos = GetTransform()->GetWorldPosition();

		if (StartPos.y <= CurPos.y)
		{
			GetTransform()->SetWorldPosition(StartPos);
			State = StageFrameState::None;
		}
	}
		break;
	default:
		break;
	}

}
