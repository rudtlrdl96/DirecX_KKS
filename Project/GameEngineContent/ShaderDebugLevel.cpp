#include "PrecompileHeader.h"
#include "ShaderDebugLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

// Actors
#include "DebugBoxActor.h"

ShaderDebugLevel::ShaderDebugLevel()
{
}

ShaderDebugLevel::~ShaderDebugLevel()
{
}

void ShaderDebugLevel::Start()
{
	if (false == GameEngineInput::IsKey("CameraRot"))
	{
		GameEngineInput::CreateKey("CameraRot", '0');
		GameEngineInput::CreateKey("CameraRotX", '7');
		GameEngineInput::CreateKey("CameraRotY", '8');
		GameEngineInput::CreateKey("CameraRotZ", '9');
	}

	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("Debug");

		std::vector<GameEngineFile> File = Path.GetAllFile({ ".Png", });

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	MainCam = GetMainCamera();
	MainCam->SetProjectionType(CameraType::Perspective);
	MainCam->GetTransform()->SetWorldPosition(float4(0, 0, -1000, 1));

	ShaderTestActor = CreateActor<DebugBoxActor>();
}

void ShaderDebugLevel::Update(float _DeltaTime)
{
	BaseDebugLevel::Update(_DeltaTime);

	if (nullptr == MainCam || nullptr == ShaderTestActor)
	{
		return;
	}

	if (true == GameEngineInput::IsDown("CameraRotX"))
	{
		if (true == IsTargetRot && TargetRotState == TargetRotType::X)
		{
			IsTargetRot = false;
		}
		else
		{
			IsTargetRot = true;
		}

		TargetRotState = TargetRotType::X;
	}
	else if (true == GameEngineInput::IsDown("CameraRotY"))
	{
		if (true == IsTargetRot && TargetRotState == TargetRotType::Y)
		{
			IsTargetRot = false;
		}
		else
		{
			IsTargetRot = true;
		}

		TargetRotState = TargetRotType::Y;
	}
	else if (true == GameEngineInput::IsDown("CameraRotZ"))
	{
		if (true == IsTargetRot && TargetRotState == TargetRotType::Z)
		{
			IsTargetRot = false;
		}
		else
		{
			IsTargetRot = true;
		}

		TargetRotState = TargetRotType::Z;
	}

	if (true == GameEngineInput::IsDown("CameraRot"))
	{
		IsCameraRot = !IsCameraRot;

		if(true == IsCameraRot)
		{
			OldTrans = MainCam->GetTransform()->GetTransDataRef();
			RotVector = float4(0, 0, -1000, 1);
			MainCam->GetTransform()->SetLocalRotation(float4::Zero);
		}
		else
		{
			MainCam->GetTransform()->SetTransformData(OldTrans);
		}
	}

	if (true == IsTargetRot)
	{
		float4 RotTarget = float4::Zero;

		switch (TargetRotState)
		{
		case ShaderDebugLevel::TargetRotType::X:
			RotTarget.x += _DeltaTime * 100.0f;
			break;
		case ShaderDebugLevel::TargetRotType::Y:
			RotTarget.y += _DeltaTime * 100.0f;
			break;
		case ShaderDebugLevel::TargetRotType::Z:
			RotTarget.z += _DeltaTime * 100.0f;
			break;
		}

		ShaderTestActor->GetTransform()->AddLocalRotation(RotTarget);
	}

	if (true == IsCameraRot)
	{
		RotVector.RotaitonYDeg(_DeltaTime * 100.0f);

		float4 TargetPos = ShaderTestActor->GetTransform()->GetWorldPosition();

		MainCam->GetTransform()->AddLocalRotation(float4(0, _DeltaTime * 100.0f, 0));
		MainCam->GetTransform()->SetWorldPosition(TargetPos + RotVector);

	}
}
