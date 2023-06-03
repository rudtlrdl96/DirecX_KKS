#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEnginePlatform/GameEngineWindow.h>

static UINT NewLevelCode = 0;

ContentLevel::ContentLevel() :
	LevelCode(++NewLevelCode)
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

	std::shared_ptr<GameEngineCamera> FadeCam = CreateActor<GameEngineCamera>();
	FadeCam->SetProjectionType(CameraType::Orthogonal);
	InsertCamera(101, FadeCam);

	MainCam = GetMainCamera();
	MainCamCtrl.Start(MainCam);
	MainCam->SetSortType(0, SortType::ZSort);
	MainCam->GetTransform()->SetLocalPosition({0, 0, -5000});
	MainCam->GetTransform()->SetLocalRotation(float4::Zero);

	std::shared_ptr<GameEngineCamera> UICam = GetCamera(100);
	UICam->SetProjectionType(CameraType::Orthogonal);
	UICam->SetSortType(0, SortType::ZSort);
	UICam->GetTransform()->SetLocalPosition({ 0, 0, -5000 });
}

void ContentLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	MainCamCtrl.Update(_DeltaTime);
}