#include "PrecompileHeader.h"
#include "CameraController.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineActor.h>

CameraController::CameraController()
{
}

CameraController::~CameraController()
{
}

void CameraController::Start(GameEngineCamera* _MainCam)
{
	if (nullptr == _MainCam)
	{
		MsgAssert("CameraController - nullptr 카메라를 설정하려 했습니다");
	}

	MainCamera = _MainCam;
	MainCamera->SetProjectionType(CameraType::Orthogonal);

	WindowSize = GameEngineWindow::GetScreenSize();
	WindowSizeHalf = WindowSize.half();
}

void CameraController::Update(float _DeltaTime)
{
	if (true == IsScaleRatio)
	{
		CurScaleProgress += _DeltaTime * ScaleSpeed;


		MainCamera->SetZoomRatio(ContentFunc::Lerp<float>(StartScale, EndScale ,CurScaleProgress));

		if (1.0f <= CurScaleProgress)
		{
			IsScaleRatio = false;
		}
	}

	if (true == MainCamera->IsFreeCamera())
	{
		return;
	}


	float4 CurCamPos = CamPos;
	float4 TargetWorldPos = CurCamPos;

	float DiffX = 0.0f;
	float DiffY = 0.0f;

	switch (CamType)
	{
	case CameraController::CamCtrlType::None:
	{
		break;
	}
	case CameraController::CamCtrlType::LookAt:
	{
		float4 LookatPos = float4::Zero;

		if (false == IsForceTarget)
		{
			if (nullptr == LookAtTarget)
			{
				CamType = CamCtrlType::None;
				return;
			}

			if (true == LookAtTarget->IsDeath())
			{
				LookAtTarget = nullptr;
				return;
			}

			TargetWorldPos = CurCamPos;

			LookatPos = LookAtTarget->GetTransform()->GetWorldPosition();
		}
		else
		{
			LookatPos = ForceTargetPos;		
		}
		
		DiffX = LookatPos.x - CurCamPos.x;
		DiffY = LookatPos.y - CurCamPos.y;
		break;
	}
	case CameraController::CamCtrlType::Move:
	{
		LerpMoveProgress += _DeltaTime * LerpMoveSpeed;
		TargetWorldPos = float4::LerpClamp(MoveStartPos, MoveEndPos, LerpMoveProgress);

		if (LerpMoveProgress >= 1.0f)
		{
			if (nullptr == LookAtTarget)
			{
				CamType = CamCtrlType::None;
			}
			else
			{
				CamType = CamCtrlType::LookAt;
			}
		}
		break;
	}
	default:
		MsgAssert("잘못된 카메라 컨트롤러 타입 입니다.");
		break;
	}
		
	if (CamCtrlType::LookAt == CamType)
	{
		float4 DiffDir = float4(DiffX, DiffY);
		float DiffSize = DiffDir.Size();

		float CamMove = _DeltaTime * DiffSize * LookatSpeed;


		if (DiffSize > 1.0f)
		{
			DiffDir.Normalize();
			TargetWorldPos +=  DiffDir * CamMove;
		}
	}

	if (TargetWorldPos.x - WindowSizeHalf.x <= MinWidth)
	{
		TargetWorldPos.x = MinWidth + WindowSizeHalf.x;
	}
	else if (TargetWorldPos.x + WindowSizeHalf.x > MaxWidth)
	{
		TargetWorldPos.x = MaxWidth - WindowSizeHalf.x;
	}

	if (TargetWorldPos.y - WindowSizeHalf.y <= MinHeight)
	{
		TargetWorldPos.y = MinHeight + WindowSizeHalf.y;
	}
	else if (TargetWorldPos.y + WindowSizeHalf.y > MaxHeight)
	{
		TargetWorldPos.y = MaxHeight - WindowSizeHalf.y;
	}

	CamPos = TargetWorldPos;
	LastCameraPos = TargetWorldPos;
	LastCameraRot = CamRot;

	// 카메라 효과 적용
	CameraEffectPos = float4::Zero;

	if (0 < ShakeCount)
	{
		ShakeProgress += _DeltaTime * ShakeSpeed;
		CameraEffectPos = float4::LerpClamp(StartShakePos, EndShakePos, ShakeProgress);
	
		if (1.0f <= ShakeProgress)
		{
			ShakeProgress -= 1.0f;
			--ShakeCount;
			CalShakeValue();
		}
	}

	LastCameraPos += CameraEffectPos;
	
	MainCamera->GetTransform()->SetWorldPosition(LastCameraPos);
	MainCamera->GetTransform()->SetWorldRotation(LastCameraRot);
}

void CameraController::CameraMove_Lerp(const float4& _Start, const float4& _End, float _Time)
{
	MoveStartPos = _Start;
	MoveStartPos.z = CamPos.z;
	
	MoveEndPos = _End;
	MoveEndPos.z = CamPos.z;;

	LerpMoveSpeed = 1.0f / _Time;
	LerpMoveProgress = 0.0f;
	CamType = CamCtrlType::Move;
}

void CameraController::CameraShake(float _ShakeDis, float _ShakeSpeed, int _ShakeCount)
{
	ShakeCount = _ShakeCount;
	ShakeSpeed = _ShakeSpeed;
	ShakeMinDistance = _ShakeDis * 0.8f;
	ShakeMaxDistance = _ShakeDis * 1.2f;
	ShakeProgress = 0.0f;

	StartShakePos = float4::Zero;
	EndShakePos = float4::Zero;
	CalShakeValue();
}

void CameraController::SetCameraPos(const float4& _Pos)
{
	CamPos = _Pos;
	MainCamera->GetTransform()->SetWorldPosition(CamPos);
}

void CameraController::AddCameraPos(const float4& _Pos)
{
	CamPos += _Pos;
	MainCamera->GetTransform()->SetWorldPosition(CamPos);
}

void CameraController::SetLookatTarget(std::shared_ptr<GameEngineActor> _Target)
{
	LookAtTarget = _Target;

	if (nullptr == LookAtTarget)
	{
		CamType = CamCtrlType::None;
	}
	else
	{
		CamType = CamCtrlType::LookAt;
	}
}

void CameraController::ResetScale()
{
	IsScaleRatio = false;

	CurScaleProgress = 0.0f;
	ScaleSpeed = 1.0f;

	float4 WindowSize = GameEngineWindow::GetScreenSize();
	MainCamera->SetZoomRatio(1.0f);
}

void CameraController::EffectScaleRatio(float _Start, float _End, float _Speed)
{
	IsScaleRatio = true;

	StartScale = _Start;
	EndScale = _End;

	CurScaleProgress = 0.0f; 
	ScaleSpeed = _Speed;
}

void CameraController::CalShakeValue()
{
	StartShakePos = EndShakePos;

	if (ShakeCount == 1)
	{
		EndShakePos = float4::Zero;
		return;
	}

	float RandomRot = GameEngineRandom::MainRandom.RandomFloat(0.0f, GameEngineMath::PIE2);
	float RandomDis = GameEngineRandom::MainRandom.RandomFloat(ShakeMinDistance, ShakeMaxDistance);

	EndShakePos.x = sinf(RandomRot);
	EndShakePos.y = cosf(RandomRot);

	EndShakePos *= RandomDis;
}